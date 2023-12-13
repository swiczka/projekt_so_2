#pragma once

#include "worker.h"

#include <QThread>
#include <QDebug>
#include <chrono>
#include <thread>

void Worker::doWork()
{
    emit workStarted();

    for (int i = 0; i < THREAD_DURATION; ++i) {
        qDebug() << "Wątek wykonuje pracę..." << i;
            QThread::sleep(1);  // Symulacja pracy
    }

    emit workFinished();
}

