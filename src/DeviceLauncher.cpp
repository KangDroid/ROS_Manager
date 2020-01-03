#include "DeviceLauncher.h"
#include "ui_DeviceLauncher.h"
#include "unistd.h"

DeviceLauncher::DeviceLauncher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLauncher) {
    ui->setupUi(this);
}

DeviceLauncher::~DeviceLauncher() {
    delete ui;
}

/**
 * @brief DeviceLauncher::on_vmburger_launch_clicked
 * Launch process is working correctly without roscore server.
 * But, the thing is, currently there isn't any way to determine whether
 * server is correctly turned on or not.
 *
 * The Choice we have is(Acutally TODO):
 * 1. Either modify ROS Package - in this situation, we have to compile ROS again on HOST.(Luckly, bionic beaver is the best)
 * 2. In SH File, add some way to write log file - but, tee or >> does not work at all on roscore or launch process.
 */
void DeviceLauncher::on_vmburger_launch_clicked() {
    if (mVMLaunchProcess.pid() > 0) {
        // Process is already running.
        qDebug("Process is already running");
    } else {
        QString program = "setsid /home/kangdroid/test_launch_vm.sh\n";
        mVMLaunchProcess.start(program);
        connect(&mVMLaunchProcess, SIGNAL(readyReadStandardError()), this, SLOT(printOutput())); // When reading STDOUT

        // We have to finish process to read output. so use finished.
        //connect(&mVMLaunchProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(printOutput()));
    }
}

void DeviceLauncher::printOutput() {
    qDebug(mVMLaunchProcess.readAllStandardOutput());
    qDebug(mVMLaunchProcess.readAllStandardError());
}

void DeviceLauncher::on_vmburger_kill_clicked() {
    QString killingProcess = "kill -TERM -" + QString::number(mVMLaunchProcess.pid());
    system(killingProcess.toStdString().c_str());
    if (mVMLaunchProcess.pid() > 0) {
        mVMLaunchProcess.terminate();
    }
}
