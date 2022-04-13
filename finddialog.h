#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPlainTextEdit>

namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT

public:
    explicit findDialog(QWidget *parent = nullptr);
    ~findDialog();
    QPlainTextEdit *plainText;

private slots:
    void on_cancelBttn_clicked();

    void on_findNextBttn_clicked();

private:
    Ui::findDialog *ui;
};

#endif // FINDDIALOG_H
