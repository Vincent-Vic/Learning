/*************************************************************************
    > File Name: Questions.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月27日 星期三 14时49分15秒
    > Functional： Questions information class
 ************************************************************************/
#include "Questions.h"


Questions::Questions():JudgmentAnswer(false),Subject("占无题库"),Choice_A("A"),Choice_B("B"),Choice_C("C"),ChoiceAnswer("D"),ComLength(0),ID(-1)
{
    for(int i=0;i<10;i++)
        Completion[i]="占无关键字";
}

Questions::~Questions()
{

}

void Questions::Clear_Comlention()
{
    for(int i=0;i<10;i++)
        Completion[i]="占无关键字";
}
