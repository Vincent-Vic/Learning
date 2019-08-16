/*************************************************************************
    > File Name: Main.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月10日 星期一 13时10分52秒
    > Functional： Main
 ************************************************************************/
#include "Main.h"

int main(int argc, char* argv[])
{

    QApplication app(argc,argv);
    Assembling* s=new Assembling();
    s->MyShow();
    return app.exec();
}

