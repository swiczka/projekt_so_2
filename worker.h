#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork();

signals:
    void workFinished();
};

#endif // WORKER_H
