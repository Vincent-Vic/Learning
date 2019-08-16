/*************************************************************************
    > File Name: MyTextEdit.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月23日 星期四 13时11分54秒
    > Functional： My TextEdit package
 ************************************************************************/
#include "MyTextEdit.h"

MyTextEdit::MyTextEdit(QString Text,QWidget* f)
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    //向标签传入字体信息
    this->setFont(ft);
    setContextMenuPolicy(Qt::NoContextMenu);
    this->Fillet_Style();
    this->setParent(f);
    this->setText(Text);
    //keyPressEvent(event);
}

void MyTextEdit::Fillet_Style()
{
    this->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:1px solid #b9babb;color:white");
}

void MyTextEdit::keyPressEvent(QKeyEvent *event)
{
    //屏蔽输入框全选、复制、粘贴功能
        if(event->matches(QKeySequence::SelectAll)
                || event->matches(QKeySequence::Copy)
                || event->matches(QKeySequence::Paste))
        {
            return;
        }

        QTextEdit::keyPressEvent(event);
}

void MyTextEdit::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void MyTextEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
