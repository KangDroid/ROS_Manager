#include "tabdialog.h"
#include "MainServerLaunch.h"
#include "DeviceInformation.h"

TabDialog::TabDialog(QDialog *parent): QDialog(parent) {
    tabWidget = new QTabWidget;
    tabWidget->addTab(new MainServerLaunch(), tr("Main Server Launcher"));
    tabWidget->addTab(new DeviceInformation(), tr("Device status"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    resize(650, 450);
}
