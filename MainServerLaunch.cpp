#include "MainServerLaunch.h"
#include "ui_MainServerLaunch.h"

MainServerLaunch::MainServerLaunch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainServerLaunch)
{
    timer = 3;
    ui->setupUi(this);
}

MainServerLaunch::~MainServerLaunch()
{
    delete ui;
}

void MainServerLaunch::run_update() {
    string tmp = "Server starts in ";
    tmp += to_string(timer);
    msgBox.setInformativeText(tmp.c_str());
    msgBox.update();
    if (timer != 0) {
        timer--;
        QTimer::singleShot(1000, this, SLOT(run_update()));
    } else if (timer == 0) {
        msgBox.close();
        timer = 3;
    }
}

// Server starts
void MainServerLaunch::on_server_launch_clicked()
{
    /*
     * This is how we create process and show console output.
     * But, for now, using Process return value to recognize fail-success.
     * If the process is running, initiating process is SUCCESS,
     * otherwise, just FAIL.
     * Make sure if process(QProcess) is not running till limit-time, Kill it.
    */
    QString program = "setsid /home/kangdroid/test.sh";
    this->mProcess.setProcessChannelMode(QProcess::MergedChannels);
    mProcess.start(program);
    msgBox.setText("Server starting..");
    msgBox.show();
    QTimer::singleShot(1, this, SLOT(run_update()));


    if (mProcess.pid() > 0) {
        // Its  running.
        std::cout << mProcess.pid() << std::endl;
    } else {
        // Something went wrong.
        std::cout << "Process has NOT started!\nSomething went wrong!!" << std::endl;
    }
    //connect(&mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
}

void MainServerLaunch::on_server_log_clicked()
{
    if (mProcess.pid() > 0) {
        QProcess mTmpProcess;
        mTmpProcess.setProcessChannelMode(QProcess::MergedChannels);
        mTmpProcess.start("/bin/bash -c \"rm -rf /tmp/test.log\"");
        mTmpProcess.waitForFinished();

        mTmpProcess.start("/bin/bash -c \"ln -s /home/kangdroid/.ros/log/latest/roslaunch*.log /tmp/test.log\"");
        mTmpProcess.waitForFinished();

        if (mTmpProcess.pid() > 0) {
            mTmpProcess.kill();
        }
        ui->textBrowser->setText("");
        std::ifstream fin("/tmp/test.log");
        std::string t;
        while (getline(fin, t)) {
            ui->textBrowser->append(t.c_str());
        }
    } else {
        // Process not started.
        ui->textBrowser->setText("Server is NOT Started!");
    }

    ui->verticalScrollBar->update();
}

void MainServerLaunch::on_server_kill_clicked()
{
    if (mProcess.pid() > 0) {
        ui->textBrowser->append("Terminate~\n");
        QString killingProcess = "kill -TERM -" + QString::number(mProcess.pid());
        system(killingProcess.toStdString().c_str());
        if (mProcess.pid() > 0) {
            mProcess.terminate();
        }
    } else {
        ui->textBrowser->setText("Server is NOT Started!\n");
    }

    ui->verticalScrollBar->update();
}
