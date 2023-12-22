#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include <QDebug>

#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startWork();
    void onWorkStarted();
    void onWorkFinished();
    /////???//////
    void onWorkFinishedMainWindow();
    /////???/////
    void handleWorkFinished();
private:
    Ui::MainWindow *ui;
    Worker worker[4];
    QThread workerThread[4];
    int currentWorkerIndex = 0;
    void runNextWorker();
};

#endif // MAINWINDOW_H

