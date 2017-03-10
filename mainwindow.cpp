#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Control Panel");
    instrBlind = false;
    instrInLight = true;
    instrOutLight = true;

    // init server
    server = new QTcpServer();
    server->listen(QHostAddress::Any,6667); // (IP, port) will be changed
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//!------DO NOT REVISE BELOW---------------------------------------------------|
void MainWindow::acceptConnection()
{
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void MainWindow::readClient()
{
    QString str = clientConnection->readAll();
    displayReceivedMessage(str);
    //ui->textBrowser_2->setText(str);//TODO
}
//!------DO NOT REVISE ABOVE---------------------------------------------------|

// Calleby by manual button Or Timer
void MainWindow::displayReceivedMessage(QString str)
{
    QByteArray messages;
    messages.append(str);
    ui->TESTLabel->setText(messages.data());
    // deal with json
    QJsonDocument itemDoc = QJsonDocument::fromJson(messages);
    QJsonObject rootObject = itemDoc.object();

    isDay = rootObject.value("isDay").toBool();
    enableOutDoorLight = rootObject.value("enableOutDoorLight").toBool();
    enableInDoorLight = rootObject.value("enableInDoorLight").toBool();
    isOutLight = rootObject.value("isOutLight").toBool();
    isInLight = rootObject.value("isInLight").toBool();
    isBlind = rootObject.value("isBlind").toBool();

    ui->isDay->setText(QString::number(isDay));
    ui->enableOutLightPushButton->setText(QString::number(enableOutDoorLight));
    ui->enableInLightPushButton->setText(QString::number(enableInDoorLight));
    ui->isOutLight->setText(QString::number(isOutLight));
    ui->isInLight->setText(QString::number(isInLight));
    ui->isBlind->setText(QString::number(isBlind));
}

// Send instructions to Simulator
// Instructions is a list of instruction encoded by Integer Number
void MainWindow::on_onPushButton_clicked()
{
    QJsonObject bodyJson{
        {"instrOutLight", instrOutLight},
        {"instrInLight",instrInLight},
        {"instrBlind", instrBlind}
    };

    QJsonDocument doc(bodyJson);
    QString strJson(doc.toJson(QJsonDocument::Indented));

    // Create TCP sender
    QTcpSocket * client;
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("192.168.1.112"), 6663); // Send to (IP, PORT)
    QByteArray message;
    message.append(strJson);
    client->write(message);
}

// Receive info from Simulator
void MainWindow::on_refreshPushButton_clicked()
{
//    displayReceivedMessage();
}

void MainWindow::on_openBlindPushButton_clicked()
{
    instrBlind = !instrBlind;
    ui->openBlindPushButton->setText(QString::number(instrBlind));
}

void MainWindow::on_openInLightPushButton_clicked()
{
    instrInLight = !instrInLight;
    ui->openInLightPushButton->setText(QString::number(instrInLight));
}

void MainWindow::on_openOutLightPushButton_clicked()
{
    instrOutLight = !instrOutLight;
    ui->openOutLightPushButton->setText(QString::number(instrOutLight));
}
