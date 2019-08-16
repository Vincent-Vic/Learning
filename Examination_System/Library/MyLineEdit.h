/*************************************************************************
    > File Name: MyLineEdit.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月21日 星期五 13时33分45秒
    > Functional： My LineEdit package
 ************************************************************************/
#ifndef PASSWORD_LINE_EDIT
#define PASSWORD_LINE_EDIT

#include <QLineEdit>
#include <QKeyEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    //输入框控件封装，主要实现控件美化及复制粘贴禁止
    explicit MyLineEdit(QWidget *parent = 0);
    void Fillet_Style();
    void SetMyFont(int size=22,QString FontName="华文新魏");
    ~MyLineEdit();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // PASSWORD_LINE_EDIT

