#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint); // 禁止移动
    w.showMaximized();
    w.setWindowTitle("=== Boat System ===");

    w.show();

    return a.exec();
}
