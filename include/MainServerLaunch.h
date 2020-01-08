#ifndef MAINSERVERLAUNCH_H
#define MAINSERVERLAUNCH_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <qprocess.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <thread>
#include <QTimer>
#include <QFile>

using namespace std;

namespace Ui {
class MainServerLaunch;
}

class MainServerLaunch : public QWidget {
    Q_OBJECT

private slots:
    void on_server_launch_clicked();

    void on_server_log_clicked();

    void on_server_kill_clicked();

    void run_update();

public:
    explicit MainServerLaunch(QWidget *parent = 0);
    ~MainServerLaunch();

private:
    QProcess mProcess;
    QMessageBox msgBox;
    bool isServerRunning;
    int timer;
    Ui::MainServerLaunch *ui;
};

#endif // MAINSERVERLAUNCH_H
