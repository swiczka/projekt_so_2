#include "mainwindow.h"
#include "qapplication.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startWorkButton, &QPushButton::clicked, this, &MainWindow::startWork);

    worker.moveToThread(&workerThread);
    connect(&worker, &Worker::workFinished, this, &MainWindow::onWorkFinished);

    workerThread.start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::startWork()
{
    QMetaObject::invokeMethod(&worker, "doWork", Qt::QueuedConnection);
}

void MainWindow::onWorkFinished()
{
    ui->infoLabel->setText("Zakończono wykonywanie wątków");
    QThread::sleep(2);
    QApplication::quit();
}
