#include "TaskRunner.h"
const quint16 PORT = 3333;
const qint64 LOADBYTES = 4 * 1024; // 4 kilo-byte
const int DATA_STREAM_VERSION = QDataStream::Qt_4_8;
TaskRunner::TaskRunner()
{
    send = new QTcpSocket(this);
    fileBytes = sentBytes = restBytes = 0;
    loadBytes = LOADBYTES;
    /* 连接已建立 -> 开始发数据 */
    connect(send, SIGNAL(connected()),
            this, SLOT(start_transfer()));
    /* 数据已发出 -> 继续发 */
    connect(send, SIGNAL(bytesWritten(qint64)),
            this, SLOT(continue_transfer(qint64)));
    /* socket出错 -> 错误处理 */
    connect(send, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(show_error(QAbstractSocket::SocketError)));
}

TaskRunner::~TaskRunner()
{
    SafeDelete(send);
}

void TaskRunner::setHostIp(QString ip)
{
    _ip =ip;
}
void TaskRunner::on_DoRequest()
{
    if(type ==uploadFile)
    {
        // 建立连接 tcp
        send->connectToHost(QHostAddress(_ip), PORT);
        if(send->waitForConnected(1000))
        {
            qDebug()<<"连接服务器成功！";

            sentBytes = 0;
        }

    }
}
void TaskRunner::setTask(QString path,TaskType _type)
{
    fileName =path;
    type =_type;
    emit UpdateText("任务等待中");
}
/*--- 开始传送 ---*/
void TaskRunner::start_transfer()
{
    file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly))
    {
        emit UpdatePercent(0);
        emit UpdateText("文件打开失败");
        qDebug() << "*** start_transfer(): File-Open-Error";
        return;
    }

    fileBytes = file->size();
    emit UpdatePercent(0);
    emit UpdateText("连接已经建立");

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out.setVersion(DATA_STREAM_VERSION);

    /* 无路径文件名 */
    QString sfName = fileName.right(fileName.size() -
                                    fileName.lastIndexOf('/') - 1);
    /* 首部 = 总大小 + 文件名长度 + 文件名 */
    out << qint64(0) << qint64(0) << sfName;
    /* 总大小加上首部的大小 */
    fileBytes += buf.size();
    emit UpdateMaximum(fileBytes);
    /* 重写首部的前两个长度字段 */
    out.device()->seek(0);
    out << fileBytes << (qint64(buf.size()) - 2 * sizeof(qint64));
    /* 发送首部，计算剩余大小 */
    restBytes = fileBytes - send->write(buf);
}

/*--- 继续传输 ---*/
void TaskRunner::continue_transfer(qint64 sentSize)
{
    sentBytes += sentSize;
    emit UpdatePercent(sentBytes);
    /* 还有数据要发 */
    if(restBytes > 0)
    {
        /* 从文件读数据 */
        QByteArray buf = file->read(qMin(loadBytes, restBytes));
        /* 发送 */
        restBytes -= send->write(buf);
    }
    else
        file->close();
    /* 全部发送完 */
    if(sentBytes == fileBytes)
    {
        send->close(); // 关socket
        fileName.clear(); // 清空文件名
        emit UpdateText("发送完成");
        emit taskFinish(nullptr);
    }
}

/*--- 出错处理 ---*/
void TaskRunner::show_error(QAbstractSocket::SocketError)
{
    qDebug() << "*** Socket Error";
    send->close();
    UpdateText("任务失败，稍后重试！");
    UpdatePercent(0);
    fileName.clear();
    emit taskFinish(nullptr);
}





