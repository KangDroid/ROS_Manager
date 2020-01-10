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

/**
 * @brief DeviceInformation::on_thread_finish
 * @param val when thread return string
 *
 * This function will set FW Information returned from thread
 * But, when thread isn't finished, return so it wouldn't set something strange string.
 *
 */
void DeviceInformation::on_thread_finish(const string val) {
    if (!(tup->isFinished())) {
        return;
    }
    if (tup->isRunning()) {
        return;
    }
    // Parse string.
    stringstream tmp;
    tmp.str(val);
    string tmp_two;
    string hw_version;
    string fw_version;
    string sw_version;
    for (int i = 0; tmp >> tmp_two; i++) {
        if (tmp_two == "hardware:") {
            tmp >> hw_version;
        } else if (tmp_two == "firmware:") {
            tmp >> fw_version;
        } else if (tmp_two == "software:") {
            tmp >> sw_version;
        }
    }
    tmp_two = "HW Version: " + hw_version + "\n" + "FW Version: " + fw_version + "\n" + "SW Version: " + sw_version + "\n";
    ui->mFWInfoLabel->setText(QString::fromStdString(tmp_two));
}

/**
 * @brief DeviceInformation::on_mFirmwareInfo_clicked
 * When Button clicked.
 */
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
