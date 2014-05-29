#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>//水平布局
#include <QVBoxLayout>//垂直布局
#include <QString>

class FindDialog : public QDialog
{
    Q_OBJECT
    
public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

signals:
    void findNext(const QString &, Qt::CaseSensitivity );
    void findPrevious(const QString &, Qt::CaseSensitivity );

public slots:
    void on_finBut_ck();
    void on_closeBut_ck();
    void finButEnble(const QString &);

private:
    void setWinLay();

    QPushButton * findBut;
    QPushButton * closeBut;
    QLineEdit * textFind;
    QLabel * editLabel;
    QCheckBox * caseChBox;
    QCheckBox * backChBox;
    QHBoxLayout * topLeftHLay;
    QVBoxLayout * leftVLay;
    QVBoxLayout * rightVLay;
    QHBoxLayout * mainLay;
};

#endif // FINDDIALOG_H
