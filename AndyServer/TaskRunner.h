#pragma once
#include "preheader.h"

class TaskRunner : public QObject
{
    Q_OBJECT

public:
    explicit TaskRunner();
    ~TaskRunner();
    enum TaskType
    {
        uploadFile,
        downloadFile
    };
    void setTask(QString path,TaskType type);
    void setHostIp(QString ip);
signals:
    void taskFinish(void*);
    void UpdateText(QString);
    void UpdatePercent(int);
    void UpdateMaximum(int);
public slots:
    void on_DoRequest();
private slots:
    void start_transfer();
    void continue_transfer(qint64);
    void show_error(QAbstractSocket::SocketError);

private:
    QString _ip ="";
    QTcpSocket *send=nullptr;
    QFile *file=nullptr;
    TaskType type;
    QString fileName;
    /* 总数据大小，已发送数据大小，剩余数据大小，每次发送数据块大小 */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;




};
