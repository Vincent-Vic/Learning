/*************************************************************************
    > File Name: MyTextBrowser.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月22日 星期六 14时52分14秒
    > Functional： My TextBrowser package
 ************************************************************************/
#ifndef MYTEXTBROWSER_H
#define MYTEXTBROWSER_H

#include <QWidget>
#include <QTextBrowser>

class MyTextBrowser:public QTextBrowser
{
public:
    //输入框控件封装，主要实现控件美化及复制粘贴禁止
    MyTextBrowser(QString Text="",QWidget* f=nullptr);
    void Fillet_Style();
};

#endif // MYTEXTBROWSER_H
