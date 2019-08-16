/*************************************************************************
    > File Name: MainSystem.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月15日 星期六 14时14分18秒
    > Functional： Main examination system interface
 ************************************************************************/
#include "MainSystem.h"

MainSystem::MainSystem(UserInformation* _User,QWidget *parent) : QWidget(parent),RecognizedScore(0),CompletionScore(0),CodeScore(0),User(_User)
{
    //设置窗口大小不变
    Desktop=new QDesktopWidget();
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setFixedSize(Desktop->width(),Desktop->height());
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    this->SetBackGround();
    TabWidget=new QTabWidget();
    TabWidgetform=new QTabWidget[5];
    Tab_layout=new QGridLayout[5];     //tab内布局
    Glayout=new QGridLayout(); //窗体布局
    Sll = new QScrollArea(this);
    Sll->setGeometry(0, 0, 200, 200);
    Sll->setWidget(&TabWidgetform[0]);
    Choice_button=new MyButton("进入选择题",&TabWidgetform[0]);
    Exit_Button=new MyButton("确认交卷！",TabWidget);
    Prompt_Title=new MyLabel("",this);
    Tab_Text=new MyLabel("\t请单击本页面上的“ 进入选择题 ”，启动选择题测试程序，按照内容正确答题！\n\n\t选择题部分只能进入一次，退出后无法再次进入！",&TabWidgetform[0]);
    JudgmentIfSubject=new MyLabel[10];
    CompletionSubject=new MyLabel[10];
    CodeSubject=new MyTextBrowser("",this);
    JudgmentIf=new GroupRadioButton[10];
    Completion_Content=new MyLineEdit[10];
    Picture_QR=new QToolButton(this);
    QRP=new MyLabel("附加题在线作答\n请关注QQ公众号\n单击招募选择对应\n方向的附加卷\n",this);
    CodeText=new MyTextEdit("",&TabWidgetform[3]);
    /*
     *     设置打码题，题库
     * */
    CodeSubjectTxet[0]="#include<stdio.h>\nint main()\n{\n    int App;\n    printf(\"Hello World\");\n    printf(\"Programming Society!\");\n    scanf(\"%d\",&App);\n    return 0;\n}";
    CodeSubjectTxet[1]="#include<iostream>\nusing namespace std;\nint main()\n{\n    int App\n    cout(\"Hello World\");\n    cout(\"Programming Society!\");\n    cin>>App;\n    return 0;\n}";
    CodeSubjectTxet[2]="public class HelloWorld {\n    public static void main(String[] args){\n        System.out.println(\"Hello World!\");\n        System.out.println(\"Programming Society!\");\n    }\n}";
    CodeSubjectTxet[3]="#include<stdio.h>\nint main()\n{\n    int sum=0;\n    for(int i=0;i<100;i++)\n    {\n        sum += i;\n    cout<<\"sum:\"<<sum;\n    }\n    return 0;\n}";
    CodeSubjectTxet[4]="#include<iostream>\nusing namespace std;\nint main()\n{\n    int sum=0;\n    for(int i=0;i<100;i++)\n    {\n        sum += i;\n    printf(\"sum:%d\",sum);\n    }\n    return 0;\n}";
    CodeSubjectTxet[5]="public class HelloWorld {\n    public static void main(String[] args){\n        for(int i=0;i<100;i++){\n        sum += i;\n        System.out.println(\"sum:\"+sum);\n    }\n}";
    MainSystem_Layout();
}


MainSystem::~MainSystem()
{
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Choice_button;
    Choice_button=nullptr;
    delete[] TabWidgetform;
    TabWidgetform=nullptr;
    delete TabWidget;
    TabWidget=nullptr;
    delete[] Tab_layout;
    Tab_layout=nullptr;
    delete Glayout;
    Glayout=nullptr;
    delete Sll;
    Sll=nullptr;
    delete Prompt_Title;
    Prompt_Title=nullptr;
    delete Tab_Text;
    Tab_Text=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
    delete[] JudgmentIf;
    JudgmentIf=nullptr;
    delete[] JudgmentIfSubject;
    JudgmentIfSubject=nullptr;
    delete[] CompletionSubject;
    CompletionSubject=nullptr;
    delete CodeSubject;
    CodeSubject=nullptr;
    delete[] Completion_Content;
    Completion_Content=nullptr;
    delete CodeText;
    CodeText=nullptr;
    delete Picture_QR;
    Picture_QR=nullptr;
}
/*
 *     分数计算功能
 * */
int MainSystem::GetRecognizedScore()
{
    bool Judgment_IF;

    for(int i=0;i<10;i++)
    {
        QString JudgAnswer=JudgmentIf[i].Judgment_Options();
        if("Yes"==JudgAnswer)
            Judgment_IF=true;
        else if(("No"==JudgAnswer))
            Judgment_IF=false;
        else
            continue;
        Questions* Judgment_Answer;
        Judgment_Answer=GetListElement(i,Judgment);
        if (!Judgment_Answer) return -1;
        if (Judgment_IF==Judgment_Answer->JudgmentAnswer)
                RecognizedScore+=1;
        Judgment_Answer=nullptr;
    }
    return RecognizedScore;    //用户判断题得分
}

int MainSystem::GetCompletionScore()
{
    for(int i=0;i<10;i++)
    {
        Questions* Completion_Answer;
        Completion_Answer = GetListElement(i,Completion);
        if(!Completion_Answer)   return -1;
        for(int j=0;j<(Completion_Answer->ComLength);j++)
            if(Completion_Content[i].text()==Completion_Answer->Completion[j])
                CompletionScore+=1;
        Completion_Answer=nullptr;
    }
    return CompletionScore;    //用户填空题得分
}

int MainSystem::GetCodeScore()
{
    double Counter=0,TotalCounter=0;
    QString TempIf= CodeText->toPlainText();
    CodeSubjectif = CodeSubjectTxet[CodeRand];
    for(int i=0;i<CodeSubjectif.size();i++)
    {
        if(i!=TempIf.size())
        {
             if(TempIf[i]==CodeSubjectif[i])
             {
                Counter++;
             }
        }
        TotalCounter++;
    }
    CodeScore=5*(Counter/TotalCounter);
    return CodeScore;          //用户打码题得分
}

void MainSystem::_Show()
{
    this->setVisible(true);
    this->SetBackGround();
}

void MainSystem::_Hide()
{
    this->setVisible(false);
}
void MainSystem::SetBackGround()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    QString background_s=QString(":/BackGround/BackGround_Public");
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(background_s);
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    palette.staticMetaObject;
    this->setPalette(palette);
}

void MainSystem::MainSystem_Layout()
{
    QString Tab_Title[5]{"  选择题  ","  判断题  ","  填空题  ","  打码题  ","  附加题  "};
    this->Choice_Layout();
    this->JudgmentAnswer_Layout();
    this->Completion_Layout();
    this->Code_Layout();
    this->Enclosure_Layout();
    for(int i=0;i<5;i++)
    {
      TabWidget->addTab(&TabWidgetform[i],Tab_Title[i]);
      TabWidgetform[i].setStyleSheet("background-image:url(:/BackGround/BackGround_Public);");
      TabWidget->setStyleSheet("QTabWidget {font:bold 32px;color:red}");
      TabWidgetform[i].showFullScreen();
    }
    TabWidget->setDocumentMode(true);
    Glayout->addWidget(Exit_Button,0,0);
    Glayout->addWidget(TabWidget,1,0);
    this->setLayout(Glayout);
}
/*
 * 各个Tab窗口内的布局
 * */
void MainSystem::Choice_Layout()
{
    Tab_Text->adjustSize();
    Tab_Text->setGeometry(QRect(30, 30, 1000, 3*32));
    Tab_Text->setWordWrap(true);
    Tab_Text->setAlignment(Qt::AlignTop);
    Tab_Text->setAttribute(Qt::WA_TranslucentBackground);
    Tab_layout[0].addWidget(Tab_Text,1,1);
    Tab_layout[0].addWidget(Choice_button,2,1);
    Tab_layout[0].setColumnStretch(0,1);
    Tab_layout[0].setRowStretch(0,1);
    Tab_layout[0].setColumnStretch(3,1);
    Tab_layout[0].setRowStretch(3,1);
    TabWidgetform[0].setLayout(&Tab_layout[0]);
}

void MainSystem::JudgmentAnswer_Layout()
{
    File_Function *file=new File_Function();
    QString Address=":/Questions/Judgment";
    file->Bin_Read_Judgment(Address,Judgment);
    for(int i=0;i<10;i++)
    {
        Questions* temp;
        temp= GetListElement(i,Judgment);
        if(!temp) return;
        QString id=QString::number(i+1,10);
        JudgmentIfSubject[i].setText(id+"、"+temp->Subject);
        JudgmentIfSubject[i].setParent(&TabWidgetform[1]);
        JudgmentIfSubject[i].adjustSize();
        JudgmentIfSubject[i].show();
        JudgmentIf[i].RadioGroupBoxIf(&TabWidgetform[1]);
        Tab_layout[1].addWidget(&JudgmentIfSubject[i],i,0);
        Tab_layout[1].addWidget(JudgmentIf[i].GroupBoxJudgment,i,1);
        temp=nullptr;
    }
    TabWidgetform[1].setLayout(&Tab_layout[1]);
}

void MainSystem::Completion_Layout()
{
    File_Function *file=new File_Function();
    QString Address=":/Questions/Completion";
    file->Bin_Read_Completion(Address,Completion);
    for(int i=0;i<10;i++)
    {
        Questions* temp;
        temp= GetListElement(i,Completion);
        if(!temp) return;
        QString id=QString::number(i+1,10);
        CompletionSubject[i].setText(id+"、"+temp->Subject);
        CompletionSubject[i].setParent(&TabWidgetform[2]);
        CompletionSubject[i].adjustSize();
        CompletionSubject[i].show();
        Completion_Content[i].setParent(&TabWidgetform[2]);
        Completion_Content[i].setPlaceholderText("请在这里补充题目横线上的内容！");
        Completion_Content[i].show();
        temp=nullptr;
    }
    for(int i=0,j=0;i<10;i++,j+=2)
    {
        Tab_layout[2].addWidget(&CompletionSubject[i],j,0);
        Tab_layout[2].addWidget(&Completion_Content[i],j+1,0);
    }
    TabWidgetform[2].setLayout(&Tab_layout[2]);
}

void MainSystem::Code_Layout()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    CodeRand=rand()%6;
    CodeSubject->setParent(&TabWidgetform[3]);
    CodeSubject->setText(CodeSubjectTxet[CodeRand]);
    CodeText->setPlaceholderText("请将上面的字符挨个输入到这里,友情提醒：区分大小写,中英文,空格！可以通过鼠标查看空格数，本代码均为英文，再次提示四个空格(自己发现），请不要使用Tab，否则后果自负！！！！请切记不要漏打！！");
    Tab_layout[3].addWidget(CodeSubject,0,0);
    Tab_layout[3].addWidget(CodeText,1,0);
    TabWidgetform[3].setLayout(&Tab_layout[3]);
}

void MainSystem::Enclosure_Layout()
{
    Picture_QR->setStyleSheet("QToolButton{border:Opx}");
    Picture_QR->setIconSize(QSize(200,200));
    QPixmap PixmapQR(":/QR_Code/QR_QQPublic");
    Picture_QR->setAutoRaise(true);
    Picture_QR->setIcon(QIcon(PixmapQR));
    QRP->setAttribute(Qt::WA_TranslucentBackground);
    QRP->setAlignment(Qt::AlignCenter);
    Tab_layout[4].addWidget(Picture_QR,1,1,Qt :: AlignHCenter);
    Tab_layout[4].addWidget(QRP,2,1,Qt :: AlignHCenter);
    Tab_layout[4].setColumnStretch(0,1);
    Tab_layout[4].setRowStretch(0,1);
    Tab_layout[4].setColumnStretch(3,1);
    Tab_layout[4].setRowStretch(3,1);
    TabWidgetform[4].setLayout(&Tab_layout[4]);
}

Questions *MainSystem::GetListElement(int Getid, QList<Questions>& Element)
{
    for(int i=0;i<Element.size();i++)
        if(Getid==Element[i].ID)
            return &Element[i];
}
