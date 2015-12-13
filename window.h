#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "mytcpserver.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
private slots:

    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);


    //服务端槽函数
    void ClientReadData(int clientID, const QString & IP, int Port, QByteArray data);
    void ClientConnect(int clientID, const QString & IP , int Port);
    void ClientDisConnect(int clientID, const QString & IP, int Port);
private:
    Ui::Window *ui;
};

#endif // WINDOW_H
