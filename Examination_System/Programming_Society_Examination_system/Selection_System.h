/*************************************************************************
    > File Name: Selection_System.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月26日 星期三 13时19分10秒
    > Functional： Selection examination system interface
 ************************************************************************/
#ifndef SELECTION_SYSTEM_H
#define SELECTION_SYSTEM_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QDesktopWidget>
#include "GroupRadioButton.h"
#include "../Library/MyButton.h"
#include "../Library/BackGround.h"
#include "Questions.h"
#include "../Library/MyLabel.h"
#include "File_Function.h"
#include "../Library/MyTextBrowser.h"
class Selection_System : public QWidget
{
    Q_OBJECT
public:
    explicit Selection_System(QWidget *parent = nullptr);
    ~Selection_System();
    MyButton* Exit_Button;
    //对外返回成绩
    int GetChoice_Score();
private:
    /*
     *  界面按钮控件及布局实现
     * */
    QDesktopWidget *Desktop;
    MyLabel* Page;
    MyLabel* Prompt;
    MyTextBrowser* Subject;
    QGridLayout *GridLayout;
    MyButton* Next_Button;
    MyButton* Last_Button;
    GroupRadioButton* RadioButton;
    BackGround* Login_BackGround;
    int Choice_Score;
    //链表
    QList<Questions> Choice;
    //当前显示题目下标
    static int index;
    void SetBackGround();
    void Selection_System_Layout();
    void SetQuestion();
    Questions* GetChoice(int Getid);
signals:

public slots:
    //下一个单击事件
    void Next_Click();
    //上一个单击事件
    void Last_Click();
};
#endif // SELECTION_SYSTEM_H
