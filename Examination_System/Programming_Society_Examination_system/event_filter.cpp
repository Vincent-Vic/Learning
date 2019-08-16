/*************************************************************************
    > File Name: End_Page.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月07日 星期一 12时45分12秒
    > Functional： Block keyboard copy paste messages
 ************************************************************************/
#include "event_filter.h"
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>

EventFilter::EventFilter(QObject *parent)
    : QObject(parent)
{

}

EventFilter::~EventFilter()
{

}

bool EventFilter::eventFilter(QObject *obj, QEvent *event)
{
    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(obj);
    if (pLineEdit != NULL)
    {
        switch (event->type())
        {
        case QEvent::MouseMove:
        case QEvent::MouseButtonDblClick:
            return true;
        case QEvent::KeyPress:
        {
            QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);
            if(pKeyEvent->matches(QKeySequence::SelectAll)
                    || pKeyEvent->matches(QKeySequence::Copy)
                    || pKeyEvent->matches(QKeySequence::Paste))
            {
                return true;
            }
        }
        }
    }
    return QObject::eventFilter(obj, event);
}

