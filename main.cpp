#include "mainwindow.h"
#include "auth.h"

#include <QApplication>
#include <QtWidgets>
#include <vector>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Auth au;
    au.show();
    if (au.exec() != QDialog::Accepted)
    {
       return 0;
    }
    MainWindow w(au.getStatus(), au.getUserName());

    w.show();

    return a.exec();
}



