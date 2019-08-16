/*************************************************************************
    > File Name: End_Page.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月07日 星期一 12时45分12秒
    > Functional： Block keyboard copy paste messages
 ************************************************************************/
#ifndef EVENT_FILTER
#define EVENT_FILTER

#include <QObject>

class EventFilter : public QObject
{
public:
    explicit EventFilter(QObject *parent = 0);
    ~EventFilter();
protected:
    //实现拦截键盘复制粘贴函数
    virtual bool eventFilter(QObject *obj, QEvent *event);
};

#endif // EVENT_FILTER

