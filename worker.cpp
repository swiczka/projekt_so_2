#pragma once

#include "worker.h"

#include <QThread>
#include <QDebug>
#include <chrono>
#include <thread>
#include <QRandomGenerator>
void Worker::doWork()
{
    emit workStarted();

    for (int i = 0; i < THREAD_DURATION; ++i) {
        qDebug() << "Wątek wykonuje pracę..." << i;
            int sleepTime = QRandomGenerator::global()->bounded(1, 6);
        qDebug()<<"wykonuje prace przez:"<<sleepTime<<"sekundy";
            QThread::sleep(sleepTime);  // Symulacja pracy
    }

    emit workFinished();
}

