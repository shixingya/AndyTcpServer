#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QDebug>
extern QString _saveDir;
const quint16 PORT = 3333;
const qint64 LOADBYTES = 4 * 1024; // 4 kilo-byte
const int DATA_STREAM_VERSION = QDataStream::Qt_4_8;
TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);
    connect(this,&TcpSocket::readyRead,this,&TcpSocket::readData);
    connect(this,SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(receive_error(QAbstractSocket::SocketError)));

    emit UpdateText("开始接收数据!") ;
    receive_gotBytes=0;
}

TcpSocket::~TcpSocket()
{
}

/*--- 出错处理 ---*/
void TcpSocket::receive_error(QAbstractSocket::SocketError)
{
    qDebug()  << "*** Socket Error ***"   << this->errorString();
    this->close(); // 关cocket

    receive_fileName.clear(); // 清空文件名
    receive_fileBytes = receive_gotBytes = receive_nameSize = 0;
    emit UpdateText("接收数据失败!") ;

    SafeDelete(receive_file);
}
void TcpSocket::readData()
{
    QDataStream in(this);
    in.setVersion(DATA_STREAM_VERSION);


    /* 首部未接收/未接收完 */
    if(receive_gotBytes <= 2 * sizeof(qint64))
    {
        if(!receive_nameSize) // 前两个长度字段未接收
        {
            if(this->bytesAvailable() >= 2 * sizeof(qint64))
            {
                in >> receive_fileBytes >> receive_nameSize;
                receive_gotBytes += 2 * sizeof(qint64);
                emit UpdateMaximum(receive_fileBytes);
                emit UpdatePercent(receive_gotBytes);
            }
            else // 数据不足，等下次
            {
                qDebug()<<" 数据不足文件名长度，等下次 Errir 044";
                return;
            }
        }
        else if(this->bytesAvailable() > receive_nameSize)
        {
            in >> receive_fileName;
            receive_gotBytes += receive_nameSize;
            emit UpdatePercent(receive_gotBytes);
            qDebug()<< "--- File Name: "
                    << receive_fileName;
        }
        else // 数据不足文件名长度，等下次
        {
            qDebug()<<" 数据不足文件名长度，等下次 Errir 046";
            return;
        }
    }

    /* 已读文件名、文件未打开 -> 尝试打开文件 */
    if(!receive_fileName.isEmpty() && receive_file == Q_NULLPTR)
    {
        QString saveFilePath =_saveDir+(receive_fileName);
        qDebug()<<_saveDir<<"保存路径为 ："<< saveFilePath;
        receive_file = new QFile(saveFilePath);
        if(!receive_file->open(QFile::WriteOnly)) // 打开失败
        {
            qDebug() << "*** File Open Failed ***"  ;
            SafeDelete(receive_file);
            return;
        }
        emit UpdateText(QString("文件%1打开成功!").arg(saveFilePath)) ;
    }
    if(receive_file == Q_NULLPTR) // 文件未打开，不能进行后续操作
        return;

    if(receive_gotBytes < receive_fileBytes) // 文件未接收完
    {
        receive_gotBytes += this->bytesAvailable();
        emit UpdatePercent(receive_gotBytes);
        receive_file->write(this->readAll());
    }
    if(receive_gotBytes == receive_fileBytes) // 文件接收完
    {
        this->close(); // 关socket
        receive_file->close(); // 关文件
        SafeDelete(receive_file);
        emit UpdatePercent(receive_gotBytes);
        emit UpdateText("文件接收完成!") ;
    }
}
