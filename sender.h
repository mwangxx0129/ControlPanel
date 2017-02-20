#ifndef SENDER_H
#define SENDER_H

class  QUdpSocket;

class Sender
{
public:
    Sender(quint16 p = 45454);
    void broadcastDatagram(QString);
private:
    QUdpSocket *udpSocket;
    quint16 port;
    int TEST_messageNo;
};

#endif // SENDER_H
