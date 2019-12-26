#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug("Hello, boat");


    messageManager = new MessageManager();
    messageThread = new QThread(this);
    messageManager->moveToThread(messageThread);
}

MainWindow::~MainWindow()
{
    delete ui;
}
