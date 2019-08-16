/*************************************************************************
    > File Name: MyPicTure.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月21日 星期五 16时45分40秒
    > Functional： My PicTure package
 ************************************************************************/
#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <QLabel>
#include <QMessageBox>
#include <QWidget>

class MyPicTure:public QLabel
{
public:
    //按钮控件封装，主要实现控件美化
    MyPicTure(QString PictureFile="" ,QWidget* f=nullptr,QString error="0x000000");
};

#endif // MYPICTURE_H
