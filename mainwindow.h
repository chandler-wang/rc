#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "message/threadmanager.h"

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

signals:
    void managerOperation(signal_data_t*);

private:
    void createThreadManager(void);
    void destroyThreadManager(void);

private:
    Ui::MainWindow *ui;

    ThreadManager *threadManager;
    QThread *managerThread;

};

#endif // MAINWINDOW_H
