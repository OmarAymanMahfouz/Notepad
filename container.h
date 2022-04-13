#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <mainwindow.h>
#include <algorithm>
#include <vector>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <algorithm>
#include <QTextStream>
#include <QDebug>

class windowController{
public:
    static void generateNewWindow();
    static void deleteWindow(int frameNumber);
    static std::vector<MainWindow*> windowsGenerated;
};

class saveClass{
public:
    static std::pair<bool, QString> saveFile(QString &text, QWidget *e);
    static bool saveFile(QString &text, QString &bath, QWidget *e);
};

class openClass{
public:
    static std::pair<bool, std::pair<QString, QString>> openFile(QWidget *e);
};


#endif // CONTAINER_H
