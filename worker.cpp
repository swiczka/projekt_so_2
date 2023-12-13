#include "worker.h"

#include <QThread>
#include <QDebug>

void Worker::doWork()
{
    for (int i = 0; i < 5; ++i) {
        qDebug() << "Wykonuję pracę..." << i;
            QThread::sleep(1);  // Symulacja pracy
    }

    emit workFinished();
}
