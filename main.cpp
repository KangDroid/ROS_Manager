#include "dialog.h"
#include "tabdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabDialog w;
    w.show();
    //Dialog w;

    return a.exec();
}
