#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->controls, SIGNAL(windToggled(bool)), ui->viewport, SLOT(setWindEnabled(bool)));
    connect(ui->controls, SIGNAL(shiveringToggled(bool)), ui->viewport,
        SLOT(setShiveringEnabled(bool)));
    connect(ui->controls, SIGNAL(windTurbulenceChanged(int)), ui->viewport,
        SLOT(setWindTurbulence(int)));
    connect(ui->controls, SIGNAL(windSpeedChanged(int)), ui->viewport, SLOT(setWindSpeed(int)));
    connect(ui->controls, SIGNAL(windDirChanged(GLfloat,GLfloat,GLfloat)), ui->viewport,
        SLOT(setWindDirection(GLfloat,GLfloat,GLfloat)));
    // Feedback.
    connect(ui->viewport, SIGNAL(primitives(int)), ui->controls, SLOT(setTriangles(int)));
    connect(ui->viewport, SIGNAL(fps(int)), ui->controls, SLOT(setFps(int)));
    ui->viewport->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* ev) {
    if(ev->key() == Qt::Key_Escape) {
        QApplication::instance()->quit();
    }
}
