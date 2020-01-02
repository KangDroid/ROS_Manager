#include "threadupdate.h"

ThreadUpdate::ThreadUpdate(QObject *parent): QThread(parent)
{
}

void ThreadUpdate::run() {
    QProcess mProcessGetFW;
    mProcessGetFW.setProcessChannelMode(QProcess::MergedChannels);
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
    /*stringstream tmp(changedPut);
    string t;
    string output_str = "";
    while(getline(tmp, t)) {
        output_str += t + "\n";
    }*/

    emit finishedRet(changedPut);
}
