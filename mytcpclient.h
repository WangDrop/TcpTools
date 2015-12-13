#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H
#include <QTcpSocket>


class MyTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit  MyTcpClient(int clientID = 0, QObject * parent = 0);
private:
    int cliendID;
signals:
    void ClientReadData(int clientID, QString IP, int Port, QByteArray Data);
    void ClientDisConnect(int clientID, QString IP, int Port);
private slots:
    void onClientReadData();
    void onClientDisConnect();
};

#endif // MYTCPCLIENT_H
