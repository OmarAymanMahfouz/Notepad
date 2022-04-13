#include "container.h"


std::vector<MainWindow*> windowController::windowsGenerated = std::vector<MainWindow*>(0);


std::pair<bool, QString> saveClass::saveFile(QString &text, QWidget *e){
    QString filter = "Text File (*.txt) ;; All Files (*.*)";
    QString fileName= QFileDialog::getSaveFileName(e, "Save As", QDir::homePath(), filter);
    bool saveStatus = saveClass::saveFile(text, fileName, e);
    if(saveStatus)
        return std::make_pair(true, fileName);
    return std::make_pair(false, "");
}


bool saveClass::saveFile(QString &text, QString &path, QWidget *e){
    QFile file(path);
    QTextStream out(&file);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        out << text;
        file.flush();
        file.close();
        return true;
    }
    return false;
}


std::pair<bool, std::pair<QString, QString>> openClass::openFile(QWidget *e){
    QString text = "";
    QString filter = "Text File (*.txt) ;; All Files (*.*)";
    QString fileName= QFileDialog::getOpenFileName(e, "Open", QDir::homePath(), filter);
    QFile file(fileName);
    QTextStream in(&file);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        text = in.readAll();
        file.close();
        return std::make_pair(true, std::make_pair(fileName, text));
    }
    return std::make_pair(false, std::make_pair("", ""));
}


void windowController::generateNewWindow(){
    MainWindow *w = new MainWindow(nullptr, windowController::windowsGenerated.size() + 1);
    w->show();
    windowController::windowsGenerated.push_back(w);
}


void windowController::deleteWindow(int frameNumber){
    int idx = -1;
    for (int i = 0; i < windowController::windowsGenerated.size(); i++){
        if(windowController::windowsGenerated[i]->frameNumber == frameNumber){
            delete windowController::windowsGenerated[i];
            idx = i;
            break;
        }
    }
    if(idx != -1)
        windowController::windowsGenerated.erase(windowController::windowsGenerated.begin() + idx);
}
