/*************************************************************************
    > File Name: MyLabel.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月20日 星期四 15时15分44秒
    > Functional： My Label package
 ************************************************************************/
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QFont>

class MyLabel:public QLabel
{
public:
    //标签控件封装，主要实现控件美化
    MyLabel(QString Text="",QWidget* f=nullptr);
    void Fillet_Style();
    void SetMyFont(int size=24,QString FontName="华文新魏");
    void SetBackGroundRed();
    void SetBackGroundWathet();
    void SetBackGroundGray();
    void SetColourFont();
};

#endif // MYLABEL_H
