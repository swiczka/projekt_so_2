#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startWorkButton, &QPushButton::clicked, this, &MainWindow::startWork);

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
    ui->startWorkButton->hide();
    int workerTimes[4] = {0, 0, 0, 0};

    for(int j = 0; j < 4; j++){
        bool ok = false;

        while(!ok){
            int newNumber = QRandomGenerator::global()->bounded(1, 8);
            ok = true;
            for(int i = 0; i < 4; i++){
                if(workerTimes[i] == newNumber){
                    ok = false;
                    break;
                }
            }
            if (ok)
                workerTimes[j] = newNumber;
        }
    }

    // wyznaczanie wątku o maksymalnym czasie pracy

    int maxTimeIndex = 0;
    int maxDuration = 0;

    for(int i = 0; i < 4; i++){

        if(maxDuration < workerTimes[i]){
            maxTimeIndex = i;
            maxDuration = workerTimes[i];
        }


        qDebug() << workerTimes[i];
        worker[i].workTime = workerTimes[i];
        worker[i].workerIndex = i;
    }
    qDebug() << "Index: " << maxTimeIndex;
    connect(&worker[maxTimeIndex], &Worker::workFinished, this, &MainWindow::handleWorkFinished);

    runNextWorker();
}

void MainWindow::onWorkStarted(int index){
    QString message = "Wykonywanie wątku " + QString::number(index + 1);

    switch(index){
    case 0:
        ui->textBrowser_1->setText(message);
        break;
    case 1:
        ui->textBrowser_2->setText(message);
        break;
    case 2:
        ui->textBrowser_3->setText(message);
        break;
    case 3:
        ui->textBrowser_4->setText(message);
        break;
    }
}

void MainWindow::onWorkFinished(int index)
{
    QString message = "Zakończono wykonywanie wątku " + QString::number(index + 1);
    ui->textBrowserMain->append(message);

    switch(index){

    case 0:
        ui->textBrowser_1->setText(message);
        break;
    case 1:
        ui->textBrowser_2->setText(message);
        break;
    case 2:
        ui->textBrowser_3->setText(message);
        break;
    case 3:
        ui->textBrowser_4->setText(message);
        break;
    }
}

void MainWindow::runNextWorker()
{
    for(int i = 0; i < 4; i++){
        QMetaObject::invokeMethod(&worker[i], "doWork", Qt::QueuedConnection);
        workerThread[i].start();
    }
}

void MainWindow::handleWorkFinished(){
    ui->textBrowserMain->append("Wszystkie wątki zakończone!");
    qDebug()<<"Wszystkie watki zakonczone. Aktualizuje ...";
}
