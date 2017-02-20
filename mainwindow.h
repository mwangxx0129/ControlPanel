#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Sender;
class Receiver;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayReceivedMessage();

private slots:
    void on_onPushButton_clicked();

    void on_refreshPushButton_clicked();

private:
    Ui::MainWindow *ui;
    Sender *sender;
    Receiver *receiver;
//    QTimer *timer; // receive  message interval
};

#endif // MAINWINDOW_H
