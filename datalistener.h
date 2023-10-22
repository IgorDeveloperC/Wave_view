#pragma once
#ifndef DATALISTENER_H
#define DATALISTENER_H

#include <QObject>
#include<QtNetwork/QUdpSocket>
#include <functional>



class DataListener : public QObject
{
    Q_OBJECT

public:
    typedef std::function<void(const QVector<double>&)> DataReceivedCallback;
    // Constructor
    explicit DataListener(QObject *parent = nullptr);

    // Destructor
    ~DataListener();
    void setCallback(const DataReceivedCallback& callback);

private slots:
    // Slot to read incoming UDP datagrams
    void readPendingDatagrams();

private:
    // QUdpSocket object for listening to UDP datagrams
    QUdpSocket* udpSocket;
    DataReceivedCallback callback;

};

#endif // DATALISTENER_H
