#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "finddialog.h"
#include <QMainWindow>
#include <QShortcut>
#include <QMessageBox>
#include <algorithm>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QTextFrame>
#include <QTextCursor>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, int frameNumber);
    ~MainWindow();
    int frameNumber;

private slots:
    void on_actionStatus_Bar_triggered();

    void on_actionExit_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionNew_triggered();

    void on_actionUndo_triggered();

    void on_actionOpen_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionFind_triggered();

    void on_plainTextEdit_cursorPositionChanged();

    void on_actionSelect_All_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_restoreDefaultZoom_triggered();

    void on_actionTime_Date_triggered();

    void on_actionWord_Wrap_triggered();

    void on_actionNewWindow_triggered();

    void on_actionDelete_triggered();

protected:
    void showCloseWindow();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
    void wheelEvent(QWheelEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    bool windowShouldCLose();
    void manageWheelEvent(QWheelEvent *event);
    bool saveRole();
    QString currentPath;
    QString fileName;
    QString initialText;
    int currentZoom;
    QShortcut *copy;
    QShortcut *cut;
    QShortcut *paste;
    QShortcut *save;
    QShortcut *find;
    QShortcut *newWindow;
    QShortcut *selectAll;
    QShortcut *undo;
    QShortcut *redo;
    findDialog *findWindow;
};
#endif // MAINWINDOW_H
