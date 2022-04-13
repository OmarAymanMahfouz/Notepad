#include "container.h"


std::vector<MainWindow*> genaricClass::windowsGenerated = std::vector<MainWindow*>(0);


genaricClass::~genaricClass(){
}

QString genaricClass::getFileName(QString &s){
    QString fileName = "";
    bool flag = false;
    for(int i = s.size() - 1; i >= 0; i--)
        if(s[i] == '/')
            break;
        else if (s[i] == '.' && !flag)
            flag = true;
        else if (flag)
            fileName.append(s[i]);

    std::reverse(fileName.begin(), fileName.end());
    return fileName;
}

std::pair<bool, QString> genaricClass::saveFile(QString &text, QWidget *e){
    QString filter = "Text File (*.txt) ;; All Files (*.*)";
    QString fileName= QFileDialog::getSaveFileName(e, "Save As", QDir::homePath(), filter);
    QFile file(fileName);
    QTextStream out(&file);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        out << text;
        file.flush();
        file.close();
        return std::make_pair(true, fileName);
    }
    return std::make_pair(false, "");
}

bool genaricClass::saveFile(QString &text, QString &path, QWidget *e){
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

std::pair<bool, std::pair<QString, QString>> genaricClass::openFile(QWidget *e){
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

void genaricClass::generateNewWindow(){
    MainWindow *w = new MainWindow(nullptr, genaricClass::windowsGenerated.size() + 1);
    w->show();
    genaricClass::windowsGenerated.push_back(w);
}

void genaricClass::deleteWindow(int frameNumber){
    int idx = -1;
    for (int i = 0; i < genaricClass::windowsGenerated.size(); i++){
        if(genaricClass::windowsGenerated[i]->frameNumber == frameNumber){
            delete genaricClass::windowsGenerated[i];
            idx = i;
            break;
        }
    }
    if(idx != -1)
        genaricClass::windowsGenerated.erase(genaricClass::windowsGenerated.begin() + idx);
}

bool genaricClass::textchanged(QString &curText, QString &path){
    if(path.isEmpty() && curText.isEmpty())
        return false;
    else if(!path.isEmpty()){
        QFile file(path);
        QTextStream in(&file);
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QString text = in.readAll();
            file.close();
            if(curText == text)
                return false;
        }
    }
    return true;
}
