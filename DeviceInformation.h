#ifndef DEVICEINFORMATION_H
#define DEVICEINFORMATION_H

#include <QWidget>
#include <QProcess>
#include <iostream>
#include <sstream>
#include <QTimer>
#include "threadupdate.h"
using namespace std;

namespace Ui {
class DeviceInformation;
}

class DeviceInformation : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceInformation(QWidget *parent = 0);
    ~DeviceInformation();

private slots:
    void on_mFirmwareInfo_clicked();
    void printOutput();
    void getFWStatusInner();
    void on_thread_finish(const string val);

private:
    QProcess mProcessGetFW;
    ThreadUpdate *tup;
    Ui::DeviceInformation *ui;
};

#endif // DEVICEINFORMATION_H
