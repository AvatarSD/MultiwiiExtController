#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mwtypes.h"
#include "Joystick/JoystickAdv/joystickadv.h"
#include <QString>
#include "sonars.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(JoystickAdv *joy, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    char ConnectionStatus;
    JoystickAdv * _joy;

signals:
    void Connect(int *res, QString port, int baud);
    void DisconnSig();

public slots:
    void metriIn(mw_metric * data);
    void showDisconnected();
    void showJoy(JoyData * joydata);
    void showDisconnectedJoy(QString str);
    void showSonarsData(SonarData data);

private slots:
    void on_btnConnect_clicked();
    void on_btnConnectJoy_clicked();
};

#endif // MAINWINDOW_H
