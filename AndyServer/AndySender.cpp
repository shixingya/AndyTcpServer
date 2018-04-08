#include "AndySender.h"
#include "ui_AndySender.h"
#include "TaskManager.h"
#include "TaskRunner.h"
#include "../AndyServer/QProgressIndicator/AndyProgressBar.h"
AndySender::AndySender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AndySender)
{
    ui->setupUi(this);
}

AndySender::~AndySender()
{
    delete ui;
}

void AndySender::on_pbt_selectFile_clicked()
{
    QFileDialog fileDialog(this);

    //设置窗口的标题
    fileDialog.setWindowTitle("选择要发送的文件");
    fileDialog.setNameFilter("所有文件(*.*)"); //设置一个过滤器
    //这个标志用来设置选择的类型，比如默认是单个文件。QFileDialog::ExistingFiles 多个文件,还可以用来选择文件夹QFileDialog::Directory。QFileDialog::ExistingFile 单个文件。注意这个ExistingFile，单词后面多了一个s 表示选择多个文件。要看清楚了。
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    //弹出对话框
    if (fileDialog.exec() == QDialog::Accepted)
    {

        TaskManager *manager =TaskManager::getInstance();
        //strPathList  返回值是一个list，如果是单个文件选择的话，只要取出第一个来就行了。
        QStringList strPathList = fileDialog.selectedFiles();
        foreach(QString path , strPathList)
        {
            qDebug()<<"添加文件上传任务："<<path;
            AndyProgressBar * progressBar =new AndyProgressBar();
            TaskRunner * runner =new TaskRunner;
            QString hostIp =ui->lineEdit->text();
            if(hostIp=="")
            {
                hostIp ="127.0.0.1";
            }
            runner->setHostIp(hostIp);
            runner->setTask(path,TaskRunner::uploadFile);
            connect(runner,SIGNAL(taskFinish(void*)),runner,SLOT(deleteLater()));
            connect(runner,SIGNAL(UpdatePercent(int)), progressBar,SLOT (on_UpdatePercent(int)));
            connect(runner,SIGNAL(UpdateMaximum(int)), progressBar,SLOT (on_UpdateMaximum(int)));
            connect(runner,SIGNAL(UpdateText(QString)), progressBar,SLOT(on_UpdateText(QString)));

            progressBar->SetMaxRange(100);
            progressBar->SetFileName(path.split("/").last());
            ui->vl_content->addWidget(progressBar);
            manager->addTask(runner);
        }
    }
}
void AndySender::on_UpdatePercent()
{

}
