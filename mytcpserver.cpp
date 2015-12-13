#include "mytcpserver.h"
#include <QHostAddress>

myTcpServer::myTcpServer(QObject * parent):
QTcpServer(parent)
{
    this->clientCount = 0;
}

void myTcpServer::incomingConnection(int handle)
{
    MyTcpClient * client = new MyTcpClient(this, handle);
    client->setSocketDescriptor(handle);

    connect(client, SIGNAL(ClientReadData(int,QString,int,QByteArray)), this, SIGNAL(ClientReadData(int,QString,int,QByteArray)));
    connect(client, SIGNAL(ClientDisConnect(int,QString,int)), this, SLOT(DisConnect(int,QString,int)));
    emit ClientConnect(handle, client->peerAddress().toString(), client->peerPort());

    clientLists.append(client);
    clientID.append(handle);
    clientCount++;

    currentClient = client;
}

void myTcpServer::DisConnect(int clientID, QString IP, int Port)
{
    for(int i = 0; i < clientCount; ++i){
        if(clientID[i] == clientID){
            clientLists.removeAt(i);
            clientID.removeAt(i);
            clientCount--;
            i--;//否则无法移除中间的链接
            emit CLientDisConnect(clientID, IP, Port);
            break;
        }
    }
}

//指定客户端链接
void myTcpServer::SendData(int clientID, QByteArray data)
{
    for(int i = 0; i < clientCount; ++i){
        if(this->clientID[i] == clientID){
            clientLists[i]->write(data);
            break;
        }
    }
}


//对当前的链接发送数据
void myTcpServer::SendDataCurrent(QByteArray data)
{
    if(clientCount < 1)
        return;
    currentClient->write(data);
}


//对所有的链接发送数据
void myTcpServer::SendDataAll(QByteArray data)
{
    for(auto client : clientLists){
        client->write(data);
    }
}

//关闭所有的链接
void myTcpServer::CloseAllClient()
{
    for(auto client : clientLists){
        client->close();
        i--;//记得减去1,否则永远只会断开第一个链接
    }
}

