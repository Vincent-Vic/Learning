/*************************************************************************
    > File Name: ClientSocket.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期四 19时55分42秒
    > Functional： Client Socket
 ************************************************************************/
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "../Library/MyTextBrowser.h"
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* Socket,QTableWidget* Tab,QObject *parent = nullptr);
private:
    QTcpSocket* Socket;
    QTableWidgetItem* Item;
    QTableWidget* Tab;
    static int index;
    void Excel(QTableWidget *table,QString title);
signals:

public slots:
    void onReady();
};

#endif // CLIENTSOCKET_H
