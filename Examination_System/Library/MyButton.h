/*************************************************************************
    > File Name: MyButton.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月20日 星期四 12时55分44秒
    > Functional： My button package
 ************************************************************************/
#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>
#include <QFont>
#include <QPalette>

class MyButton:public QPushButton
{
public:
    //按钮控件封装，主要实现控件美化
    MyButton(QString Text="",QWidget* f=nullptr);
    void Fillet_Style();
    void SetMyFont(int size=20, QString FontName="黑体");
};

#endif // MYBUTTON_H
