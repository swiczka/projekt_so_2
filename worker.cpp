#pragma once

#include "worker.h"

#include <QThread>
#include <QDebug>

Worker::Worker()
{
    mutex = new QMutex();
}

Worker::~Worker()
{
    delete mutex;
}

void Worker::doWork()
{
    mutex->lock();
    //      SEKCJA KRYTYCZNA
    emit workStarted(workerIndex);
    //      KONIEC SEKCJI KRYTYCZNEJ
    mutex->unlock();

    qDebug()<<"Wątek" << workerIndex + 1 << "wykonuje prace przez:"<< workTime <<"sekundy";

    for (int i = 0; i < workTime; ++i) {
        qDebug() << "Wątek" << workerIndex + 1 << "wykonuje pracę..." << i;
        QThread::sleep(1);
    }

    mutex->lock();
    //      SEKCJA KRYTYCZNA
    emit workFinished(workerIndex);
    //      KONIEC SEKCJI KRYTYCZNEJ
    mutex->unlock();
}

