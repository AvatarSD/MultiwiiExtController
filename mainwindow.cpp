#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(JoystickAdv * joy, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _joy(joy)
{
    ui->setupUi(this);
    ConnectionStatus = 0;
    ui->statusBar->showMessage("by S.D.");
//    _joy = new JoystickAdv();
    QObject::connect(_joy, SIGNAL(dataRsv(JoyData*)), this, SLOT(showJoy(JoyData*)));
    QObject::connect(_joy, SIGNAL(disconnected(QString)), this, SLOT(showDisconnectedJoy(QString)));
}

MainWindow::~MainWindow()
{
    delete _joy;
    delete ui;
}

void MainWindow::metriIn(mw_metric * data)
{
    ui->valAccelX->setText(QString::number(data->AccelX));
    ui->valAccelY->setText(QString::number(data->AccelY));
    ui->valAccelZ->setText(QString::number(data->AccelZ));

    ui->valGyroX->setText(QString::number(data->GyroX));
    ui->valGyroY->setText(QString::number(data->GyroY));
    ui->valGyroZ->setText(QString::number(data->GyroZ));

    ui->valMagX->setText(QString::number(data->MagX));
    ui->valMagY->setText(QString::number(data->MagY));
    ui->valMagZ->setText(QString::number(data->MagZ));
}

void MainWindow::showJoy(JoyData * joydata)
{

    ui->pbThrot->setValue(joydata->throt);
    ui->pbPich->setValue(joydata->pich);
    ui->pbRoll->setValue(joydata->roll);
    ui->pbYaw->setValue(joydata->yaw);
    ui->pbAux1->setValue(joydata->aux1);
    ui->pbAux2->setValue(joydata->aux2);
}

void MainWindow::on_btnConnect_clicked()
{
    static int ConnectionStatus = 0;
    if(ConnectionStatus == 0)
    {
        emit Connect(&ConnectionStatus, ui->valSerialName->text(), 115200);
        if(ConnectionStatus == 1)
        {
            ui->statusBar->showMessage("Connected");
            ui->btnConnect->setText("Connected");
        }
        else if(ConnectionStatus == 0)
        {
            ui->statusBar->showMessage("Disconnected");
            ui->btnConnect->setText("Disconnected");
        }
    }
    else
    {
      emit DisconnSig();
      ConnectionStatus = 0;
      ui->statusBar->showMessage("Disconnected");
    }
}

void MainWindow::showDisconnected()
{
    ui->statusBar->showMessage("Disconnected");
    ui->btnConnect->setText("Disconnected");
    ConnectionStatus = 0;
}


void MainWindow::on_btnConnectJoy_clicked()
{
    if(!(_joy->isConnected()))
    {
        _joy->BSerialPort::connect(ui->valJoyName->text().toStdString());
        if(_joy->isConnected()) ui->btnConnectJoy->setText("Connected");
    }
    else
    {
        _joy->BSerialPort::disconnect();
        ui->btnConnectJoy->setText("Connect");
    }
}

void MainWindow::showDisconnectedJoy(QString str)
{
    ui->statusBar->showMessage("Joy: " + str);
    ui->btnConnectJoy->setText("Connect");
}

void MainWindow::showSnarsData(const SonarsData & data)
{
if(data.getName() == "PD0")
    ui->sonarBar->setValue(data.getVal());
}
