#include <QApplication>
#include "mainview.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWidget w1;
//    w1.show();

    MainWindow w2;
    w2.show();

//    MainView w3;
//    w3.show();
    return a.exec();
}
