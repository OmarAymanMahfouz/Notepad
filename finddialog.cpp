#include "finddialog.h"
#include "ui_finddialog.h"
#include <QTextDocument>
#include <QDebug>

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

findDialog::~findDialog()
{
    delete ui;
    ui = nullptr;
}

void findDialog::on_cancelBttn_clicked()
{
    this->close();
}


void findDialog::on_findNextBttn_clicked()
{
    if(ui->upRadio->isChecked()){
        this->plainText->find(ui->findText->text(), QTextDocument::FindBackward);
        qDebug() << true;
    }
    else{
        qDebug() << false;
    }
}

