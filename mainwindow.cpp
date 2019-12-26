#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMessageThread();

    qDebug("MainWindow::MainWindow()");
}

MainWindow::~MainWindow()
{
    delete ui;

    cleanMessageThread();

    qDebug("MainWindow::~MainWindow()");
}

void MainWindow::initMessageThread(void)
{
    messageManager = new MessageManager();
    messageThread = new QThread(this);
    connect(messageThread, SIGNAL(started()), messageManager, SLOT(run()));
    messageManager->moveToThread(messageThread);
    messageThread->start();
}

void MainWindow::cleanMessageThread(void)
{
    usleep(1000*10);

    if (messageThread)
    {
        if (messageThread->isRunning())
        {
            messageThread->quit();
            messageThread->wait();
        }

        if (messageManager)
        {
            disconnect(messageThread, SIGNAL(started()), messageManager, SLOT(run()));
        }

        delete messageThread;
        messageThread = NULL;
    }

    if (messageManager)
    {
        delete messageManager;
        messageManager = NULL;
    }
}
