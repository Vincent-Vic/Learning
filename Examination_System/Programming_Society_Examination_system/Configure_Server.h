/*************************************************************************
    > File Name: Configure_Server.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月12日 星期六 16时20分19秒
    > Functional： Configure Server
 ************************************************************************/
#ifndef CONFIGURE_SERVER_H
#define CONFIGURE_SERVER_H

#include <QWidget>
#include <QGridLayout>
#include <QBitmap>
#include <QPixmap>
#include <QMouseEvent>
#include <QRect>
#include <QMessageBox>
#include "IPAddress.h"
#include "../Library/MyLabel.h"
#include "File_Function.h"
#include "../Library/MyButton.h"
#include "../Library/MyLineEdit.h"
#include "../Library/BackGround.h"
#include "../Library/MyPicTure.h"
#include "File_Function.h"

class Configure_Server : public QWidget
{
    Q_OBJECT
public:
    explicit Configure_Server(IPAddress* ipAddress,QWidget *parent = nullptr);
    ~Configure_Server();
private:
    /*
     *  界面控件及布局
     * */
    IPAddress* ipAddress;
    MyLabel* Prompt;
    MyLabel* IPAddressPrompt;
    MyLabel* PortCodePrompt;
    MyLineEdit* GetIPAddress;
    MyLineEdit* GetPortCode;
    QGridLayout *GridLayout;
    MyButton* Exit_Button;
    MyButton* Cancel;
    MyPicTure* BackGroundPicturn;
    BackGround* Login_BackGround;
    QString* Configure_Data;
    File_Function* Configure_File;
    void Configure_Setbackground();
    void Configure_Server_Layout();
protected:
    /*
     *  不规则窗口实现函数
     * */
    void  mouseMoveEvent(QMouseEvent *event);
    void  mousePressEvent(QMouseEvent *event);
    void  mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint mouseMovePos;
signals:

public slots:
    //退出单击事件
    void Exit_Click();
};

#endif // CONFIGURE_SERVER_H
