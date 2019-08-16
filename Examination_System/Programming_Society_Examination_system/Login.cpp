/*************************************************************************
    > File Name: Login.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月10日 星期一 13时12分38秒
    > Functional： Login interface
 ************************************************************************/
#include "Login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    //设置窗口大小不变
    Desktop=new QDesktopWidget();
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setFixedSize(Desktop->width(),Desktop->height());
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    Help=new Help_Form();
    Help->hide();
    Login_BackGround=new BackGround();
    Exit_Button=new MyButton("登入",this);
    Cancel=new MyButton("取消",this);
    edit=new MyLineEdit[6];
    label=new MyLabel[6]{};
    Title=new MyLabel[4]{};
    QString LogoAddress=":/Logo/Logo";
    QString HelpAddress=":/Logo/Help";
    Picture_Logo=new QToolButton(this);
    Picture_Help=new QToolButton(this);
    Software=new QRadioButton("软件/游戏开发方向",this);
    Website=new QRadioButton("网站大佬开发方向",this);
    pLayout = new QGridLayout();
    this->Login_Setbackground();
    this->Login_Title();
    this->Login_Label();
    this->Login_Edit();
    this->Login_Picture();
    this->Login_Class();
    this->Login_Layout();
    connect(Picture_Help,SIGNAL(clicked(bool)),this,SLOT(Help_Click()));
    connect(Cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

Login::~Login()
{
    delete[] label;
    label=nullptr;
    delete[] Title;
    Title=nullptr;
    delete[] edit;
    edit=nullptr;
    delete Help;
    Help=nullptr;
    delete Login_BackGround;
    Login_BackGround=nullptr;
    delete pLayout;
    pLayout=nullptr;
    delete Picture_Logo;
    Picture_Logo=nullptr;
    delete Picture_Help;
    Picture_Help=nullptr;
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Cancel;
    Cancel=nullptr;
}

void Login::GetUserInformation(UserInformation& User)
{
    User.UserName=edit[0].text();
    User.UserGrade=edit[1].text();
    User.UserMajoy=edit[2].text();
    User.UserTelephone=edit[3].text();
    User.UserQQ=edit[4].text();
    User.UserMail=edit[5].text();
}

void Login::Login_Setbackground()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    Login_BackGround->SetBackGround(this,":/BackGround/BackGround_Login");
}

void Login::Login_Picture()
{
    Picture_Logo->setStyleSheet("QToolButton{border:Opx}");
    Picture_Logo->setIconSize(QSize(200,200));
    QPixmap PixmapLogo(":/Logo/Logo");
    Picture_Logo->setAutoRaise(true);
    Picture_Logo->setIcon(QIcon(PixmapLogo));
    Picture_Help->setStyleSheet("QToolButton{border:Opx}");
    Picture_Help->setIconSize(QSize(400,200));
    QPixmap PixmapHelp(":/Logo/Help");
    Picture_Help->setAutoRaise(true);
    Picture_Help->setIcon(QIcon(PixmapHelp));
    Picture_Logo->show();
    Picture_Help->show();

}

void Login::Login_Class()
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    ft.setFamily("华文新魏");
    Software->setFont(ft);
    Website->setFont(ft);
    //创建调色板
    QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    Software->setPalette(pa);
    Website->setPalette(pa);
}

void Login::Login_Label()
{
    QString Tetx_Label[6]{"姓名","年级","专业","电话","QQ","邮箱"};
    for(int i=0;i<6;i++)
    {

          label[i].setText(Tetx_Label[i]);
          label[i].setParent(this);
          label[i].show();

    }
}

void Login::Login_Edit()
{
    QString Tetx_Label[6]{"姓名","年级","专业","电话","QQ","邮箱"};
    for(int i=0;i<6;i++)
    {
        edit[i].setPlaceholderText("请输入"+Tetx_Label[i]);
    }
    edit[1].setPlaceholderText("例如：1701");
}

void Login::Login_Layout()
{
    pLayout->addWidget(&Title[0],0,1,Qt :: AlignHCenter);
    pLayout->addWidget(Picture_Logo,0,2,1,2,Qt :: AlignHCenter);
    pLayout->addWidget(&Title[1],0,4,Qt :: AlignHCenter);
    static int x=2;
    for(int i=0;i<6;i++,x++)
    {

         pLayout->addWidget(&label[i],x,2);
         pLayout->addWidget(&edit[i],x,3);

    }
    //设置按钮位置
    pLayout->addWidget(Software,x++,2,1,2);
    pLayout->addWidget(Website,x++,2,1,2);
    pLayout->addWidget(Exit_Button,x++,2,1,2);
    pLayout->addWidget(Cancel,x++,2,1,2);
    //设置位置
    pLayout->setColumnStretch(1,1);
    pLayout->setRowStretch(1,1);
    pLayout->setColumnStretch(x++,1);
    pLayout->setRowStretch(x++,1);
    pLayout->addWidget(Picture_Help,14,4);
    this->setLayout(pLayout);
}

void Login::Login_Title()
{
    QString Str_Title[4]{"Programming Society","Examination System"};
    for(int i=0;i<2;i++)
    {
        Title[i].setParent(this);
        Title[i].setText(Str_Title[i]);
        Title[i].SetMyFont(72,"Edwardian Script ITC");
        Title[i].show();
    }
}

void Login::Help_Click()
{
    Help->show();
}
