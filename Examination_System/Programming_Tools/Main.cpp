/*************************************************************************
    > File Name: Main.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月15日 星期二 13时52分14秒
    > Functional： Main
 ************************************************************************/

/**
 *  本工具复用之前的封装控件
 */
#include "Main.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    Tools* T=new Tools();
    T->show();
    return app.exec();
}
