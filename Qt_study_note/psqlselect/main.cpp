#include "mainwindow.h"
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase myDb = QSqlDatabase::addDatabase("QPSQL");
    myDb.setHostName("localhost");
    myDb.setDatabaseName("cmss");
    myDb.setUserName("postgres");
    myDb.setPassword("123789");

    MainWindow w(myDb);
    w.show();

    return a.exec();
}
