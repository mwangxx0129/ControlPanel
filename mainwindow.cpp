#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sender.h"
#include "receiver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new Sender(45453); //45453 as sender port
    receiver = new Receiver(45455); //45455 as receiver port
//    timer = new QTimer(this); // open later

    this->setWindowTitle("Control Panel");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Calleby by manual button Or Timer
void MainWindow::displayReceivedMessage()
{
    QByteArray messages = receiver->processPendingDatagrams();
    ui->TESTLabel->setText(messages.data());
}

// Send instructions to Simulator
// Instructions is a list of instruction encoded by Integer Number
void MainWindow::on_onPushButton_clicked()
{
    sender->broadcastDatagram("1,2,3,");
}

// Receive info from Simulator
void MainWindow::on_refreshPushButton_clicked()
{
    displayReceivedMessage();
}
