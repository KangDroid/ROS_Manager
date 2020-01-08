#ifndef DEVICELAUNCHER_H
#define DEVICELAUNCHER_H

#include <QWidget>
#include <QProcess>
#include <iostream>
#include <QFile>

using namespace std;

namespace Ui {
class DeviceLauncher;
}

class DeviceLauncher : public QWidget {
    Q_OBJECT

public:
    explicit DeviceLauncher(QWidget *parent = 0);
    ~DeviceLauncher();

private slots:
    void on_vmburger_launch_clicked();
    void printOutput();

    void on_vmburger_kill_clicked();

private:
    Ui::DeviceLauncher *ui;
    QProcess mVMLaunchProcess;
};

#endif // DEVICELAUNCHER_H
