#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>

class TabDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TabDialog(QDialog *parent = 0);

private:
    QTabWidget *tabWidget;

};

#endif // TABDIALOG_H
