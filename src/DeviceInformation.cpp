#include "DeviceInformation.h"
#include "ui_DeviceInformation.h"

DeviceInformation::DeviceInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceInformation) {
    ui->setupUi(this);
}

DeviceInformation::~DeviceInformation() {
    delete ui;
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

void DeviceInformation::on_mFirmwareInfo_clicked() {
    // This SHOULD executed AFTER launching the server.
    tup = new ThreadUpdate();
    qRegisterMetaType<string>("string");
    connect(tup, SIGNAL(finishedRet(string)), this, SLOT(on_thread_finish(string)));
    tup->start();
}

void DeviceInformation::printOutput() {
    ui->mFWInfoLabel->setText(mProcessGetFW.readAllStandardOutput());
}
