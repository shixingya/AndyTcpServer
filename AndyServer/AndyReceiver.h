#pragma once
#include "preheader.h"
#include "./QProgressIndicator/AndyProgressBar.h"
#include "./TaskManager.h"
#include "tcpserver.h"
extern QString _saveDir;
namespace Ui {
class AndyReceiver;
}



class AndyReceiver : public QWidget
{
    Q_OBJECT

public:
    explicit AndyReceiver(QWidget *parent = 0);
    ~AndyReceiver();

private slots:
    void on_pushButton_2_clicked();
    void on_createNewTask(TcpSocket*);
private:
    Ui::AndyReceiver *ui;
    TcpServer *server=nullptr;
    QString receiveDir ="D:\\";
};
