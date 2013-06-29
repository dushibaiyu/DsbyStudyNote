#include "finddialog.h"
#include <QDebug>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    //初始化控件，并定义属性
    this->editLabel = new QLabel(tr("Find &What:"));
    this->textFind = new QLineEdit;
    this->editLabel->setBuddy(this->textFind);//设置lineEdit作为label的伙伴，也就是按下label的快捷键时，焦点移动到lineEdit

    this->caseChBox = new QCheckBox(tr("Match &Case "));
    this->backChBox = new QCheckBox(tr("Search &BackWard"));

    this->findBut = new QPushButton(tr("Find"));
    this->findBut->setDefault(true);//设置为默认值，也就是对话框enter默认触发的
    this->findBut->setEnabled(false);//设置为不启用状态

    this->closeBut = new QPushButton(tr("Close"));

    setWinLay();//设置窗口布局

    //设置信号槽连接
    connect(findBut,SIGNAL(clicked()),this,SLOT(on_finBut_ck()));
    connect(closeBut,SIGNAL(clicked()),this,SLOT(on_closeBut_ck()));
    connect(textFind,SIGNAL(textChanged(QString)),this,SLOT(finButEnble(QString)));

    this->setWindowTitle(tr("Find:"));

}

FindDialog::~FindDialog()
{
    delete findBut;
    delete closeBut;
    delete textFind;
    delete editLabel;
    delete topLeftHLay;
    delete caseChBox;
    delete backChBox;
    delete leftVLay;
    delete rightVLay;
    delete mainLay;
}

void FindDialog::setWinLay()//设置布局
{
    topLeftHLay = new QHBoxLayout;//topLiftLayout
    topLeftHLay->addWidget(this->editLabel);
    topLeftHLay->addWidget(this->textFind);

    leftVLay = new QVBoxLayout;//leftLayout
    leftVLay->addLayout(topLeftHLay);
    leftVLay->addWidget(this->caseChBox);
    leftVLay->addWidget(this->backChBox);

    rightVLay = new QVBoxLayout;//rightLayout
    rightVLay->addWidget(this->findBut);
    rightVLay->addWidget(this->closeBut);
    rightVLay->addStretch();//添加分隔符

    mainLay = new QHBoxLayout;//mainLayout
    mainLay->addLayout(leftVLay);
    mainLay->addLayout(rightVLay);

    this->setLayout(mainLay);
}

void FindDialog::on_closeBut_ck()
{
    this->close();
}

void FindDialog::finButEnble(const QString & str)
{
    qDebug() << "textChanged():"<< str;
    if(!str.isEmpty())
    {
        this->findBut->setEnabled(true);
    }
    else
    {
        this->findBut->setEnabled(false);
    }
}

void FindDialog::on_finBut_ck()
{
    QString str = this->textFind->text();
    //Qt::CaseSensitivity 为枚举类型, 可取值Qt::CaseSensitive 和 Qt::CaseInsensitive, 表示匹配的灵敏度。
    Qt::CaseSensitivity cs = this->caseChBox->isChecked()?Qt::CaseSensitive : Qt::CaseInsensitive;

    if(this->backChBox->isChecked())
    {
        qDebug() << "findPrevious(str,cs): str:"<<str<<"  cs:" << cs;
        emit findPrevious(str,cs);//发送findPrevious信号
    }
    else
    {
        qDebug() << "findNext(str,cs)"<<str<<"  cs:" << cs;
        emit findNext(str,cs);//发送findNext信号
    }
}
