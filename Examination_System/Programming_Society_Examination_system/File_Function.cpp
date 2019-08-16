/*************************************************************************
    > File Name: File_Function.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月27日 星期五 14时25分10秒
    > Functional： File read and write operation
 ************************************************************************/
#include "File_Function.h"

File_Function::File_Function()
{

}

bool File_Function::Random(QList<Questions> &RandomList)
{
    /*
     *  随机抽号，不重复功能
     * */
    int End=RandomList.size();
    int i,j;
    QList<int> numbersList;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (i=0; i<End; i++)
    {
         numbersList.append(qrand()%End);
         bool flag=true;
         while (flag)
         {
             for (j=0;j<i;j++)
                if(numbersList[i]==numbersList[j])
                    break;
             if(j<i)   numbersList[i]=rand()%End;
             if(j==i)  flag=!flag;
         }
    }
    for(i=0;i<End;i++)
    {
        //将id随机赋值，不重复功能赋值进链表
       RandomList[i].ID = numbersList[i];
    }
}
bool File_Function::Text_Read_Public(QString& Address, QString& Read)
{
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         while ( !in.atEnd() )
         {
            Read += in.readLine() ;
         }
         file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Rx000P", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    return true;
}

bool File_Function::Text_Read_Configure_Server(QString &Address, IPAddress* Read)
{
    QString P;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         while ( !in.atEnd() )
         {
            Read->IP= in.readLine() ;
            P= in.readLine() ;
            Read->Port=P.toInt();
         }
         file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "服务器自动自动配置失败，请联系手动配置", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    return true;
}

bool File_Function::Text_Write_Information(QString & Address, UserInformation * User)
{
    QFile file(Address);
   if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
   {
       QTextStream out(&file);
       out <<"姓名：" +User->UserName<<endl ;
       out <<"年级：" +User->UserGrade<<endl ;
       out <<"专业：" +User->UserMajoy<<endl ;
       out <<"邮箱：" +User->UserMail<<endl ;
       out <<"手机：" +User->UserTelephone<<endl ;
       out <<"QQ：" +User->UserQQ<<endl ;
       out <<"选择题：" +QString::number(User->UserMultipleScore)<<endl ;
       out <<"判断题：" +QString::number(User->UserRecognizedScore)<<endl ;
       out <<"填空题：" +QString::number(User->UserCompletionScore)<<endl ;
       out <<"打码题：" +QString::number(User->UserCodeScore)<<endl ;
       out <<"总分：" +QString::number(User->UserTotalScore)<<endl ;
       file.close();
   }
   else
   {
       QMessageBox::information(NULL, "提示", "保存出差错，错误代码：Wx000U", QMessageBox::Yes , QMessageBox::Yes);
       return false;
   }
    return true;
}

bool File_Function::Text_Read_Choice(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         while ( !in.atEnd() )
         {
            temp.Subject = in.readLine() ;
            temp.Choice_A = in.readLine() ;
            temp.Choice_B = in.readLine() ;
            temp.Choice_C = in.readLine() ;
            temp.ChoiceAnswer =in.readLine() ;
            ReadList<<temp;
         }
         file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Rx000C", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}
bool File_Function::Text_Write_Choice(QString& Address, QList<Questions> &WriteList)
{
   QFile file(Address);
   if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
   {
       QTextStream out(&file);
       for (int i=0;i !=WriteList.size();i++ )
       {
           out << WriteList[i].Subject ;
           out << WriteList[i].Choice_A ;
           out << WriteList[i].Choice_B ;
           out << WriteList[i].Choice_C ;
           out << WriteList[i].ChoiceAnswer ;
       }
       file.close();
   }
   else
   {
       QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000C", QMessageBox::Yes , QMessageBox::Yes);
       return false;
   }
    return true;
}

bool File_Function::Text_Read_Judgment(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         while( !in.atEnd() )
         {
            temp.Subject = in.readLine() ;
            if ("T"==in.readLine()) temp.JudgmentAnswer =true;
            ReadList << temp ;
         }
         file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Rx000J", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}

bool File_Function::Text_Write_Judgment(QString& Address, QList<Questions>& WriteList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream out(&file);
        for (int i=0;i !=WriteList.size();i++ )
        {
             out << WriteList[i].Subject ;
             out << WriteList[i].JudgmentAnswer ;
        }
        file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000J", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    return true;
}

bool File_Function::Text_Read_Completion(QString& Address, QList<Questions> &ReadList)
{
    QString len;
    Questions temp;
    QFile file(Address);
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         while ( !in.atEnd() )
         {
            temp.Subject = in.readLine() ;
            len = in.readLine();
            temp.ComLength = len.toInt() ;
            for (int i=0; i < temp.ComLength; i++)
                 temp.Completion[i] = in.readLine() ;
            ReadList << temp ;
            temp.Clear_Comlention();
         }
         file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：0x000P", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}
bool File_Function::Text_Write_Completion(QString& Address, QList<Questions> &WriteList)
{
    QFile file(Address);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream out(&file);
        for (int i=0;i !=WriteList.size();i++ )
        {
            out << WriteList[i].Subject ;
            out << WriteList[i].ComLength ;
            for(int j=0; j < WriteList[i].ComLength; j++)
                out << WriteList[i].Completion[j] ;
        }
        file.close();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000C", QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }
     return true;
}

bool File_Function::Bin_Read_Public(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);
        while ( !in.atEnd() )
        {
            in.setVersion(QDataStream::Qt_4_7);
            in >> temp.Subject ;
            ReadList << temp ;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000P", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}

bool File_Function::Bin_Write_Public(QString& Address, QList<Questions> &WriteList)
{
    QFile file(Address);
    if( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);
        for (int i = 0; i != WriteList.size(); i++)
        {
            out.setVersion(QDataStream::Qt_4_7);
            out << WriteList[i].Subject ;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000P", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
     return true;
}

bool File_Function::Bin_Read_Choice(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);
        while ( !in.atEnd() )
        {
            in.setVersion(QDataStream::Qt_4_7);
            in >> temp.Subject ;
            in >> temp.Choice_A ;
            in >> temp.Choice_B ;
            in >> temp.Choice_C ;
            in >> temp.ChoiceAnswer ;
            ReadList<<temp ;
        }
        file.close();

    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000C", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}

bool File_Function::Bin_Write_Choice(QString& Address, QList<Questions> &WriteList)
{
    QFile file(Address);
    if( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);
        for (int i = 0; i != WriteList.size(); i++)
        {
            out.setVersion(QDataStream::Qt_4_7);
            out << WriteList[i].Subject ;
            out << WriteList[i].Choice_A ;
            out << WriteList[i].Choice_B ;
            out << WriteList[i].Choice_C ;
            out << WriteList[i].ChoiceAnswer ;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000C", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
     return true;
}

bool File_Function::Bin_Read_Judgment(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file(Address);
    if ( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);
        while ( !in.atEnd() )
        {
            in.setVersion(QDataStream::Qt_4_7);
            in >> temp.Subject;
            in >> temp.JudgmentAnswer ;
            ReadList<<temp;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000J", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}

bool File_Function::Bin_Write_Judgment(QString& Address, QList<Questions> &WriteList)
{
    QFile file(Address);
    if ( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);
        for (int i = 0; i != WriteList.size(); i++)
        {
            out.setVersion(QDataStream::Qt_4_7);
            out << WriteList[i].Subject ;
            out << WriteList[i].JudgmentAnswer;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000J", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    return true;
}

bool File_Function::Bin_Write_Information(QString & Address, UserInformation *User)
{
    QFile file(Address);
    if ( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_7);
        out <<"姓名：" +User->UserName;
        out <<"年级：" +User->UserGrade;
        out <<"专业：" +User->UserMajoy;
        out <<"邮箱：" +User->UserMail;
        out <<"手机：" +User->UserTelephone;
        out <<"QQ：" +User->UserQQ;
        out <<"选择题：" +QString::number(User->UserMultipleScore);
        out <<"判断题：" +QString::number(User->UserRecognizedScore);
        out <<"填空题：" +QString::number(User->UserCompletionScore);
        out <<"打码题：" +QString::number(User->UserCodeScore) ;
        out <<"总分：" +QString::number(User->UserTotalScore) ;
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx000J", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    return true;
}

bool File_Function::Bin_Read_Completion(QString& Address, QList<Questions> &ReadList)
{
    Questions temp;
    QFile file3(Address);
    if ( file3.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file3);
        while ( !in.atEnd() )
        {
            in.setVersion(QDataStream::Qt_4_7);
            in >> temp.Subject;
            in >> temp.ComLength;
            for (int i=0; i<temp.ComLength; i++)
                in >> temp.Completion[i] ;
            ReadList << temp ;
            temp.Clear_Comlention() ;
        }
        file3.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Rx00CL", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
    for (int i=0;i !=ReadList.size();i++ )
            if(!Random(ReadList)) return false;
     return true;
}

bool File_Function::Bin_Write_Completion(QString& Address, QList<Questions> &WriteList)
{
    QFile file(Address);
    if ( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);
        for (int i = 0; i != WriteList.size(); i++)
        {
            out.setVersion(QDataStream::Qt_4_7);
            out << WriteList[i].Subject ;
            out << WriteList[i].ComLength ;
            for(int j=0; j < WriteList[i].ComLength; j++)
                out << WriteList[i].Completion[j] ;
        }
        file.close();
    }
    else
    {
          QMessageBox::information(NULL, "提示", "题库加载失败，错误代码：Wx00CL", QMessageBox::Yes , QMessageBox::Yes);
          return false;
    }
     return true;
}
