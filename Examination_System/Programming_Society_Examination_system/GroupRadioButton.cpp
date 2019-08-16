/*************************************************************************
    > File Name: GroupRadioButton.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月25日 星期二 15时25分54秒
    > Functional： Radio button combination package
 ************************************************************************/
#include "GroupRadioButton.h"
GroupRadioButton::GroupRadioButton(QWidget *parent) : QWidget(parent)
{
        RadioButton=new QRadioButton[3];
        GroupBoxJudgment = new QGroupBox();
        GroupBoxChoice = new QGroupBox();
        Vbox=new QVBoxLayout();
        Hbox=new QHBoxLayout();
}

GroupRadioButton::~GroupRadioButton()
{
    delete Vbox;
    Vbox=nullptr;
    delete Hbox;
    Hbox=nullptr;
    delete GroupBoxChoice;
    GroupBoxChoice=nullptr;
    delete GroupBoxJudgment;
    GroupBoxJudgment=nullptr;
    delete[] RadioButton;
    RadioButton=nullptr;
}

void GroupRadioButton::RadioGroupBoxChoice(QWidget *p, Questions* Question)
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    //创建调色板
    QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    for(int i=0;i<3;i++)
    {
        RadioButton[i].setFont(ft);
        RadioButton[i].setPalette(pa);
        RadioButton[i].setParent(p);
        if(0==i)
            RadioButton[i].setText("A、"+Question->Choice_A);
        else if(1==i)
            RadioButton[i].setText("B、"+Question->Choice_B);
        else
            RadioButton[i].setText("C、"+Question->Choice_C);
        Vbox->addWidget(&RadioButton[i]);
    }
    Vbox->setParent(p);
    GroupBoxChoice->setLayout(Vbox);
    GroupBoxChoice->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;color:white");
    HideBox();
}

void GroupRadioButton::RadioGroupBoxIf(QWidget *p)
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    //创建调色板
    QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    for(int i=0;i<2;i++)
    {
        RadioButton[i].setFont(ft);
        RadioButton[i].setPalette(pa);
        RadioButton[i].setParent(p);
        if(0==i)
            RadioButton[i].setText("√");
        else if(1==i)
            RadioButton[i].setText("X");
        Hbox->addWidget(&RadioButton[i]);
    }
    Hbox->setParent(p);
    GroupBoxJudgment->setLayout(Hbox);
    GroupBoxJudgment->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;color:white");
}

QString GroupRadioButton::Choice_Options()
{
    if(RadioButton[0].isChecked())        return "A";
     else if(RadioButton[1].isChecked())     return "B";
        else if(RadioButton[2].isChecked())     return "C";
            else                                   return "Not";
}

QString GroupRadioButton::Judgment_Options()
{
    if(RadioButton[0].isChecked())        return "Yes";
     else if(RadioButton[1].isChecked())     return "No";
       else                                    return "Not";
}

void GroupRadioButton::ShowBox()
{
    for(int i=0;i<3;i++)
    {
        RadioButton[i].setVisible(true);
    }
}

void GroupRadioButton::HideBox()
{
    for(int i=0;i<3;i++)
    {
        RadioButton[i].setVisible(false);
    }
}

