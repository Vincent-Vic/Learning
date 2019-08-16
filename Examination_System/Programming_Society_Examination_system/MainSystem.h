/*************************************************************************
    > File Name: MainSystem.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月15日 星期六 14时14分18秒
    > Functional： Main examination system interface
 ************************************************************************/
#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>
#include <QTabWidget>
#include <QToolButton>
#include <QDesktopWidget>
#include "event_filter.h"
#include "../Library/MyButton.h"
#include "../Library/MyLineEdit.h"
#include "../Library/MyTextEdit.h"
#include "../Library/MyTextBrowser.h"
#include "../Library/MyLabel.h"
#include "Selection_System.h"
#include "File_Function.h"
#include "GroupRadioButton.h"
#include "Selection_System.h"
#include "UserInformation.h"
#include <QTime>
class MainSystem : public QWidget
{
    Q_OBJECT
public:
    explicit MainSystem(UserInformation* _User,QWidget *parent = nullptr);
    ~MainSystem();
    /*
     *  分数计算功能实现
     * */
    int GetRecognizedScore();    //用户判断题得分
    int GetCompletionScore();    //用户填空题得分
    int GetCodeScore();          //用户打码题得分
    void _Show();
    void _Hide();
    /*
     *  界面按钮控件及布局实现
     * */
    MyButton* Exit_Button;
    MyButton* Choice_button;
private:
    QDesktopWidget *Desktop;
    QToolButton* Picture_QR;
    MyLabel* QRP;
    QTabWidget* TabWidgetform;
    QTabWidget* TabWidget;
    QGridLayout* Tab_layout;
    QGridLayout* Glayout;
    QScrollArea* Sll;
    MyLabel* Prompt_Title;
    MyLabel* Tab_Text;
    QGridLayout *GridLayout;
    GroupRadioButton* JudgmentIf;
    MyLabel* JudgmentIfSubject;
    MyLabel* CompletionSubject;
    MyLineEdit* Completion_Content;
    MyTextBrowser* CodeSubject;
    MyTextEdit* CodeText;
    UserInformation* User;
    QString CodeSubjectTxet[6];
    QString CodeSubjectif;
    int CodeRand;
    int Choice_Score;
    QList<Questions> Judgment;
    QList<Questions> Completion;
    QList<Questions> Code;
    int RecognizedScore;    //用户判断题得分
    int CompletionScore;    //用户填空题得分
    int CodeScore;          //用户打码题得分
    void SetBackGround();
    void MainSystem_Layout();
    void Choice_Layout();
    void JudgmentAnswer_Layout();
    void Completion_Layout();
    void Code_Layout();
    void Enclosure_Layout();
    Questions* GetListElement(int Getid,QList<Questions>& Element);
signals:

private slots:
};

#endif // MAINFORM_H
