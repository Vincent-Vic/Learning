/*************************************************************************
    > File Name: IPAddress.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期二 15时46分38秒
    > Functional： IPAddress And Port information
 ************************************************************************/
#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>

class IPAddress
{
public:
    /*
     *  IP And Port 信息并初始化
     * */
    IPAddress(QString ip="127.0.0.1",int port=808);
    QString IP;
    int Port;
};

#endif // IPADDRESS_H
