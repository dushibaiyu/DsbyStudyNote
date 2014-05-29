#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QString>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");//定义数据库，和使用的数据库驱动，这里使用的postgres驱动
    db.setHostName("localhost");//设置主机名
    db.setPort(5432);//端口号
    db.setDatabaseName("cmss");//数据库的名字
    db.setUserName("postgres");//用户名
    db.setPassword("123789");//密码

    bool ok = db.open();//打开数据库
    std::cout << ok <<std::endl;

    QSqlQuery qu;//定义执行sql语句
    ok =  qu.exec("select uuid, REG_OPT AS REG,CTNNO AS CT from t_kenpin_data_2");//执行sql语句
    if (ok)
    {
        std::cout << "chenggong" << std::endl;
        while (qu.next())//判断是否结束
        {
            //输出值
            std::cout << qu.value("REG").toString().toStdString() << "  " <<
                         qu.value("CT").toString().toStdString() <<std::endl;

        }
    }
    else
    {
        std::cout << "shibai "<<std::endl;
    }
	db.close();
    system("pause");
    return a.exec();
}
