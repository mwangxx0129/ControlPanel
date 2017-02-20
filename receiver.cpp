#include <QUdpSocket>
#include "receiver.h"

Receiver::Receiver(quint16 p)
    :port(p)
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(port, QUdpSocket::ShareAddress);
}

QByteArray Receiver::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) { // TODO using if?
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    }
    return datagram;
}
