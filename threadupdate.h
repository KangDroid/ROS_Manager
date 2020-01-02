#ifndef THREADUPDATE_H
#define THREADUPDATE_H

#include <QThread>
#include <QProcess>
#include <iostream>
#include <string>

using namespace std;

class ThreadUpdate : public QThread
{
    Q_OBJECT
public:
    explicit ThreadUpdate(QObject *parent = 0);

private:
    void run();

signals:
    void finishedRet(const string val);
};

#endif // THREADUPDATE_H
