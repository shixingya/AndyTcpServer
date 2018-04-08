#pragma once
#include "preheader.h"

class TaskRunner;
class TaskManager : public QObject
{
    Q_OBJECT

public:
    static TaskManager* getInstance();


    void addTask(TaskRunner*);
private:
    TaskManager();
    ~TaskManager();
    static TaskManager *m_instance;

    QList<QThread*> _threadList;
    QList<TaskRunner*> _waittingTasks; //等待中的任务
    QMap<QThread*,TaskRunner*> _runningTasks; //进行中的任务


private slots:
    void onUpdateTaskList();
    void on_CircleTaskList();
};
