#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
QWidget(parent),
ui(new Ui::ControlPanel) {
    ui->setupUi(this);
    connect(ui->windBox, SIGNAL(toggled(bool)), this, SIGNAL(windToggled(bool)));
    connect(ui->shiveringCheckbox, SIGNAL(toggled(bool)), this, SIGNAL(shiveringToggled(bool)));
    connect(ui->windTurbulenceSlider, SIGNAL(valueChanged(int)), this,
        SIGNAL(windTurbulenceChanged(int)));
    connect(ui->windSpeedSlider, SIGNAL(valueChanged(int)), this,
        SIGNAL(windSpeedChanged(int)));
    connect(ui->windXValue, SIGNAL(valueChanged(double)), this, SLOT(onWindDirChange()));
    connect(ui->windYValue, SIGNAL(valueChanged(double)), this, SLOT(onWindDirChange()));
    connect(ui->windZValue, SIGNAL(valueChanged(double)), this, SLOT(onWindDirChange()));
}

ControlPanel::~ControlPanel() {
    delete ui;
}

void ControlPanel::onWindDirChange() {
    emit windDirChanged(ui->windXValue->value(), ui->windYValue->value(), ui->windZValue->value());
}

void ControlPanel::setTriangles(const int tris) {
    ui->trianglesValue->setText(QString::number(tris));
}

void ControlPanel::setFps(const int fps) {
    ui->fpsValue->setText(QString::number(fps));
}
