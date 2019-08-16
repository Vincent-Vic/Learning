/*************************************************************************
    > File Name: Help_Form.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期日 13时18分16秒
    > Functional： Software information
 ************************************************************************/
#include "Help_Form.h"

Help_Form::Help_Form(QWidget *parent) : QWidget(parent)
{
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    //设置无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置大小
    resize(900,700);
    Picture_Logo=new MyPicTure(":/Logo/Logo",this,"0x00001L");
    Picture_QR_Code=new MyPicTure(":/QR_Code/QR_Public",this,"0x0000PQ");
    Picture_QR_offical=new MyPicTure(":/QR_Code/QR_offical",this,"0x0000OF");
    OK=new MyButton("确定",this);
    connect(OK, SIGNAL(clicked(bool)), this, SLOT(close()));
    Help_BackGround=new BackGround();
    Information=new MyLabel("\t\t    编程社考试系统\n\n版本：编程社纳新系统1.3\nCopyright © Mystery Engineer And Programming Society\n日期：2017年8月27日\n编程社官网：\n开发作者：软件/游戏开发方向-Vincent·Vic\n微信公众号：",this);
    Website=new MyLabel("<a href = www.xxbcs.win>单击打开编程社官网</a>",this);
    NewHelpForm();
}

Help_Form::~Help_Form()
{
    delete Picture_Logo;
    Picture_Logo=nullptr;
    delete Picture_QR_Code;
    Picture_QR_Code=nullptr;
    delete Help_BackGround;
    Help_BackGround=nullptr;
    delete Information;
    Information=nullptr;
    delete Website;
    Website=nullptr;
    delete OK;
    OK=nullptr;
}

void Help_Form::NewHelpForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    resize(1000,700);
    QPixmap mask(":/BackGround/BackGroundHelp");//加载掩码图像
    setMask(QBitmap(mask.mask())); //设置窗体的掩码图像,抠除图像的白色区域实现不规则窗体
    QPalette p;//设置调色板
    p.setBrush(QPalette::Window, QBrush(mask));//将调色板的画刷设置为掩码位图,在不规则窗体上显示出掩码位图
    setPalette(p);
    mouseMovePos = QPoint(0, 0);
    Information->setGeometry(50,150,900,400);
    Information->SetMyFont();
    Information->show();
    Website->setOpenExternalLinks(true);
    Website->setGeometry(230,375,300,50);
    Website->SetMyFont();
    Website->show();
    Picture_Logo->setGeometry(370,0,200,200);
    Picture_Logo->show();
    Picture_QR_Code->setGeometry(230,450,200,200);
    Picture_QR_Code->show();
    Picture_QR_offical->setGeometry(450,450,200,200);
    Picture_QR_offical->show();
    OK->setGeometry(700,600,100,50);
    OK->show();
}


void Help_Form::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseMovePos != QPoint(0, 0))
    {
        move(geometry().x() + event->globalPos().x() - mouseMovePos.x(), geometry().y() + event->globalPos().y() - mouseMovePos.y());
        mouseMovePos = event->globalPos();
    }
}

void Help_Form::mousePressEvent(QMouseEvent *event)
{
    mouseMovePos = event->globalPos();
}

void Help_Form::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMovePos = QPoint(0, 0);
}
