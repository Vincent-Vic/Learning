/*************************************************************************
    > File Name: MainServer.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期四 16时01分08秒
    > Functional： Main Server
 ************************************************************************/
#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <QThread>
#include <QtNetwork/QNetworkInterface.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QDataStream>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include <QHeaderView>
#include <QDesktopWidget>
#include "../Library/BackGround.h"
#include "../Library/MyLabel.h"
#include "../Library/MyButton.h"
#include "../Library/MyTextBrowser.h"
#include "../Library/ClientSocket.h"

class MainServer : public QWidget
{
    Q_OBJECT
public:
    explicit MainServer(QWidget *parent = nullptr);
    ~MainServer();
    int PortCode;
private:
    QDesktopWidget *Desktop;
    int Total;
    QTableWidget* TAB;
    QTimer* timer;
    MyLabel* Title;
    MyLabel* information;
    MyLabel* IPAddress;
    MyLabel* Port;
    MyLabel* Hour;
    MyLabel* Day;
    MyLabel* Week;
    MyLabel* State;
    MyButton* Eixt;
    MyButton* Monitor;
    MyTextBrowser* Message;
    MyTextBrowser* Display;
    QTcpServer* Server;
    QTcpSocket *clientConnection;
    BackGround* ServerBackGround;
    QGridLayout* GridLayout;
    QVBoxLayout* VBoxLayout;
    void Server_Table();
    void Server_Layout();
    void Server_Setbackground();
    //以Excel的形式保存
    void Excel(QTableWidget *table, QString title);
signals:

public slots:
    void Exit_Click();
    //绑定ip地址并开始监听
    void Listen();
    //客户端连接消息
    void Status();
    //客户端端口消息
    void DisplayDisconnect();
    //窗口刷新
    void Timer_Refresh();
};

#endif // MAINSERVER_H
