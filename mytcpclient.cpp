#include "mytcpclient.h"
#include "myhelper.h"
#include <QHostAddress>

MyTcpClient::MyTcpClient(QObject * parent, int ClientID)
    :   QTcpSocket(parent)
{
    this->cliendID = ClientID;
    connect(this, SIGNAL(readyRead()), this, SLOT(onClientReadData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(onClientDisConnect()));
}


void MyTcpClient::onClientReadData()
{
    MyHelper::Sleep(100);
    QByteArray data = this->readAll();
    emit ClientReadData(this->cliendID, this->peerAddress().toString(), this->peerPort(), data);
}


void MyTcpClient::onClientDisConnect()
{
    emit this->ClientDisConnect(this->cliendID, this->peerAddress(), this->peerPort());
}

