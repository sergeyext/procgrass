#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QtOpenGL/QGL>

namespace Ui {
    class ControlPanel;
}

class ControlPanel : public QWidget {
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

private:
    Ui::ControlPanel *ui;

private slots:

    void onWindDirChange();

public slots:

    void setTriangles(const int tris);

    void setFps(const int fps);

signals:

    void windToggled(bool);

    void shiveringToggled(bool);

    void windTurbulenceChanged(int);

    void windSpeedChanged(int);

    void windDirChanged(GLfloat, GLfloat, GLfloat);
};

#endif // CONTROLPANEL_H
