#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimerEvent>

#include <QMatrix4x4>
#include <QVector3D>

#include "fpvcamera.h"
#include "shaderprogram.h"

#include "proceduralgrass.h"

namespace Ui {
    class Viewport;
}

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
    Q_OBJECT

public:
    explicit Viewport(QWidget *parent = 0);
    ~Viewport();

public slots:

    void setWindEnabled(bool enabled);

    void setShiveringEnabled(bool enabled);

    void setWindTurbulence(int turb);

    void setWindSpeed(int speed);

    void setWindDirection(GLfloat x, GLfloat y, GLfloat z);

signals:

    void primitives(int);
    void fps(int);

private:
    void initializeGL();

    void paintGL();

    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent* ev);

    void mouseReleaseEvent(QMouseEvent* ev);

    void mouseMoveEvent(QMouseEvent* ev);

    void keyPressEvent(QKeyEvent* ev);

    void keyReleaseEvent(QKeyEvent* ev);

    void timerEvent(QTimerEvent* ev);

    void measure();

    Ui::Viewport *ui;

    bool leftBtnPressed = false;
    int prevX = 0;
    int prevY = 0;
    float dFwd = 0.0f;
    float dSide = 0.0f;
    FpvCamera camera;

    ShaderProgram grassShader;
    ProceduralGrass *pg;

    GLuint randTexture;
    GLuint primQuery;
    GLuint timeQuery;

    GLint frameNumber = 0;
};

#endif // VIEWPORT_H
