/*************************************************************************
    > File Name: BackGround.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月12日 星期三 21时40分12秒
    > Functional： Package background
 ************************************************************************/
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>

class BackGround : public QWidget
{
    Q_OBJECT
public:
    explicit BackGround();
    //设置背景图片
    bool SetBackGround(QWidget*,QString);
signals:

public slots:
};

#endif // BACKGROUND_H
