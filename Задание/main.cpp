#include "mainwindow.h"
#include "handler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale(QLocale::Russian));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
