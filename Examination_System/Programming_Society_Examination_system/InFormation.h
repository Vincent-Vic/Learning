/*************************************************************************
    > File Name: InFormation.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月01日 星期二 16时26分36秒
    > Functional： Examination information
 ************************************************************************/
#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include <QGridLayout>
#include <QDesktopWidget>
#include "BackGround.h"
#include "../Library/MyLabel.h"
#include "../Library/MyButton.h"
#include <QCheckBox>
#include "../Library/MyPicTure.h"

class InFormation : public QWidget
{
    Q_OBJECT
public:
    explicit InFormation(QWidget *parent = nullptr);
    ~InFormation();
    //复选框是否选中
    bool Treaty_Selected;
    //下一个按钮
    MyButton* Exit_Button;
private:
    /*
     *  界面按钮控件及布局实现
     * */
    QDesktopWidget *Desktop;
    MyLabel* Title;
    MyLabel* Outline;
    MyLabel* Prompt;
    MyLabel* Treaty;
    QCheckBox* ChoiceTreaty;
    MyPicTure* Logo;
    BackGround* InFormationBackGround;
    QGridLayout *GridLayout;
    void InFormation_Layout();
    void InFormation_Setbackground();
signals:

public slots:
    void Treaty_Click(int);
};

#endif // INFORMATION_H
