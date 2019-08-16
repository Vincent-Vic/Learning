/*************************************************************************
    > File Name: UserInformation.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月10日 星期一 13时39分56秒
    > Functional： User information class
 ************************************************************************/
#include "UserInformation.h"

UserInformation::UserInformation():UserTotalScore(0),UserCompletionScore(0),UserCodeScore(0),UserRecognizedScore(0),UserMultipleScore(0),UserClass("软游方向")
{

}

UserInformation &UserInformation::operator=(const UserInformation *User)
{
    this->UserName=User->UserName;
    this->UserGrade=User->UserGrade;
    this->UserMajoy=User->UserMajoy;
    this->UserMail=User->UserMail;
    this->UserTelephone=User->UserTelephone;
    this->UserQQ=User->UserQQ;
}
