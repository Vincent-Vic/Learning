/*************************************************************************
    > File Name: GroupRadioButton.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月25日 星期二 15时25分54秒
    > Functional： Radio button combination package
 ************************************************************************/
#ifndef MYRADIOBUTTON_H
#define MYRADIOBUTTON_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include "Questions.h"

class GroupRadioButton : public QWidget
{
    Q_OBJECT
public:
    /*
     *  实现选择题及判断题单选按钮组合
     * */
    explicit GroupRadioButton(QWidget *parent = nullptr);
    ~GroupRadioButton();
    QVBoxLayout* Vbox;
    QHBoxLayout* Hbox;
    QGroupBox* GroupBoxChoice;
    QGroupBox* GroupBoxJudgment;
    QRadioButton* RadioButton;
    void RadioGroupBoxChoice(QWidget *p,Questions* Question);
    void RadioGroupBoxIf(QWidget *p);
    QString Choice_Options();
    QString Judgment_Options();
    //实现显示隐藏按钮
    void ShowBox();
    void HideBox();
signals:

public slots:
};
#endif // MYRADIOBUTTON_H
