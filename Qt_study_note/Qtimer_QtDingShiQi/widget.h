#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
  //  void timerEvent(QTimerEvent *);//重写事件实现定时器
private slots:
    void setLabl3();
    void setLabel2();
private:
    Ui::Widget *ui;
   // int m_timeId;
    QTimer * timer;//使用qt定时器类
};

#endif // WIDGET_H

/*
qt实现定时器：
1.重写事件实现定时器，
void timerEvent(QTimerEvent *)。
*/
