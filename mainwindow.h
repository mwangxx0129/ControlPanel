#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayReceivedMessage(QString str);

private slots:
    void on_onPushButton_clicked();

    void on_refreshPushButton_clicked();

    void on_openBlindPushButton_clicked();

    void on_openInLightPushButton_clicked();

    void on_openOutLightPushButton_clicked();
    void acceptConnection();
    void readClient();

private:
    Ui::MainWindow *ui;

    bool isDay;
    bool enableOutDoorLight;
    bool enableInDoorLight;
    bool isOutLight;
    bool isInLight;
    bool isBlind;

    //instructions
    bool instrOutLight;
    bool instrInLight;
    bool instrBlind;

    QTcpServer *server;
    QTcpSocket *clientConnection;
};

#endif // MAINWINDOW_H
