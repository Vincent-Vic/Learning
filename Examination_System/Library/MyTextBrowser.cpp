/*************************************************************************
    > File Name: MyTextBrowser.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月22日 星期六 14时52分14秒
    > Functional： My TextBrowser package
 ************************************************************************/
#include "MyTextBrowser.h"

MyTextBrowser::MyTextBrowser(QString Text, QWidget *f)
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    //向标签传入字体信息
    this->setFont(ft);
    //创建调色板
    QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    //设置无右键菜单
    setContextMenuPolicy(Qt::NoContextMenu);
    this->Fillet_Style();
    this->setParent(f);
    this->setText(Text);
}

void MyTextBrowser::Fillet_Style()
{
     this->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:1px solid #b9babb;color:white");
}
