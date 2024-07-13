#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();  // 显示主窗口

    return app.exec();  // 进入 Qt 应用程序的事件循环
}
