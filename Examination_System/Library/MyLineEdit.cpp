/*************************************************************************
    > File Name: MyLineEdit.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月21日 星期五 13时33分45秒
    > Functional： My LineEdit package
 ************************************************************************/
#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget *parent ): QLineEdit(parent)
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(22);
    ft.setBold(true);
    ft.setFamily("华文新魏");
    //向标签传入字体信息
    this->setFont(ft);
    this->Fillet_Style();
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::white);
    this->setPalette(palette);
    //设置无右键菜单
    setContextMenuPolicy(Qt::NoContextMenu);
    // this->keyPressEvent(event);
}

void MyLineEdit::Fillet_Style()
{
    this->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:1px solid #b9babb");

}

void MyLineEdit::SetMyFont(int size, QString FontName)
{
    QFont font;
    font.setPointSize(size);
    font.setFamily(FontName);
    this->setFont(font);
}


MyLineEdit::~MyLineEdit()
{
}

//屏蔽输入框全选、复制、粘贴功能
void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::SelectAll)
            || event->matches(QKeySequence::Copy)
            || event->matches(QKeySequence::Paste))
    {
        return;
    }

    QLineEdit::keyPressEvent(event);
}

//鼠标位于密码框中时不可移动
void MyLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

//鼠标位于密码框中时不可移动
void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
