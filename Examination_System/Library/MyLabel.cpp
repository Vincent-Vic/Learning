/*************************************************************************
    > File Name: MyLabel.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月20日 星期四 15时15分44秒
    > Functional： My Label package
 ************************************************************************/
#include "MyLabel.h"

MyLabel::MyLabel(QString Text,QWidget* f)
{
     QFont ft;
    //设置字体大小
    ft.setPointSize(22);
    ft.setBold(true);
    //ft.setFamily("宋体");
    this->setFont(ft);
    //创建调色板
     QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    this->setPalette(pa);
    this->setParent(f);
    this->setText(Text);
}

void MyLabel::Fillet_Style()
{
    this->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
}

void MyLabel::SetMyFont(int size, QString FontName)
{
    QFont font;
    font.setPointSize(size);
    font.setFamily(FontName);
    this->setFont(font);
}

void MyLabel::SetBackGroundRed()
{

    this->setStyleSheet("background-color:red");
}

void MyLabel::SetBackGroundWathet()
{
    this->setStyleSheet("background-color:rgb(85, 255, 255)");
    SetColourFont();
}

void MyLabel::SetBackGroundGray()
{
    this->setStyleSheet("background-color:rgb(136, 134, 134)");
}

void MyLabel::SetColourFont()
{
    QPalette pa;
   //设置颜色
   pa.setColor(QPalette::WindowText,Qt::black);
   this->setPalette(pa);
}


