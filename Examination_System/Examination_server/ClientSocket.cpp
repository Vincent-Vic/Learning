/*************************************************************************
    > File Name: ClientSocket.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期四 19时55分42秒
    > Functional： Client Socket
 ************************************************************************/
#include "ClientSocket.h"
int ClientSocket::index=0;
ClientSocket::ClientSocket(QTcpSocket* Socket,QTableWidget* Tab,QObject *parent) : Socket(Socket),Tab(Tab), QObject(parent)
{
    connect(Socket,SIGNAL(readyRead()),this,SLOT(onReady()));
}

void ClientSocket::onReady()
{
    QDataStream in(Socket);
    in.setVersion(QDataStream::Qt_5_6);
    QString information[12];
    for(int i=0;i<12;i++)
        in>>information[i];
    Item=new QTableWidgetItem[12];
    for(int i=0;i<12;i++)
    {
        Item[i].setTextColor(QColor(255,255,255));
        Item[i].setText(information[i]);
        Item[i].setTextAlignment(Qt::AlignCenter);
        Tab->setItem(index,i,&Item[i]);
    }
    index++;
}
