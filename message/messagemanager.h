#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>

class MessageManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageManager();
    ~MessageManager();

signals:

public slots:
    void run();
    void handleMessage(int value);
};

#endif // MESSAGEMANAGER_H
