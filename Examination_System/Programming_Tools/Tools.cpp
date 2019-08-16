/*************************************************************************
    > File Name: Tools.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月15日 星期二 14时00分14秒
    > Functional： Tools
 ************************************************************************/
#include "Tools.h"

Tools::Tools(QWidget *parent) :  QWidget(parent)
{
    Qt::WindowFlags flags = 0;
        flags |= Qt::WindowMinimizeButtonHint;
        flags |=Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
        setFixedSize(700,700);
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    Tools_Setbackground();
    Tools_Title=new MyLabel("编程社纳新离线成绩翻译器\n",this);
    Tools_Address_Prompt=new MyLabel("文件名：",this);
    Tools_Text=new MyTextBrowser("",this);
    Tools_Address=new MyLineEdit(this);
    GridLayout=new QGridLayout();
    Exit_Button=new MyButton("读取",this);
    Folder=new MyButton("创建文件夹",this);
    Cancel=new MyButton("取消",this);
    Tools_Layout();
    connect(Exit_Button,SIGNAL(clicked(bool)),this,SLOT(Exit_Click()));
    connect(Folder,SIGNAL(clicked(bool)),this,SLOT(Folder_Click()));
    connect(Cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

Tools::~Tools()
{
    delete Tools_Title;
    Tools_Title=nullptr;
    delete Tools_Address_Prompt;
    Tools_Address_Prompt=nullptr;
    delete Tools_Text;
    Tools_Text=nullptr;
    delete Tools_Address;
    Tools_Address=nullptr;
    delete GridLayout;
    GridLayout=nullptr;
    delete Exit_Button;
    Exit_Button=nullptr;
    delete Folder;
    Folder=nullptr;
    delete Cancel;
    Cancel=nullptr;
}

void Tools::Tools_Setbackground()
{
    resize(700,700);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap mask(":/BackGround/Small");//加载掩码图像
    setMask(QBitmap(mask.mask())); //设置窗体的掩码图像,抠除图像的白色区域实现不规则窗体
    QPalette p;//设置调色板
    p.setBrush(QPalette::Window, QBrush(mask));//将调色板的画刷设置为掩码位图,在不规则窗体上显示出掩码位图
    setPalette(p);
    mouseMovePos = QPoint(0, 0);
}

void  Tools::mouseMoveEvent(QMouseEvent *event)//鼠标按下并移动则移动不规则窗体
{
if(mouseMovePos != QPoint(0, 0))
{
    move(geometry().x() + event->globalPos().x() - mouseMovePos.x(), geometry().y() + event->globalPos().y() - mouseMovePos.y());
    mouseMovePos = event->globalPos();
}
}

void  Tools::mousePressEvent(QMouseEvent *event)
{
    mouseMovePos = event->globalPos();
}

void  Tools::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMovePos = QPoint(0, 0);
}

void Tools::Exit_Click()
{
    /*
     * 检查文件是否存在
     * */
    QDir *temp = new QDir;
    QString FileAddress=QCoreApplication::applicationDirPath();
    bool exist = temp->exists(FileAddress+"//Score");
    if(!exist)
    {
        QMessageBox::information(NULL, "提示", "没有文件夹，已自动创建文件夹\n请把dll文件放在Score中，翻译文件也在Score中", QMessageBox::Yes , QMessageBox::Yes);
        temp->mkdir(FileAddress+"//Score");
        return;
    }
    QString Address=Tools_Address->text();
    if(""==Address)
    {
        QMessageBox::information(NULL, "提示", "亲填写文件名称\n请把dll文件放在Score中，翻译文件也在Score中", QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    /*
     *  文件读入到只读显示框，写入文件
     * */
    QFile file("Score\\"+Address+".dll");
    if ( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);
        while ( !in.atEnd() )
        {
            QString Temp;
            in.setVersion(QDataStream::Qt_4_7);
            in >> Temp;
            Tools_Text->append(Temp);

        }
        file.close();
    }
    else
    {
         QMessageBox::information(NULL, "提示", "文件读取失败，或文件不存在\n请把dll文件放在Score中，翻译文件也在Score中", QMessageBox::Yes , QMessageBox::Yes);
         return;
    }
    QString Data=Tools_Text->toPlainText();
    QFile files("Score\\"+Address+".txt");
    if ( files.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
         QTextStream out(&files);
         out << Data ;
         file.close();
    }
    else
    {
         QMessageBox::information(NULL, "提示", "保存出差错", QMessageBox::Yes , QMessageBox::Yes);
    }
}

void Tools::Folder_Click()
{
    /**
     * 创建文件夹
     */
    QDir *temp = new QDir;
    QString FileAddress=QCoreApplication::applicationDirPath();
    bool exist = temp->exists(FileAddress+"//Score");
    if(!exist)
    {
        QMessageBox::information(NULL, "提示", "创建成功！！！\n请把dll文件放在Score中，翻译文件也在Score中", QMessageBox::Yes , QMessageBox::Yes);
        temp->mkdir(FileAddress+"//Score");
        return;
    }
    else
    {
         QMessageBox::information(NULL, "提示", "文件夹已存在\n请把dll文件放在Score中，翻译文件也在Score中", QMessageBox::Yes , QMessageBox::Yes);
    }
}

void Tools::Tools_Layout()
{
    Tools_Title->SetMyFont();
    Tools_Title->setAlignment(Qt::AlignCenter);
    Tools_Address_Prompt->SetMyFont();
    Tools_Address->setPlaceholderText("文件名（不需要后缀）");
    GridLayout->addWidget(Tools_Title,1,1,1,3);
    GridLayout->addWidget(Tools_Text,2,1,1,3);
    GridLayout->addWidget(Tools_Address_Prompt,3,1);
    GridLayout->addWidget(Tools_Address,3,2);
    GridLayout->addWidget(Folder,3,3);
    GridLayout->addWidget(Exit_Button,4,1,1,3);
    GridLayout->addWidget(Cancel,5,1,1,3);
    this->setLayout(GridLayout);
}
