/*************************************************************************
    > File Name: UserInformation.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月10日 星期一 13时39分56秒
    > Functional： User information class
 ************************************************************************/
#ifndef USERINFORMATION_H
#define USERINFORMATION_H
#include<QString>

class UserInformation
{
public:
    UserInformation();
    QString UserName;           //用户姓名
    QString UserGrade;          //用户年级
    QString UserMajoy;          //用户专业
    QString UserMail;           //用户邮箱
    QString UserTelephone;      //用户电话
    QString UserClass;          //用户方向
    QString UserQQ;             //用户QQ
    int UserTotalScore;         //用户总分
    int UserMultipleScore;      //用户选择题得分
    int UserRecognizedScore;    //用户判断题得分
    int UserCompletionScore;    //用户选择题得分
    int UserCodeScore;          //用户打码题得分
    //获取登入用户信息的重载
    UserInformation & operator=(const UserInformation* User);
    void print_U();
};

#endif // USERINFORMATION_H
