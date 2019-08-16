/*************************************************************************
    > File Name: Main.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期四 15时11分02秒
    > Functional： Main
 ************************************************************************/

/**
 *  服务端控件复用客户端的封装
 * */
#include "Main.h"

int main(int argc, char *argv[])
{
    QApplication APP(argc,argv);
    MainServer* s=new MainServer();
    s->show();
    return APP.exec();
}

