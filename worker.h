#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>

class Worker : public QObject
{
    Q_OBJECT

private:
    QMutex *mutex;

public:
    Worker();
    ~Worker();
    int workTime;
    int workerIndex;

public slots:
    void doWork();

signals:
    void workStarted(int index);
    void workFinished(int index);

};

#endif // WORKER_H

