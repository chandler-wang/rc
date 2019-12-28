#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "message/ithread.h"

#include <unistd.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QMap<QObject*, QThread*> *m;
//    m = new QMap<QObject*, QThread*>();
//    IThread::setMap(m);

    createThreadManager();
    connect(this,SIGNAL(managerOperation(signal_data_t*)), threadManager, SLOT(doOperation(signal_data_t*)));

    qDebug("MainWindow::MainWindow()");
}

MainWindow::~MainWindow()
{
    delete ui;

    destroyThreadManager();

    qDebug("MainWindow::~MainWindow()");
}

void MainWindow::createThreadManager(void)
{
    threadManager = new ThreadManager;
    managerThread = new QThread(this);
    threadManager->moveToThread(managerThread);

    managerThread->start();
}

void MainWindow::destroyThreadManager(void)
{
    usleep(1000*10);

    if (managerThread)
    {
        if (managerThread->isRunning())
        {
            managerThread->quit();
            managerThread->wait();
        }

        if (threadManager)
        {
            disconnect(this,SIGNAL(managerOperation(signal_data_t*)), threadManager, SLOT(doOperation(signal_data_t*)));
        }

        delete managerThread;
        managerThread = NULL;
    }

    if (threadManager)
    {
        delete threadManager;
        threadManager = NULL;
    }
}

void MainWindow::on_pushButton_clicked()
{
    signal_data_t sd;

    qDebug("MainWindow::on_pushButton_clicked");
    sd.index = 0;

    emit managerOperation(&sd);
}
