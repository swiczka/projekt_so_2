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
    void onWorkFinished();

private:
    Ui::MainWindow *ui;
    Worker worker;
    QThread workerThread;
};

#endif // MAINWINDOW_H

