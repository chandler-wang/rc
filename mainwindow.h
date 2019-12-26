#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "message/messagemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initMessageThread(void);
    void cleanMessageThread(void);

private:
    Ui::MainWindow *ui;

    MessageManager *messageManager;
    QThread *messageThread;
};

#endif // MAINWINDOW_H
