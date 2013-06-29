#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QSqlDatabase & db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sql = db;
    sql.open();
    QObject::connect(ui->but, &QPushButton::clicked, this, &MainWindow::jiansuo);
}

MainWindow::~MainWindow()
{
    delete ui;
    sql.close();
}

void MainWindow::jiansuo()
{
    qDebug()<< "jiansuo";
    QMessageBox msgbox;
    msgbox.setText("执行检索");
    msgbox.exec();
    static QSqlQueryModel *mode  = new QSqlQueryModel(ui->tableView);
    mode->setQuery("select * from t_kenpin_data_2",sql);
    ui->tableView->setModel(mode);

}
