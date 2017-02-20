#ifndef RECEIVER_H
#define RECEIVER_H

class QUdpSocket;
class Receiver
{
public:
    Receiver(quint16 p = 45455);
    QByteArray processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    quint16 port;
};

#endif // RECEIVER_H
