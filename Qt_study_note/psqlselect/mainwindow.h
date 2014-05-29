#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QSqlDatabase & db,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void jiansuo();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase sql;
};

#endif // MAINWINDOW_H
