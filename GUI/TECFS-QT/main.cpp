#include "src/MainWindow/mainwindow.h"
#include "src/Socket/Client.cpp"
#include <thread>
#include <QApplication>

void RunClient() {
    InitClient();
}
int runGui(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


int main(int argc, char *argv[])
{
    thread runs(runGui,argc,argv);
    thread main(RunClient);
    runs.join();
    main.join();
    return 0;
}

