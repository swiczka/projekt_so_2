#include "mainwindow.h"
#include "qapplication.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startWorkButton, &QPushButton::clicked, this, &MainWindow::startWork);
    //connect(ui->stopThreadButton, &QPushButton::clicked, &worker[currentWorkerIndex], &Worker::workFinished);

    for (int i = 0; i < 4; i++){
        connect(&worker[i], &Worker::workFinished, this, &MainWindow::onWorkFinished);
        connect(&worker[i], &Worker::workStarted, this, &MainWindow::onWorkStarted);
        worker[i].moveToThread(&workerThread[i]);
    }
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < 4; i++){
        workerThread[i].quit();
        workerThread[i].wait();
    }

    delete ui;
}

void MainWindow::startWork()
{
    runNextWorker();
}

void MainWindow::onWorkStarted(){
    switch(currentWorkerIndex){
    case 0:
        ui->textBrowser_1->setText("Wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 1:
        ui->textBrowser_2->setText("Wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 2:
        ui->textBrowser_3->setText("Wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 3:
        ui->textBrowser_4->setText("Wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    }
}

void MainWindow::onWorkFinished()
{
    switch(currentWorkerIndex){
    case 0:
        ui->textBrowser_1->setText("Zakończono wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 1:
        ui->textBrowser_2->setText("Zakończono wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 2:
        ui->textBrowser_3->setText("Zakończono wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    case 3:
        ui->textBrowser_4->setText("Zakończono wykonywanie wątku " + QString::number(currentWorkerIndex + 1));
        break;
    }
    currentWorkerIndex++;
    runNextWorker();
}

void MainWindow::runNextWorker()
{
    if(currentWorkerIndex < 4){
        QMetaObject::invokeMethod(&worker[currentWorkerIndex], "doWork", Qt::QueuedConnection);
        workerThread[currentWorkerIndex].start();
    }
}
