#ifndef ITHREAD_H
#define ITHREAD_H

#include <QThread>
#include <QMap>

//QT容器类（三） 之 QMap、QHash
//https://blog.csdn.net/hustyangju/article/details/17756907

class IThread{

public:
    IThread();
    ~IThread();

    static void addToMap(QObject* obj, QThread* qthread);
    static QMap<QObject*, QThread*> *getMap(void);

private:
    static QMap<QObject*, QThread*> *map;
};

#endif // ITHREAD_H
