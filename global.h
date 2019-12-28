#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QVector>

#define FAIL -1
#define OK 0

typedef struct SignalData
{
    int index; // 动作编号
    QVector<float> value;
    QVector<QObject*> obj;
}signal_data_t;

#endif // GLOBAL_H
