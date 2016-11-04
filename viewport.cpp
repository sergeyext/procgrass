#include "viewport.h"
#include "ui_viewport.h"

#include <cmath>
#include <random>

#include <QMessageBox>

Viewport::Viewport(QWidget* parent) :
QOpenGLWidget(parent),
ui(new Ui::Viewport) {
    ui->setupUi(this);
    setMouseTracking(true);
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setSamples(32);
    setFormat(fmt);
}

Viewport::~Viewport() {
    makeCurrent();
    glDeleteTextures(1, &randTexture);
    glDeleteQueries(1, &primQuery);
    glDeleteQueries(1, &timeQuery);
    delete pg;
    delete ui;
    doneCurrent();
}

void Viewport::setWindEnabled(bool enabled) {
    makeCurrent();
    grassShader.setUniformValue("windEnabled", enabled ? 1.0f : 0.0f);
    doneCurrent();
}

void Viewport::setShiveringEnabled(bool enabled) {
    makeCurrent();
    grassShader.setUniformValue("shiveringEnabled", enabled ? 1.0f : 0.0f);
    doneCurrent();
}

void Viewport::setWindTurbulence(int turb) {
    makeCurrent();
    grassShader.setUniformValue("windTurbulence", turb / 100.0f);
    doneCurrent();
}

void Viewport::setWindSpeed(int speed) {
    makeCurrent();
    grassShader.setUniformValue("windSpeed", GLfloat(speed));
    doneCurrent();
}

void Viewport::setWindDirection(GLfloat x, GLfloat y, GLfloat z) {
    makeCurrent();
    GLfloat n = sqrt(x * x + y * y + z *z);
    const GLfloat thresh = 1e-03;
    if(n < thresh) {
        grassShader.setUniformValue("windDirection", 0.0f, 0.0f, 0.0f);
    } else {
        grassShader.setUniformValue("windDirection", x / n, y / n, z / n);
    }
    doneCurrent();
}

void Viewport::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    pg = new ProceduralGrass;

    // Generate uniform random data from [0, 1].
    const GLuint randTexSize = 256;
    GLfloat randTexData[randTexSize];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    std::generate(randTexData, randTexData + randTexSize, [&](){return dis(gen);});
    // Create and tune random texture.
    glGenTextures(1, &randTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, randTexture);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_R16F, randTexSize, 0, GL_RED, GL_FLOAT, randTexData);
    glUniform1i(glGetUniformLocation(grassShader.programId(), "urandom01"), 0);
    // Queries.
    glGenQueries(1, &primQuery);
    glGenQueries(1, &timeQuery);
    // Shader.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    if(grassShader.init({
        "shared.glsl",
        "classicnoise2D.glsl",
        "classicnoise3D.glsl",
        "worley.glsl"
    }, "grass") != 0) {
        QMessageBox::critical(0, "Error.", "Could not initialize shader.");
        return;
    }
    grassShader.bind();
    grassShader.setUniformValue("numPrimitives", pg->getNumClusters());

    // Go.
    enableDraw = true;
    startTimer(10);
}

void Viewport::resizeGL(int w, int h) {
    camera.setProjection(w, h);
}

void Viewport::mousePressEvent(QMouseEvent* ev) {
    ev->accept();
    leftBtnPressed = ev->buttons() & Qt::LeftButton;
    if(leftBtnPressed) {
        prevX = ev->x();
        prevY = ev->y();
        grabMouse();
    }
}

void Viewport::mouseReleaseEvent(QMouseEvent* ev) {
    ev->accept();
    leftBtnPressed = ev->buttons() & Qt::LeftButton;
    if(!leftBtnPressed) {
        releaseMouse();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *ev) {
    ev->accept();
    if(!leftBtnPressed) {
        return;
    }
    static const float MOUSE_SENSITIVITY = 0.003f;
    camera.rotate((prevY - ev->y()) * MOUSE_SENSITIVITY,
        (prevX - ev->x()) * MOUSE_SENSITIVITY);
    prevX = ev->x();
    prevY = ev->y();
}

void Viewport::keyPressEvent(QKeyEvent* ev) {
    static const float MOVEMENT_SPEED = 0.1f;
    switch(ev->key()) {
    case Qt::Key_W:
        dFwd = -MOVEMENT_SPEED;
        break;
    case Qt::Key_S:
        dFwd = MOVEMENT_SPEED;
        break;
    case Qt::Key_A:
        dSide = MOVEMENT_SPEED;
        break;
    case Qt::Key_D:
        dSide = -MOVEMENT_SPEED;
        break;
    default:
        QOpenGLWidget::keyPressEvent(ev);
    }
}

void Viewport::keyReleaseEvent(QKeyEvent* ev) {
    switch(ev->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
        dFwd = 0.0f;
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        dSide = 0.0f;
        break;
    default:
        QOpenGLWidget::keyReleaseEvent(ev);
    }
    ev->accept();
}

void Viewport::measure() {
    makeCurrent();
    GLuint prims;
    GLuint64 elapsed;
    glGetQueryObjectuiv(primQuery, GL_QUERY_RESULT, &prims);
    glGetQueryObjectui64v(timeQuery, GL_QUERY_RESULT, &elapsed);
    emit primitives(prims);
    emit fps(int(1.0 / (elapsed * 1e-9)));
    doneCurrent();
}

void Viewport::timerEvent(QTimerEvent* ev) {
    /**
     * @todo Write a correct main loop?
     * Tips:
     * http://gameprogrammingpatterns.com/game-loop.html
     * http://gamedev.stackexchange.com/questions/651/tips-for-writing-the-main-game-loop
     * http://gafferongames.com/game-physics/fix-your-timestep/
     */
    ev->accept();
    static const GLint totalFrames = 65536;
    frameNumber = (frameNumber + 1) % totalFrames;
    camera.move(dFwd, dSide);
    update();
    measure();
}

void Viewport::paintGL() {
    if(!enableDraw) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    grassShader.setUniformValue("viewProjectionMatrix", camera.getMatrix());
    grassShader.setUniformValue("eyePosition", camera.getPosition());
    grassShader.setUniformValue("lookDirection", camera.getLookDirection());
    grassShader.setUniformValue("frameNumber", frameNumber);
    glBeginQuery(GL_PRIMITIVES_GENERATED, primQuery);
    glBeginQuery(GL_TIME_ELAPSED, timeQuery);
    pg->draw();
    glEndQuery(GL_TIME_ELAPSED);
    glEndQuery(GL_PRIMITIVES_GENERATED);
}
