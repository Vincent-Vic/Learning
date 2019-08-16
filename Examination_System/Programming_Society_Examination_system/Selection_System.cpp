/*************************************************************************
    > File Name: Selection_System.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月26日 星期三 13时19分10秒
    > Functional： Selection examination system interface
 ************************************************************************/
#include "Selection_System.h"

int Selection_System::index=0;
Selection_System::Selection_System(QWidget *parent) : QWidget(parent)
{
    //设置窗口大小不变
    Desktop=new QDesktopWidget();
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setFixedSize(Desktop->width(),Desktop->height());
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    Choice_Score=0;
    SetBackGround();
    GridLayout=new QGridLayout();
    RadioButton=new GroupRadioButton[15];
    Exit_Button=new MyButton("保存并退出",this);
    Next_Button=new MyButton("下一题",this);
    Last_Button=new MyButton("上一题",this);
    Page=new MyLabel[15];
    Prompt=new MyLabel("红色代表未做，浅蓝色代表已做！");
    Subject=new MyTextBrowser[15];
    Selection_System_Layout();
    connect(Next_Button, SIGNAL(clicked(bool)), this, SLOT(Next_Click()));
    connect(Last_Button, SIGNAL(clicked(bool)), this, SLOT(Last_Click()));
}

Selection_System::~Selection_System()
{
    delete[] Page;
    Page=nullptr;
    delete Prompt;
    Prompt=nullptr;
    delete[] Subject;
    Subject=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Next_Button;
    Next_Button=nullptr;
    delete Last_Button;
    Last_Button=nullptr;
    delete[] RadioButton;
    RadioButton=nullptr;
    delete Login_BackGround;
    Login_BackGround=nullptr;
    delete Desktop;
}

int Selection_System::GetChoice_Score()
{
    Questions* IfChoiceAnswer;
    for(int i=0;i<15;i++)
    {
        QString ChoiceAnswer=RadioButton[i].Choice_Options();
        IfChoiceAnswer=GetChoice(i);
        if(ChoiceAnswer==IfChoiceAnswer->ChoiceAnswer)
           Choice_Score+=1;
    }
    return Choice_Score;
}

void Selection_System::SetBackGround()
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

void Selection_System::Selection_System_Layout()
{
    File_Function *file=new File_Function();
    QString Address=":/Questions/Choice";
    file->Bin_Read_Choice(Address,Choice);
    Questions* temp;
    for(int i=0;i<15;i++)
    {
        temp= GetChoice(i);
        QString id=QString::number(i+1,10);
        Subject[i].setText(id+"、"+temp->Subject);
        Subject[i].setParent(this);
        Subject[i].setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;color:white");
        Subject[i].setMaximumSize(Desktop->width(),100);
        if(i!=0)
        {
            GridLayout->addWidget(&Subject[i],4,0,1,17);
            GridLayout->addWidget(RadioButton[i].GroupBoxChoice,5,0,0,17);
        }
        Subject[i].hide();
        RadioButton[i].RadioGroupBoxChoice(this,temp);
    }
    GridLayout->addWidget(&Subject[0],0,0,1,22);
    GridLayout->addWidget(RadioButton[0].GroupBoxChoice,1,0,1,22);
    Subject[0].show();
    RadioButton[0].ShowBox();
    GridLayout->setRowStretch(2,1);
    GridLayout->setRowStretch(6,1);
    GridLayout->setColumnStretch(19,1);
    GridLayout->addWidget(Last_Button,7,20,1,2);
    GridLayout->addWidget(Next_Button,8,20,1,2);
    GridLayout->addWidget(Exit_Button,9,20,1,2);
    GridLayout->setRowStretch(10,1);
    GridLayout->setColumnStretch(19,1);
    for(int i=0;i<15;i++)
    {
        QString id=QString::number(i+1,10);
        Page[i].setParent(this);
        Page[i].SetMyFont(12);
        Page[i].SetBackGroundRed();
        Page[i].setText(id);
        Page[i].setAlignment(Qt::AlignCenter);
        GridLayout->addWidget(&Page[i],11,i+2);
    }
    Prompt->Fillet_Style();
    GridLayout->addWidget(Prompt,12,2,1,15);
    GridLayout->setColumnStretch(19,1);
    this->setLayout(GridLayout);

}

Questions* Selection_System::GetChoice(int Getid)
{
    for(int i=0;i<Choice.size();i++)
        if(Getid==Choice[i].ID)
            return &Choice[i];
}

void Selection_System::Next_Click()
{
    QString Answer=RadioButton[index].Choice_Options();
     if(Answer=="A"||Answer=="B"||Answer=="C")
           Page[index].SetBackGroundWathet();
    if(14==index) return;
    GridLayout->setRowStretch(3,1);
    GridLayout->addWidget(&Subject[index],4,0,1,17);
    GridLayout->addWidget(RadioButton[index].GroupBoxChoice,5,0,1,17);
    Subject[index].setVisible(false);
    RadioButton[index].HideBox();
    index++;
    Subject[index].setVisible(true);
    RadioButton[index].ShowBox();
    GridLayout->addWidget(&Subject[index],0,0,1,22);
    GridLayout->addWidget(RadioButton[index].GroupBoxChoice,1,0,1,22);
    GridLayout->setRowStretch(2,1);
}

void Selection_System::Last_Click()
{
    QString Answer=RadioButton[index].Choice_Options();
     if(Answer=="A"||Answer=="B"||Answer=="C")
           Page[index].SetBackGroundWathet();
    if(0==index) return;
    GridLayout->setRowStretch(3,1);
    GridLayout->addWidget(&Subject[index],4,0,1,17);
    GridLayout->addWidget(RadioButton[index].GroupBoxChoice,5,0,1,17);
    Subject[index].setVisible(false);
    RadioButton[index].HideBox();
    index--;
    Subject[index].setVisible(true);
    RadioButton[index].ShowBox();
    GridLayout->addWidget(&Subject[index],0,0,1,22);
    GridLayout->addWidget(RadioButton[index].GroupBoxChoice,1,0,1,22);
    GridLayout->setRowStretch(2,1);
}
