/*************************************************************************
    > File Name: MyTextEdit.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月23日 星期四 13时11分54秒
    > Functional： My TextEdit package
 ************************************************************************/
#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class MyTextEdit:public QTextEdit
{
public:
    //输入框控件封装，主要实现控件美化及复制粘贴禁止
    MyTextEdit(QString Text="",QWidget* f=nullptr);
    void Fillet_Style();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MYTEXTEDIT_H
