#include "TaskManager.h"
#include "TaskRunner.h"

const int MaxThreadCount =30;
TaskManager* TaskManager::m_instance = NULL;
TaskManager::TaskManager()
{
    auto initThreadList=[&]()
    {
        for(int i=0; i<MaxThreadCount; i++)
        {
            QThread *thread =new QThread(this);
            thread->start();
            _threadList.push_back(thread);
        }
    };
    initThreadList();
    QTimer *timer=new QTimer();
    connect(timer,SIGNAL(timeout()), this,SLOT(on_CircleTaskList()));
    timer->start(200);

}

TaskManager::~TaskManager()
{

}

TaskManager* TaskManager::getInstance()
{
    if(m_instance == NULL)
        m_instance = new TaskManager();
    return m_instance;
}
void TaskManager::addTask(TaskRunner* runner)
{
    _waittingTasks.push_front(runner);
}
void TaskManager::on_CircleTaskList()
{
    auto circleTaskList =[&](QList<TaskRunner*>& _waitTasks,  QList<QThread*> &threadList , QMap<QThread*,TaskRunner*> &runningTasks )
    {
        while(_waitTasks.count()>0 && runningTasks.count() <threadList.count())
        {

            TaskRunner* runner = _waitTasks.takeFirst();
            if(runner)
            {
                for(int i=0; i<threadList.count(); i++)
                {
                    QThread* thread =threadList[i];
                    if(runningTasks.contains(thread))
                        continue;
                    else
                    {
                        runner->moveToThread(thread);
                        connect(runner, SIGNAL(taskFinish(void*)), this,SLOT(onUpdateTaskList()));
                        runningTasks.insert(thread,runner);
                        QTimer::singleShot(0,runner, &TaskRunner::on_DoRequest);
                        break;
                    }
                }

            }
        }
    } ;
    circleTaskList(_waittingTasks,_threadList,_runningTasks);
}
void TaskManager::onUpdateTaskList()
{
    TaskRunner * runner =(TaskRunner*)sender();

    if(runner)
    {
        for(auto itr =_runningTasks.begin(); itr !=_runningTasks.end(); itr++)
        {
            if(itr.value() ==runner)
            {
                _runningTasks.erase(itr++);
                break;
            }
        }
        runner->deleteLater();
    }
}
