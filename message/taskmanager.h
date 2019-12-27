#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "task.h"

class TaskManager : public ITask
{
public:
    TaskManager();

public:
    void create();
    void destory();
};

#endif // TASKMANAGER_H
