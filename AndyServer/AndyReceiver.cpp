#include "AndyReceiver.h"
#include "ui_AndyReceiver.h"

const quint16 PORT = 3333;
const qint64 LOADBYTES = 4 * 1024; // 4 kilo-byte
const int DATA_STREAM_VERSION = QDataStream::Qt_4_8;
AndyReceiver::AndyReceiver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AndyReceiver)
{
    ui->setupUi(this);

    server = new TcpServer(this);
    connect(server, SIGNAL(createNewTask(TcpSocket*)),
            this,SLOT(on_createNewTask(TcpSocket*)));
    /* 连接请求 -> 接受连接 */

   if(!server->listen(QHostAddress::Any, PORT))
    {
        qDebug() << "*** Listen to Port Failed ***" ;
        qDebug() << server->errorString();
    }
}

AndyReceiver::~AndyReceiver()
{
    delete ui;

    SafeDelete(server);
}

void AndyReceiver::on_pushButton_2_clicked()
{
    QString dir =QFileDialog::getExistingDirectory(this, tr("Open Directory"), "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    dir.append("/");
    dir.replace("/","\\");
    qDebug()<<"本地接收数据存档为："<<dir;
    receiveDir= dir;
}
/*--- 接受连接请求 ---*/
void AndyReceiver::on_createNewTask(TcpSocket* socket)
{
    AndyProgressBar *bar =new AndyProgressBar();
    connect(socket,SIGNAL(UpdatePercent(int)), bar,SLOT (on_UpdatePercent(int)));
    connect(socket,SIGNAL(UpdateMaximum(int)), bar,SLOT (on_UpdateMaximum(int)));
    connect(socket,SIGNAL(UpdateText(QString)), bar,SLOT(on_UpdateText(QString)));

    bar->SetMaxRange(100);
    bar->UpdateProgress(0);
    ui->vl_content->addWidget(bar);
}




