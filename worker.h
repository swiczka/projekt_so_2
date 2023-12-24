#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#define THREAD_DURATION 4

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork();

signals:
    void workStarted();
    void workFinished();
private:
    int qrand();
};
///hejka
#endif // WORKER_H

