/*************************************************************************
    > File Name: Questions.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月27日 星期三 14时49分15秒
    > Functional： Questions information class
 ************************************************************************/
#ifndef CHOICEQUESTION_H
#define CHOICEQUESTION_H

#include <QString>
#include <QDebug>
class Questions
{
public:
    Questions();
    ~Questions();
    QString Subject;              //题目
    QString Choice_A;             //A选项
    QString Choice_B;             //B选项
    QString Choice_C;             //C选项
    QString ChoiceAnswer;         //选择题答案
    bool JudgmentAnswer;          //判断题答案
    QString Completion[10];       //填空题
    int ComLength;                //填空题答案库长度
    int ID;                       //选择题ID
    void Clear_Comlention();      //清除填空题答案
    void print_Q();               //测试
};

#endif // CHOICEQUESTION_H
