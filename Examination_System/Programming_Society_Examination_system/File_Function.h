/*************************************************************************
    > File Name: File_Function.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月27日 星期五 14时25分10秒
    > Functional： File read and write operation
 ************************************************************************/
#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H

#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <QTime>
#include <QTextCodec>
#include <QString>
#include <QList>
#include <QMessageBox>
#include "Questions.h"
#include "UserInformation.h"
#include "MyTextBrowser.h"
#include "IPAddress.h"

class File_Function
{
public:
    /*
     *  文件读写 Text：文字读写，Bin：二进制读写
     * */
    File_Function();
    //随机数生成，实现随机抽题
    bool  Random(QList<Questions> &RandomList);
    bool Text_Read_Public(QString&, QString&);
    bool Text_Read_Configure_Server(QString& Address, IPAddress* Read);
    bool Text_Write_Information(QString&, UserInformation*);
    bool Text_Read_Choice(QString&, QList<Questions>&);
    bool Text_Write_Choice(QString&, QList<Questions>&);
    bool Text_Read_Judgment(QString&, QList<Questions>&);
    bool Text_Write_Judgment(QString&, QList<Questions>&);
    bool Text_Read_Completion(QString&, QList<Questions>&);
    bool Text_Write_Completion(QString&, QList<Questions>&);
    bool Bin_Read_Public(QString&, QList<Questions>&);
    bool Bin_Write_Public(QString&, QList<Questions>&);
    bool Bin_Read_Choice(QString&, QList<Questions>&);
    bool Bin_Write_Choice(QString&, QList<Questions>&);
    bool Bin_Read_Judgment(QString&, QList<Questions>&);
    bool Bin_Write_Judgment(QString&, QList<Questions>&);
    bool Bin_Write_Information(QString&, UserInformation*);
    bool Bin_Read_Completion(QString&, QList<Questions>&);
    bool Bin_Write_Completion(QString&, QList<Questions>&);
};

#endif // FILE_FUNCTION_H
