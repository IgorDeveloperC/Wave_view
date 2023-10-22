#include "datalistener.h"

DataListener::DataListener(QObject *parent) : QObject(parent), udpSocket(new QUdpSocket(this))
{
    udpSocket->bind(QHostAddress("127.0.0.1"), 10002, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

DataListener::~DataListener()
{

}

void DataListener::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        //qDebug("Received datagram: \"%s\"", datagram.data());
        if(datagram.size()!=8192)
        {
            qWarning() << "Invalid datagram size";
            continue; // Skip this datagram
        }

        QVector<double> Array;
        const int16_t* buffer = reinterpret_cast<const int16_t*>(datagram.constData());

        for (int i = 0; i < datagram.size() / sizeof(int16_t); ++i)
        {
            Array.append(buffer[i]);
        }

        if (callback) {
            callback(Array);
        }

    }
}
void DataListener::setCallback(const DataReceivedCallback& newCallback)
{
    callback = newCallback;
}

