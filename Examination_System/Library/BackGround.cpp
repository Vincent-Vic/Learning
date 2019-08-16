/*************************************************************************
    > File Name: BackGround.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月12日 星期三 21时40分12秒
    > Functional： Package background
 ************************************************************************/
#include "BackGround.h"

BackGround::BackGround()
{

}

bool BackGround::SetBackGround(QWidget * f, QString Picture)
{
    QPixmap pixmap(Picture);
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    f->setPalette(palette);
    return true;
}
