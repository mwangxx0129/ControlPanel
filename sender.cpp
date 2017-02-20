#include <QUdpSocket>
#include "sender.h"

Sender::Sender(quint16 p)
    :port(p)
{
    udpSocket = new QUdpSocket();
    TEST_messageNo = 1;
}

//"1,2,3"
void Sender::broadcastDatagram(QString message)
{
    //Encode
    QByteArray datagram = "Header:Broadcast message\n"
            + QByteArray::number(TEST_messageNo);
    datagram.append("\nbody:"+message);

    //Send
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, port);
    //Count message only for test
    TEST_messageNo++;
}
