#include "mainwindow.h"
#include "container.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    windowController::generateNewWindow();
    return a.exec();
}
