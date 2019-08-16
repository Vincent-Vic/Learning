/*************************************************************************
    > File Name: Assembling.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月10日 星期四 13时09分41秒
    > Functional： Window assembly
 ************************************************************************/
#include "Assembling.h"
bool Assembling::Server=false;
Assembling::Assembling(QWidget *parent) : QWidget(parent),Into(false)
{
    //通过窗口类连接各界面，本界面无需显示
    this->setVisible(false);
    /*
     *      生成各个界面
     * */
    m_iLogin=new Login();
    ipAddress=new IPAddress();
    m_iInFormation=new InFormation();
    m_Configure_Server=new Configure_Server(ipAddress);
    File=new File_Function();
    m_iSelection_System=new Selection_System;
    m_iMainSystem=new MainSystem(&m_iUserInformation);
    End=new End_Page();
    /*
     *  服务端创建连接
     * */
    TcpClient=new QTcpSocket();
    connect(TcpClient,&QTcpSocket::connected,this,&Assembling::DisplayConnect);//连接
    connect(TcpClient,&QTcpSocket::disconnected,this,&Assembling::DisplayDisconnect);//断开
    connect(TcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError(QAbstractSocket::SocketError)));
}

Assembling::~Assembling()
{
    //释放内存
    delete End;
    End=nullptr;
    delete m_iSelection_System;
    m_iSelection_System=nullptr;
    delete m_iMainSystem;
    m_iMainSystem=nullptr;
}

void Assembling::MyShow()
{
    /*
     *  初始化窗口显示隐藏初始值-登入页面显示
     * */
    m_iLogin->setVisible(true);
    m_Configure_Server->setVisible(false);
    m_iInFormation->setVisible(false);
    m_iMainSystem->_Hide();
    m_iSelection_System->setVisible(false);
    End->setVisible(false);
    /*
     *   连接各功能信号和槽
     * */
    connect(m_iLogin->Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Login_Click()));
    connect(m_iLogin->Picture_Logo,SIGNAL(clicked(bool)),this,SLOT(Server_Click()));
    connect(m_iInFormation->Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Login_InFormation_Click()));
    connect(m_iMainSystem->Choice_button,SIGNAL(clicked(bool)),this,SLOT(Into_Click()));
    connect(m_iMainSystem->Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Assignment_Click()));
    connect(m_iSelection_System->Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Selection_Click()));
    connect(End->Logo,SIGNAL(clicked(bool)),this,SLOT(END_Click()));

}

bool Assembling::Chinese(QString src)
{

   int nCount = src.count();
   for(int i = 0 ; i < nCount ; i++)
   {
        QChar cha = src.at(i);
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            return true;
        }
    }
    return false;
}

bool Assembling::Mail(QString src)
{
    for(int i=0;i<src.size();i++)
    {
             if(src[i]=="@")
               return true;
    }
    return false;
}

/**
 * ---------------Login_Click-------------
 */
void Assembling::Login_Click()
{
    /*
     *  判断登入信息是否符合要求
     * */
    m_iLogin->GetUserInformation(m_iUserInformation);
    if(m_iUserInformation.UserName==""||m_iUserInformation.UserTelephone==""||m_iUserInformation.UserMail==""
            ||m_iUserInformation.UserMajoy==""||m_iUserInformation.UserQQ==""||m_iUserInformation.UserGrade=="")
    {
        QMessageBox::information(NULL, "提示", "信息填写不完整", QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    else if(m_iLogin->Software->isChecked())        m_iUserInformation.UserClass="软游方向";
    else if(m_iLogin->Website->isChecked())     m_iUserInformation.UserClass="网站方向";
    else
    {
            QMessageBox::information(NULL, "提示", "需要选择方向，如果不确定可以咨询纳新负责同学", QMessageBox::Yes , QMessageBox::Yes);
            return;
     }
    if(2>m_iUserInformation.UserName.size()||!Chinese(m_iUserInformation.UserName))
    {
            QMessageBox::information(NULL, "提示", "请填写正确的中文名字，有问题请联系纳新同学帮助！", QMessageBox::Yes , QMessageBox::Yes);
            return;
    }
    if(Chinese(m_iUserInformation.UserGrade)||2>m_iUserInformation.UserGrade.size())
    {
            QMessageBox::information(NULL, "提示", "无需加入中文，按照年级+班级，比如：1701！", QMessageBox::Yes , QMessageBox::Yes);
            return;
    }
    if(!Chinese(m_iUserInformation.UserMajoy))
    {
            QMessageBox::information(NULL, "提示", "请填写专业名称，有问题请联系纳新同学帮助！", QMessageBox::Yes , QMessageBox::Yes);
            return;
    }
    if(11< m_iUserInformation.UserTelephone.size()||11> m_iUserInformation.UserTelephone.size()||Chinese(m_iUserInformation.UserTelephone))
    {
            QMessageBox::information(NULL, "提示", "电话信息有误", QMessageBox::Yes , QMessageBox::Yes);
            return;
     }
    if(5> m_iUserInformation.UserQQ.size()||11< m_iUserInformation.UserQQ.size()||Chinese(m_iUserInformation.UserTelephone))
    {
            QMessageBox::information(NULL, "提示", "QQ信息有误", QMessageBox::Yes , QMessageBox::Yes);
            return;
     }
    if(!Mail(m_iUserInformation.UserMail)||10>m_iUserInformation.UserMail.size()||30<m_iUserInformation.UserMail.size())
    {
        QMessageBox::information(NULL, "提示", "邮箱信息有误", QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    TcpClient->abort();
    TcpClient->connectToHost(ipAddress->IP,ipAddress->Port);
    m_iLogin->close();
    delete m_iLogin;
    m_iLogin=nullptr;
    m_iInFormation->show();
}

void Assembling::Server_Click()
{
    m_Configure_Server->setVisible(true);
}

void Assembling::Login_InFormation_Click()
{
    if(!m_iInFormation->Treaty_Selected)
    {
            QMessageBox::information(NULL, "提示", "需要同意，如有对章程有异议\n请向纳新同学反馈", QMessageBox::Yes , QMessageBox::Yes);
            return;
    }
    m_iInFormation->close();
    delete m_iInFormation;
    m_iInFormation=nullptr;
    m_iMainSystem->_Show();
    m_iMainSystem->showFullScreen();

}

void Assembling::Into_Click()
{
    if(Into)
    {
        QMessageBox::information(NULL, "提示", "你无法进入第二次！！！", QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    Into=true;
    m_iMainSystem->setVisible(false);
    m_iSelection_System->setVisible(true);
}

void Assembling::Selection_Click()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出选择题考试系统"),
    QString(tr("警告：是否确认保存并退出选择题系统，无法再次进入?")),QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No)
    {
          return;
    }
    else if (button == QMessageBox::Yes)
    {
        //获取选择题成绩
        m_iUserInformation.UserMultipleScore=m_iSelection_System->GetChoice_Score();
        m_iSelection_System->close();
        m_iMainSystem->setVisible(true);
    }
}

void Assembling::Assignment_Click()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出选择题考试系统"),QString(tr("是否确认无误，交卷?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No)
    {
        return;
    }
    else if (button == QMessageBox::Yes)
    {
        //获取判断题成绩
        m_iUserInformation.UserRecognizedScore=m_iMainSystem->GetRecognizedScore();
        //获取填空题成绩
        m_iUserInformation.UserCompletionScore=m_iMainSystem->GetCompletionScore();
        //获取打码题成绩
        m_iUserInformation.UserCodeScore=m_iMainSystem->GetCodeScore();
        //计算总成绩
        m_iUserInformation.UserTotalScore= m_iUserInformation.UserMultipleScore+m_iUserInformation.UserRecognizedScore+m_iUserInformation.UserCompletionScore+ m_iUserInformation.UserCodeScore;
        /*
         *  创建文件夹，并写本地备份成绩
         * */
        QString FileAddress=QCoreApplication::applicationDirPath();
        QDir *temp = new QDir;
        bool exist = temp->exists(FileAddress+"//Mysterious");
        if(!exist)
                 temp->mkdir(FileAddress+"//Mysterious");
         QString Address=FileAddress+"\\Mysterious\\"+m_iUserInformation.UserName+".dll";
         File->Bin_Write_Information(Address,&m_iUserInformation);
         /*
          *     向服务端发送用户信息及成绩
          * */
         QByteArray buff;
         QDataStream out(&buff,QIODevice::WriteOnly);
         out.setVersion(QDataStream::Qt_5_6);
         out<<m_iUserInformation.UserName;
         out<<m_iUserInformation.UserGrade;
         out<<m_iUserInformation.UserMajoy;
         out<<m_iUserInformation.UserTelephone;
         out<<m_iUserInformation.UserQQ;
         out<<m_iUserInformation.UserMail;
         out<<m_iUserInformation.UserClass;
         out<<QString::number( m_iUserInformation.UserMultipleScore);
         out<<QString::number( m_iUserInformation.UserRecognizedScore);
         out<<QString::number( m_iUserInformation.UserCompletionScore);
         out<<QString::number( m_iUserInformation.UserCodeScore);
         out<<QString::number( m_iUserInformation.UserTotalScore);
         TcpClient->write(buff);
         QString Result=QString::number(m_iUserInformation.UserTotalScore,10);
         if(Server)
                End->SetResult("考试结束！<"+m_iUserInformation.UserName+">战绩为："+Result);
         else
                End->SetResult("由于服务端连接失败!\n请联系纳新同学手动录入！\n<"+m_iUserInformation.UserName+">战绩为："+Result);
        m_iMainSystem->close();
        End->setVisible(true);
    }
}

void Assembling::END_Click()
{
    End->close();
}

/**
 * @brief SAGNAL::DisplayConnect
 */
void Assembling::DisplayConnect()
{
    QMessageBox::information(NULL, "提示", "服务端连接成功", QMessageBox::Yes , QMessageBox::Yes);
    Server=true;
}

void Assembling::DisplayDisconnect()
{
    QMessageBox::information(NULL, "提示", "服务端已断开", QMessageBox::Yes , QMessageBox::Yes);
    Server=false;
}

void Assembling::onError(QAbstractSocket::SocketError socketError)
{
    Server=false;
    QMessageBox::critical(this,"服务器连接提示","服务端未连接，自动切换本地模式，请在考完找纳新同学手动登记！");
}
