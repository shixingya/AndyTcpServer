#pragma once
#include "preheader.h"


class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = 0);
    ~TcpSocket();
    QByteArray handleData(QByteArray data,const QString & ip, qint16 port);//用来处理数据的函数

signals:
    void UpdateText(QString);
    void UpdateMaximum(int);
    void UpdatePercent(int);
    //void readData(const int,const QString &,const quint16,const QByteArray &);
    void sockDisConnect(const int ,const QString &,const quint16, QThread *);//NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的
public slots:
//    void sentData(const QByteArray & ,const int);//发送信号的槽
//    void disConTcp(int i);

protected slots:
    void readData();//接收数据
     void receive_error(QAbstractSocket::SocketError);
protected:
    QFutureWatcher<QByteArray> watcher;
    QQueue<QByteArray> datas;

    QString receive_fileName="";
    QFile *receive_file=nullptr;
    /* 已接受数据，总数据，文件名长度 */
    qint64 receive_gotBytes=0, receive_fileBytes=0, receive_nameSize=0;

private:
    qintptr socketID;
    QMetaObject::Connection dis;
};
