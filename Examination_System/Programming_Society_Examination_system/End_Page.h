/*************************************************************************
    > File Name: End_Page.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月07日 星期一 12时45分12秒
    > Functional： End interface
 ************************************************************************/
#ifndef END_PAGE_H
#define END_PAGE_H

#include <QWidget>
#include <QGridLayout>
#include "../Library/BackGround.h"
#include "../Library/MyLabel.h"
#include "../Library/MyButton.h"
#include <QToolButton>
#include "../Library/MyPicTure.h"

class End_Page : public QWidget
{
    Q_OBJECT
public:
    explicit End_Page(QWidget *parent = nullptr);
    ~End_Page();
    //结束按钮
    QToolButton* Logo;
    //设置成绩结果
    void SetResult(QString Result);
private:
    /*
     *  界面按钮控件及布局实现
     * */
    MyLabel* Title;
    MyLabel* Outline;
    QToolButton* QR_code;
    BackGround* End_PageGround;
    QGridLayout *GridLayout;
    void End_Page_Layout();
    void End_Page_Setbackground();
    void Picturn();
signals:

public slots:
};

#endif // END_PAGE_H
