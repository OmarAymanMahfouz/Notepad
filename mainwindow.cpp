#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "container.h"

MainWindow::MainWindow(QWidget *parent, int frameNumber)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , frameNumber(frameNumber)
    , fileName("Untitled")
    , currentPath("")
    , currentZoom(100)
    , findWindow(nullptr)
    , initialText("")
{
    ui->setupUi(this);

    //Set Window Before Start
    QPixmap pix(":/resources/img/icon-1.png");
    this->setWindowTitle(this->fileName + " - Notepad");
    this->setWindowIcon(pix.scaled(50, 50, Qt::KeepAspectRatio));
    this->setCentralWidget(ui->plainTextEdit);
    ui->statusbar->addPermanentWidget(ui->label, 4);
    ui->statusbar->addPermanentWidget(ui->lineCol,2);
    ui->statusbar->addPermanentWidget(ui->zoomSize,1);
    ui->statusbar->addPermanentWidget(ui->UTF_8,1);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionFind->setEnabled(false);

    //Control KeyBoards Shortcuts
    this->save = new QShortcut(QKeySequence("Ctrl+S"), this);
    QObject::connect(this->save, SIGNAL(activated()), this, SLOT(on_actionSave_triggered()));
    this->copy = new QShortcut(QKeySequence("Ctrl+C"), this);
    QObject::connect(this->copy, SIGNAL(activated()), this, SLOT(on_actionCopy_triggered()));
    this->cut = new QShortcut(QKeySequence("Ctrl+X"), this);
    QObject::connect(this->cut, SIGNAL(activated()), this, SLOT(on_actionCut_triggered()));
    this->paste = new QShortcut(QKeySequence("Ctrl+V"), this);
    QObject::connect(this->paste, SIGNAL(activated()), this, SLOT(on_actionPaste_triggered()));
    this->selectAll = new QShortcut(QKeySequence("Ctrl+A"), this);
    QObject::connect(this->selectAll, SIGNAL(activated()), this, SLOT(on_actionSelect_All_triggered()));
    this->undo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QObject::connect(this->undo, SIGNAL(activated()), this, SLOT(on_actionUndo_triggered()));
    this->redo = new QShortcut(QKeySequence("Ctrl+Y"), this);
    QObject::connect(this->redo, SIGNAL(activated()), this, SLOT(on_actionRedo_triggered()));
    this->newWindow = new QShortcut(QKeySequence("Ctrl+N"), this);
    QObject::connect(this->newWindow, SIGNAL(activated()), this, SLOT(on_actionNewWindow_triggered()));
    this->find = new QShortcut(QKeySequence("Ctrl+F"), this);
    QObject::connect(this->find, SIGNAL(activated()), this, SLOT(on_actionFind_triggered()));
    QObject::connect(ui->plainTextEdit, SIGNAL(clicked()), this, SLOT(on_plainTextEdit_cursorPositionChanged()));
}


MainWindow::~MainWindow()
{
   // if(this->findWindow)
        this->findWindow->close();
    delete this->ui;
    delete this->findWindow;
    delete this->copy;
    delete this->cut;
    delete this->paste;
    delete this->save;
    delete this->find;
    delete this->newWindow;
    delete this->selectAll;
    delete this->undo;
    delete this->redo;
    this->ui = nullptr;
    this->findWindow = nullptr;
    this->copy = this->cut = this->paste = this->save = this->find =
                 this->newWindow = this->selectAll = this->undo =
                 this->redo = nullptr;

    genaricClass::deleteWindow(this->frameNumber);
}

//done
void MainWindow::closeEvent(QCloseEvent *event){
    if(windowShouldCLose())
        event->accept();
    else
        event->ignore();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->plainTextEdit && event->type() == QEvent::Wheel){
        QWheelEvent *wheel = static_cast<QWheelEvent*>(event);
        if(wheel->modifiers() == Qt::ControlModifier){
            this->manageWheelEvent(wheel);
            return true;
        }
    }
    else if (event->type() == QEvent::KeyRelease){
        QKeyEvent *key = static_cast<QKeyEvent*>(event);
        //right Arrow  + 3 = 16777234 + 3

        if(key->key() >= 16777234 && key->key() <= 16777237){
            this->on_plainTextEdit_cursorPositionChanged();
            return true;
        }
    }
//    else if (event->type() == QEvent::MouseButtonPress){
//        qDebug() <<"Iam here";
//        QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
//        if(mouse->button() == Qt::LeftButton){
//            this->on_plainTextEdit_cursorPositionChanged();
//            return true;
//        }
//    }

    return QObject::eventFilter(obj, event);
}

//done
void MainWindow::wheelEvent(QWheelEvent *event){
    this->eventFilter(ui->plainTextEdit, event);
}

//done
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    this->eventFilter(nullptr, event);
}

//done
void MainWindow::manageWheelEvent(QWheelEvent *event){
    QPoint degrees = event->angleDelta() / (8 * 15);
    int scale = degrees.y();
    if(scale > 0){
        this->on_actionZoom_in_triggered();
    }
    else if (scale < 0){
        this->on_actionZoom_out_triggered();
    }
}

//done
bool MainWindow::windowShouldCLose(){
    QString text = ui->plainTextEdit->toPlainText();
    if(this->initialText == ui->plainTextEdit->toPlainText())
        return true;

    QMessageBox dialog;
    dialog.setWindowTitle("Notepad");
    dialog.setWindowIcon(QPixmap(":/resources/img/icon-1.png"));
    QString dialogText;
    if(this->currentPath.isEmpty())
        dialogText = "<font style=\"color:darkblue; font-size:15px\">Do you want to save changes to " + this->fileName + "?<br>       \n </font>";
    else
        dialogText = "<font style=\"color:darkblue; font-size:15px\">Do you want to save changes to " + this->currentPath + "?<br>       \n </font>";

    dialog.setText(dialogText);
    dialog.setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::CustomizeWindowHint
                          | Qt::WindowCloseButtonHint);
    dialog.setIcon(QMessageBox::NoIcon);

    QPushButton *save = dialog.addButton(tr("Save"), QMessageBox::ActionRole);
    QPushButton *dontSave = dialog.addButton(tr("     Don't Save     "), QMessageBox::ActionRole);
    QPushButton *cancel = dialog.addButton(tr("Cancel"), QMessageBox::ActionRole);

    dialog.exec();
    if(dialog.clickedButton() == save){
        bool flag = this->saveRole();
        delete save;
        delete dontSave;
        delete cancel;
        return flag;
    }
    else if (dialog.clickedButton() == dontSave){

        delete save;
        delete dontSave;
        delete cancel;
        return true;
    }
    else{
        delete save;
        delete dontSave;
        delete cancel;
        return false;
    }
}

//done
bool MainWindow::saveRole(){
    QString text = ui->plainTextEdit->toPlainText();
    if (this->currentPath == ""){
        std::pair<bool, QString> closeCurWindow = genaricClass::saveFile(text, this);
        if(closeCurWindow.first){
            return true;
        }
    }
    else{
        bool flag = genaricClass::saveFile(text, this->currentPath, this);
        if(flag)
            return true;
    }
    return false;
}

//done
void MainWindow::on_actionStatus_Bar_triggered()
{
    if(ui->actionStatus_Bar->isChecked())
        ui->statusbar->hide();
    else
        ui->statusbar->show();
}

//done
void MainWindow::on_actionExit_triggered()
{
    bool flag =  this->windowShouldCLose();
    if(flag)
        this->close();
}

//done
void MainWindow::on_actionSave_As_triggered()
{
    QString text = ui->plainTextEdit->toPlainText();
    std::pair<bool, QString> isSaved = genaricClass::saveFile(text, this);
    if (isSaved.first){
        this->currentPath = isSaved.second;
        this->fileName = genaricClass::getFileName(this->currentPath);
        this->setWindowTitle(this->fileName + " - Notepad");
    }
}

//done
void MainWindow::on_actionSave_triggered()
{
    QString text = ui->plainTextEdit->toPlainText();
    if(this->currentPath.isEmpty()){
        std::pair<bool, QString> flag = genaricClass::saveFile(text, this);
        if(flag.first){
            this->currentPath = flag.second;
            this->fileName = genaricClass::getFileName(this->currentPath);
            this->setWindowTitle(this->fileName + " - Notepad");
        }
    }
    else
        genaricClass::saveFile(text, this->currentPath, this);
}

//done
void MainWindow::on_actionNew_triggered()
{
    bool flag = this->windowShouldCLose();
    if (flag){
        genaricClass::generateNewWindow();
        this->close();
    }
}

//done
void MainWindow::on_actionOpen_triggered()
{
    bool flag = this->windowShouldCLose();
    if(flag){
        std::pair<bool, std::pair<QString, QString>> state = genaricClass::openFile(this);
        if(!state.first)
            return;
        this->currentPath = state.second.first;
        this->fileName = genaricClass::getFileName(this->currentPath);
        this->initialText = state.second.second;
        ui->plainTextEdit->setPlainText(state.second.second);
        this->setWindowTitle(this->fileName + " - Notepad");
    }
}

//done
void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}

//done
void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

//done
void MainWindow::on_actionCut_triggered()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    if(cursor.hasSelection())
        ui->plainTextEdit->cut();
}

//done
void MainWindow::on_actionCopy_triggered()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    if(cursor.hasSelection())
        ui->plainTextEdit->copy();
}

//done
void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}

//done
void MainWindow::on_actionDelete_triggered()
{
    ui->plainTextEdit->clear();
}

//done
void MainWindow::on_plainTextEdit_textChanged()
{
    QString text = ui->plainTextEdit->toPlainText();
    if(this->currentPath.isEmpty()){
       if(text.isEmpty()){
           this->setWindowTitle(this->fileName + " - Notepad");
           ui->actionFind->setEnabled(false);
       }
       else{
           this->setWindowTitle("*" + this->fileName + " - Notepad");
           ui->actionFind->setEnabled(true);
       }
    }
    else{
        if(this->initialText == text){
            this->setWindowTitle(this->fileName +  " - Notepad");
            if(text.isEmpty())
                ui->actionFind->setEnabled(false);
            else
                ui->actionFind->setEnabled(true);
        }
        else{
            this->setWindowTitle("*" + this->fileName +  " - Notepad");
            if(text.isEmpty())
                ui->actionFind->setEnabled(false);
            else
                ui->actionFind->setEnabled(true);
        }
    }
}


void MainWindow::on_actionFind_triggered()
{
    if(!this->findWindow){
        this->findWindow = new findDialog();
        this->findWindow->plainText = ui->plainTextEdit;
        this->findWindow->show();
    }
}

//done
void MainWindow::on_plainTextEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    if(cursor.hasSelection()){
        ui->actionCopy->setEnabled(true);
        ui->actionCut->setEnabled(true);
        ui->actionDelete->setEnabled(true);
    }
    else{
        ui->actionCopy->setEnabled(false);
        ui->actionCut->setEnabled(false);
        ui->actionDelete->setEnabled(false);
    }
    int line = cursor.blockNumber() + 1;
    int col = cursor.positionInBlock() + 1;
    ui->lineCol->setText("Ln " + QString::number(line) + ", Col " + QString::number(col));
}

//done
void MainWindow::on_actionSelect_All_triggered()
{
    ui->plainTextEdit->selectAll();
}

//done
void MainWindow::on_actionZoom_in_triggered()
{
    if(this->currentZoom >= 500)
        return;
    ui->plainTextEdit->zoomIn();
    this->currentZoom += 10;
    QString zoom = QString::number(this->currentZoom) + " %";
    ui->zoomSize->setText(zoom);
}

//done
void MainWindow::on_actionZoom_out_triggered()
{
    if(this->currentZoom <= 10)
        return;
    ui->plainTextEdit->zoomOut();
    this->currentZoom -= 10;
    QString zoom = QString::number(this->currentZoom) + " %";
    ui->zoomSize->setText(zoom);
}

//done
void MainWindow::on_restoreDefaultZoom_triggered()
{
    int zoom = this->currentZoom;
    if(zoom > 100){
        ui->plainTextEdit->zoomOut((zoom - 100) / 10);
        ui->zoomSize->setText("100 %");
    }
    else{
        ui->plainTextEdit->zoomIn((100 - zoom) / 10);
        ui->zoomSize->setText("100 %");
    }
    this->currentZoom = 100;
}

//done
void MainWindow::on_actionTime_Date_triggered()
{
    QTime curTime = QTime::currentTime();
    QDate curDate = QDate::currentDate();
    QString dateTime;
    int hour = curTime.hour();
    if(hour <= 12){
        dateTime = curTime.toString("hh : mm") + " am "
                                    + curDate.toString("dd/MM/yyyy");
    }
    else{
        hour -= 12;
        if(hour < 10)
            dateTime = "0" + QString::number(hour - 12) + " : " + curTime.toString("mm") + " pm " + curDate.toString("dd/MM/yyyy");
        else
            dateTime = QString::number(hour - 12) + " : " + curTime.toString("mm") + " pm " + curDate.toString("dd/MM/yyyy");
    }

    ui->plainTextEdit->insertPlainText(dateTime);
}

//done
void MainWindow::on_actionWord_Wrap_triggered()
{
    if(ui->actionWord_Wrap->isChecked())
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
}

//done
void MainWindow::on_actionNewWindow_triggered()
{
    genaricClass::generateNewWindow();
}
