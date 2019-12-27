#ifndef TASK_H
#define TASK_H

class ITask
{
public:
    virtual ~ITask();

    virtual void create()=0;
    virtual void destory()=0;
};

ITask::~ITask()
{}

#endif // TASK_H
