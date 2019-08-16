/*************************************************************************
    > File Name: End_Page.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月07日 星期一 12时45分12秒
    > Functional： End interface
 ************************************************************************/
#include "End_Page.h"

End_Page::End_Page(QWidget *parent) : QWidget(parent)
{
    //设置窗口大小不变
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setFixedSize(867,391);
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    End_PageGround=new BackGround();
    GridLayout=new QGridLayout(this);
    End_Page_Setbackground();
    Title=new MyLabel("",this);
    Outline=new MyLabel("请加入官方主群！！！之前的为纳新咨询群！！",this);
    QR_code=new QToolButton(this);
    Logo=new QToolButton(this);
    End_Page_Layout();
}

End_Page::~End_Page()
{
    delete Title;
    Title=nullptr;
    delete Outline;
    Outline=nullptr;
    delete QR_code;
    QR_code=nullptr;
    delete Logo;
    Logo=nullptr;
    delete End_PageGround;
    End_PageGround=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
}

void End_Page::SetResult(QString Result)
{
    Title->setText(Result);
}

void End_Page::End_Page_Layout()
{
    Title->SetMyFont();
    Outline->SetMyFont();
    Picturn();
    GridLayout->addWidget(Logo,1,2);
    GridLayout->addWidget(Title,2,2);
    GridLayout->addWidget(Outline,3,1,1,3);
    GridLayout->addWidget(QR_code,4,2);
    GridLayout->setColumnStretch(0,1);
    GridLayout->setRowStretch(0,1);
    GridLayout->setColumnStretch(5,1);
    GridLayout->setRowStretch(5,1);
    Logo->resize(200,200);
    this->setLayout(GridLayout);
}

void End_Page::End_Page_Setbackground()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    End_PageGround->SetBackGround(this,":/BackGround/BackGround_Public");
}

void End_Page::Picturn()
{
    //标志
    Logo->setStyleSheet("QToolButton{border:Opx}");
    Logo->setIconSize(QSize(300,300));
    QPixmap PixmapLogo(":/Logo/Logo");
    Logo->setAutoRaise(true);
    Logo->setIcon(QIcon(PixmapLogo));
    //二维码
    QR_code->setStyleSheet("QToolButton{border:Opx}");
    QR_code->setIconSize(QSize(300,300));
    QPixmap PixmapQR_code(":/QR_Code/QR_QQ");
    QR_code->setAutoRaise(true);
    QR_code->setIcon(QIcon(PixmapQR_code));
}
