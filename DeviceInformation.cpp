#include "DeviceInformation.h"
#include "ui_DeviceInformation.h"

DeviceInformation::DeviceInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceInformation)
{
    ui->setupUi(this);
}

DeviceInformation::~DeviceInformation()
{
    delete ui;
}

void DeviceInformation::getFWStatusInner() {
    /*mProcessGetFW.setProcessChannelMode(QProcess::MergedChannels);
    mProcessGetFW.start("/bin/bash");
    mProcessGetFW.waitForStarted();
    mProcessGetFW.write("source /opt/ros/melodic/setup.bash\n");
    mProcessGetFW.write("source /home/kangdroid/catkin_ws/devel/setup.bash\n");
    mProcessGetFW.write("source /home/kangdroid/catkin_ws/install_isolated/setup.bash\n");
    mProcessGetFW.write("export ROS_MASTER_URI=http://192.168.0.17:11311\n");
    mProcessGetFW.write("export ROS_HOSTNAME=192.168.0.17\n");
    mProcessGetFW.write("rostopic echo -n1 /firmware_version\n");
    mProcessGetFW.write("exit\n");
    mProcessGetFW.waitForFinished();
    QString output(mProcessGetFW.readAllStandardOutput());
    string changedPut = output.toStdString();
    stringstream tmp(changedPut);
    string t;
    string output_str = "";
    while(getline(tmp, t)) {
        output_str += t + "\n";
    }*/
    tup = new ThreadUpdate();
    qRegisterMetaType<string>("string");
    connect(tup, SIGNAL(finishedRet(string)), this, SLOT(on_thread_finish(string)));
    tup->start();

}

void DeviceInformation::on_thread_finish(const string val) {
    if (!(tup->isFinished())) {
        return;
    }
    if (tup->isRunning()) {
        return;
    }
    QString str = QString::fromStdString(val);
    ui->mFWInfoLabel->setText(str);
}

void DeviceInformation::on_mFirmwareInfo_clicked()
{
    getFWStatusInner();
}

void DeviceInformation::printOutput() {
    ui->mFWInfoLabel->setText(mProcessGetFW.readAllStandardOutput());
}
