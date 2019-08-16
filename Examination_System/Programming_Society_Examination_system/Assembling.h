/*************************************************************************
    > File Name: Assembling.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月10日 星期四 13时09分41秒
    > Functional: Window assembly
 ************************************************************************/
#ifndef ASSEMBLING_H
#define ASSEMBLING_H

#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QTcpSocket>
#include <cctype>
#include <QAbstractSocket>
#include <QMessageBox>
#include "IPAddress.h"
#include "File_Function.h"
#include "Selection_System.h"
#include "Login.h"
#include "InFormation.h"
#include "MainSystem.h"
#include "Selection_System.h"
#include "End_Page.h"
#include "File_Function.h"
#include "UserInformation.h"
#include "Configure_Server.h"
#include <synchapi.h>
class Assembling : public QWidget
{
    Q_OBJECT
public:
    explicit Assembling(QWidget *parent = nullptr);
    ~Assembling();
    void MyShow();
private:
    //服务器连接状态
    static bool Server;
    //创建客户端TCP协议
    QTcpSocket* TcpClient;
    //创建用户信息
    UserInformation m_iUserInformation;
    //创建登入窗口
    Login* m_iLogin;
    //获取服务器IP地址
    IPAddress* ipAddress;
    //获取服务器端口号
    Configure_Server* m_Configure_Server;
    //创建考试确认窗口
    InFormation* m_iInFormation;
    //创建选择题系统
    Selection_System* m_iSelection_System;
    //判断选择题是否有进入记录
    bool Into;
    //创建考试主系统
    MainSystem* m_iMainSystem;
    //成绩本地文件备份实现
    File_Function* File;
    //创建结束页面
    End_Page* End;
    //判断是否是中文
    bool Chinese(QString src);
    //判断是否是邮箱，仅实现判断是否含@功能
    bool Mail(QString src);
signals:
public slots:
    //登入页面切换按钮单击事件
    void Login_Click();
    //登入页面配置服务端功能按钮单击事件
    void Server_Click();
    //考试信息页面切换按钮单击事件
    void Login_InFormation_Click();
    //进入选择题系统页面切换按钮单击事件
    void Into_Click();
    //选择题系统页面退出按钮单击事件
    void Selection_Click();
    //主考试界面退出按钮单击事件
    void Assignment_Click();
    //结束退出按钮单击事件
    void END_Click();
    //服务端连接事件
    void DisplayConnect();
    //服务端断开事件
    void DisplayDisconnect();
    //服务端错误事件
    void onError(QAbstractSocket::SocketError socketError);


};

#endif // ASSEMBLING_H
