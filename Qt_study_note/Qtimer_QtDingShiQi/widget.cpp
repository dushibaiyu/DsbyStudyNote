#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // m_timeId = startTimer(1000);//启动一个定时器
    //qDebug() <<"Time ID:"<< m_timeId;

    timer = new QTimer(this);//初始化timer对象，并把此类设为父级，这样在此类对象析构时，会自动析构timer
    //timer->setInterval(1000);//把定时器设为1000毫秒
    timer->start(1000);//把定时器设为1000毫秒，并启动
    connect(timer,SIGNAL(timeout()),this,SLOT(setLabel2()));//建立qt定时器类超时信号槽连接，每超时就执行
    timer->singleShot(5000,this,SLOT(setLabl3()));//只执行一次
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::timerEvent(QTimerEvent * e)//捕获定时器事件，重写事件实现定时器
//{
//    static int i = 0;
//    if (e->timerId() == m_timeId)
//    {
//        ui->label->setText(QTime::currentTime().toString("hh:mm:ss"));//让label显示当前系统时间
//        //qDebug()<< "i:" <<i << " m_timeId :" << m_timeId;
//        ++i;
//    }
//    qDebug()<< "time_id:" <<e->timerId();
//}

void Widget::setLabl3()//qt超时执行槽
{
    static int t = 0;
    qDebug() << "执行"<<t<<"次！";
    ++t;
}

void Widget::setLabel2()//只执行一次槽
{

    ui->label_2->setText("timer：" + QTime::currentTime().toString("hh:mm:ss"));

}

