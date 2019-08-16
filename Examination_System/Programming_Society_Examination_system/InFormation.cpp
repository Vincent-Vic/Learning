/*************************************************************************
    > File Name: InFormation.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月01日 星期二 16时26分36秒
    > Functional： Examination information
 ************************************************************************/
#include "InFormation.h"

InFormation::InFormation(QWidget *parent) : QWidget(parent),Treaty_Selected(false)
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
    /*
     *      设置信息
     * */
    InFormationBackGround=new BackGround();
    GridLayout=new QGridLayout(this);
    InFormation_Setbackground();
    Title=new MyLabel("编程社考试须知！",this);
    Outline=new MyLabel("\t考试内容\n\n1、选择题\t15分\n2、判断题\t10分\n3、填空题\t10分\n4、打码题\t5分\n5、附加题（选做）\t25分\n6、总分40+25",this);
    Prompt=new MyLabel("\t考试须知\n1、选择题只能进入一次，无法再次进入\n2、附加题为选做，建议做，建议做，建议做！\n3、事情说三遍4、考试完成告点击完成退出\n确认无误离开，无需关机",this);
    ChoiceTreaty=new QCheckBox("我同意并遵守编程社",this);
    Logo=new MyPicTure(":/Logo/Logo",this);
    Exit_Button=new MyButton("开始考试",this);
    //实现打开word功能
    Treaty=new MyLabel(QString::fromUtf8 ("<style> a {text-decoration: none} </style><a href =Treaty.docx> 《编程社章程》 </a> <meta charste=\"utf-8\">"),this);
    Treaty->setOpenExternalLinks(true);
    InFormation_Layout();
    connect(ChoiceTreaty, SIGNAL(stateChanged(int)), this, SLOT(Treaty_Click(int)));
}

InFormation::~InFormation()
{
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Title;
    Title=nullptr;
    delete Outline;
    Outline=nullptr;
    delete Prompt;
    Prompt=nullptr;
    delete Treaty;
    Treaty=nullptr;
    delete ChoiceTreaty;
    ChoiceTreaty=nullptr;
    delete Logo;
    Logo=nullptr;
    delete InFormationBackGround;
    InFormationBackGround=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
}

void InFormation::InFormation_Layout()
{
    QFont ft;
    //设置字体大小
    ft.setPointSize(24);
    ft.setBold(true);
    ft.setFamily("宋体");
    ChoiceTreaty->setFont(ft);
    //创建调色板
    QPalette pa;
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::white);
    ChoiceTreaty->setPalette(pa);
    GridLayout->addWidget(Title,2,2,1,2);
    GridLayout->addWidget(Logo,3,1,2,2);
    GridLayout->addWidget(Outline,3,3,1,2);
    GridLayout->addWidget(Prompt,4,3,1,2);
    GridLayout->addWidget(ChoiceTreaty,5,2);
    GridLayout->addWidget(Treaty,5,3);
    GridLayout->addWidget(Exit_Button,6,2,1,2);
    GridLayout->setColumnStretch(0,1);
    GridLayout->setRowStretch(0,1);
    GridLayout->setColumnStretch(7,1);
    GridLayout->setRowStretch(7,1);
    Logo->resize(200,200);
    Title->show();
    Outline->show();
    Prompt->show();
    Logo->show();
    ChoiceTreaty->show();
    Treaty->show();
    Exit_Button->show();
    this->setLayout(GridLayout);
}

void InFormation::InFormation_Setbackground()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    InFormationBackGround->SetBackGround(this,":/BackGround/BackGround_Public");
}

void InFormation::Treaty_Click(int state)
{
        if (state == Qt::Checked) // "选中"
        {
           Treaty_Selected=true;
        }
        else if(state == Qt::Unchecked) // "未选"
        {
            Treaty_Selected=false;
        }
}
