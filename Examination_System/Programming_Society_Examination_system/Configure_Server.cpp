/*************************************************************************
    > File Name: Configure_Server.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月12日 星期六 16时20分19秒
    > Functional： Configure Server
 ************************************************************************/
#include "Configure_Server.h"

Configure_Server::Configure_Server(IPAddress* ipAddress,QWidget *parent) : ipAddress(ipAddress), QWidget(parent)
{
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    Configure_File=new File_Function;
    QString Address="Server1.txt";
    if(Configure_File->Text_Read_Configure_Server(Address,ipAddress))
    {
        ipAddress->IP="127.0.0.";
        ipAddress->Port=808;
    }
    Configure_Setbackground();
    Prompt=new MyLabel("\t配置服务端\n",this);
    IPAddressPrompt=new MyLabel("服务端IP：",this);
    PortCodePrompt=new MyLabel("端口：",this);
    GetIPAddress=new MyLineEdit(this);
    GetIPAddress->setText(ipAddress->IP);
    GetPortCode=new MyLineEdit(this);
    GetPortCode->setText(QString::number(ipAddress->Port));
    GridLayout=new QGridLayout();
    Exit_Button=new MyButton("确定",this);
    Cancel=new MyButton("取消",this);
    Configure_Server_Layout();
    connect(Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Exit_Click()));
    connect(Cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

Configure_Server::~Configure_Server()
{
    delete Configure_File;
    Configure_File=nullptr;
    Configure_Data=nullptr;
    delete Prompt;
    Prompt=nullptr;
    delete IPAddressPrompt;
    IPAddressPrompt=nullptr;
    delete PortCodePrompt;
    PortCodePrompt=nullptr;
    delete GetIPAddress;
    GetIPAddress=nullptr;
    delete GetPortCode;
    GetPortCode=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Cancel;
    Cancel=nullptr;
}

void Configure_Server::Configure_Setbackground()
{
    resize(500,300);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap mask(":/BackGround/Small");//加载掩码图像
    setMask(QBitmap(mask.mask())); //设置窗体的掩码图像,抠除图像的白色区域实现不规则窗体
    QPalette p;//设置调色板
    p.setBrush(QPalette::Window, QBrush(mask));//将调色板的画刷设置为掩码位图,在不规则窗体上显示出掩码位图
    setPalette(p);
    mouseMovePos = QPoint(0, 0);
}

void  Configure_Server::mouseMoveEvent(QMouseEvent *event)//鼠标按下并移动则移动不规则窗体
{
if(mouseMovePos != QPoint(0, 0))
{
    move(geometry().x() + event->globalPos().x() - mouseMovePos.x(), geometry().y() + event->globalPos().y() - mouseMovePos.y());
    mouseMovePos = event->globalPos();
}
}

void  Configure_Server::mousePressEvent(QMouseEvent *event)
{
    mouseMovePos = event->globalPos();
}

void  Configure_Server::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMovePos = QPoint(0, 0);
}

void Configure_Server::Exit_Click()
{
    ipAddress->IP=GetIPAddress->text();
    ipAddress->Port=GetPortCode->text().toInt();
    if(""==ipAddress->IP&&0==ipAddress->Port)
        QMessageBox::information(NULL, "提示", "不能为空", QMessageBox::Yes , QMessageBox::Yes);
    else if(""==ipAddress->IP)
        QMessageBox::information(NULL, "提示", "IP不能为空", QMessageBox::Yes , QMessageBox::Yes);
    else if(0==ipAddress->Port)
        QMessageBox::information(NULL, "提示", "端口不能为空", QMessageBox::Yes , QMessageBox::Yes);
    else
            this->close();
}

void Configure_Server::Configure_Server_Layout()
{
    Prompt->SetMyFont();
    IPAddressPrompt->SetMyFont();
    PortCodePrompt->SetMyFont();
    GridLayout->addWidget(Prompt,1,0,1,2);
    GridLayout->addWidget(IPAddressPrompt,2,0);
    GridLayout->addWidget(GetIPAddress,2,1);
    GridLayout->addWidget(PortCodePrompt,3,0);
    GridLayout->addWidget(GetPortCode,3,1);
    GridLayout->addWidget(Exit_Button,4,0,1,2);
    GridLayout->addWidget(Cancel,5,0,1,2);
    GridLayout->setColumnStretch(0,1);
    GridLayout->setRowStretch(0,1);
    GridLayout->setColumnStretch(6,1);
    GridLayout->setRowStretch(6,1);
    this->setLayout(GridLayout);
}
