/*************************************************************************
    > File Name: Login.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月10日 星期一 13时12分38秒
    > Functional： Login interface
 ************************************************************************/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QCompleter>
#include <QStringList>
#include <QToolButton>
#include <QRadioButton>
#include <QDesktopWidget>
#include "../Library/BackGround.h"
#include "UserInformation.h"
#include "../Library/MyPicTure.h"
#include "Help_Form.h"
#include "event_filter.h"
#include "../Library/MyButton.h"
#include "../Library/MyLineEdit.h"
#include "../Library/MyTextEdit.h"
#include "../Library/MyLabel.h"

class Login : public QWidget
{
    Q_OBJECT
public:
    /*
     *  界面按钮控件及布局实现
     * */
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    MyButton* Exit_Button;
    QRadioButton* Software;
    QRadioButton* Website;
    QToolButton* Picture_Logo;
    void GetUserInformation(UserInformation& User);
private:
    QDesktopWidget *Desktop;
    Help_Form* Help;
    MyButton* Cancel;
    BackGround* Login_BackGround;
    MyLabel* label;
    MyLabel* Title;
    MyLineEdit* edit;
    QGridLayout *pLayout;
    QToolButton* Picture_Help;
    QString Class;
    void Login_Setbackground();
    void Login_Picture();
    void Login_Class();
    void Login_Label();
    void Login_Edit();
    void Login_Layout();
    void Login_Title();


signals:

public slots:
    void Help_Click();
};

#endif // LOGIN_H
