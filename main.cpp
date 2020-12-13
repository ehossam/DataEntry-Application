#include "mainwindow.h"
#include "adminpanel.h"
#include <QApplication>
#include "databasemanager.h"
#include <memory>
#include <QWidget>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBaseManager::createInstance();

    unique_ptr<QWidget> w= make_unique<MainWindow>();
    //w->showFullScreen();
    w->show();
    return a.exec();
}
