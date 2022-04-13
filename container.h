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

class genaricClass{
public:
    static std::pair<bool, QString> saveFile(QString &text, QWidget *e);
    static bool saveFile(QString &text, QString &bath, QWidget *e);
    static std::pair<bool, std::pair<QString, QString>> openFile(QWidget *e);
    static void generateNewWindow();
    static void deleteWindow(int frameNumber);
    static std::vector<MainWindow*> windowsGenerated;
    static QString getFileName(QString &s);
    ~genaricClass();
};


#endif // CONTAINER_H
