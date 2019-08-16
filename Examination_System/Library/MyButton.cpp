/*************************************************************************
    > File Name: MyButton.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月20日 星期四 12时55分44秒
    > Functional： My button package
 ************************************************************************/
#include "MyButton.h"

MyButton::MyButton(QString Text,QWidget* f)
{
        QFont ft;
        //设置字体大小
        ft.setPointSize(24);
        ft.setBold(true);
        ft.setFamily("华文新魏");
        //向标签传入字体信息
        this->setFont(ft);
        //创建调色板
        QPalette pa;
        //设置颜色
        pa.setColor(QPalette::ButtonText, QColor(200,200,200));
        this->setPalette(pa);
        this->setFlat(true);
        this->Fillet_Style();
        this->setParent(f);
        this->setText(Text);
}

void MyButton::Fillet_Style()
{
    this->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
}

void MyButton::SetMyFont(int size, QString FontName)
{
    QFont font;
    font.setPointSize(size);
    font.setFamily(FontName);
    this->setFont(font);
}
