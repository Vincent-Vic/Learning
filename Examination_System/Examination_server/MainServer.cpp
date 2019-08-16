/*************************************************************************
    > File Name: MainServer.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期四 16时01分08秒
    > Functional： Main Server
 ************************************************************************/
#include "MainServer.h"

MainServer::MainServer(QWidget *parent) : QWidget(parent),PortCode(808),Total(0)
{
    Desktop=new QDesktopWidget();
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setFixedSize(Desktop->width(),Desktop->height());
    /**
     * 本地文件的方式配置端口号
     */
    QString code;
    QFile file("Server.txt");
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
         QTextStream in(&file);
         code = in.readLine() ;
         file.close();
         PortCode=code.toInt();
    }
    else
    {
        QMessageBox::information(NULL, "提示", "使用默认端口", QMessageBox::Yes , QMessageBox::Yes);
    }
    //设置图标
    this->setWindowIcon(QIcon(QStringLiteral(":/Logo/V")));
    /**
     * 获取本地IP地址
     */
    QString ipAddr;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if (address.protocol() == QAbstractSocket::IPv4Protocol)
       {
             ipAddr = address.toString();
                 break;
         }
     }
    TAB=new QTableWidget(100,12);
    timer = new QTimer(this);
    Title=new MyLabel("编程社纳新服务端",this);
    information=new MyLabel[12];//姓名   年级     专业     电话      QQ    邮箱 方向 成绩,选择题 判断题 填空题 打码题
    IPAddress=new MyLabel("IP：  "+ipAddr,this);
    Port=new MyLabel("Port："+QString::number(PortCode),this);
    Hour=new MyLabel("--:--:--",this);
    Week=new MyLabel("-----",this);
    Day=new MyLabel("--------",this);
    State=new MyLabel("服务端信息",this);
    Server=new QTcpServer(this);
    clientConnection=new QTcpSocket(this);
    ServerBackGround=new BackGround();
    Eixt=new MyButton("保存并退出",this);
    Monitor=new MyButton("监听",this);
    Message=new MyTextBrowser("",this);
    GridLayout=new QGridLayout(this);
    VBoxLayout=new QVBoxLayout(this);
    /**
     * 绑定消息
     */
    connect(Eixt,SIGNAL(clicked(bool)),this,SLOT(Exit_Click()));
    connect(Monitor,SIGNAL(clicked(bool)),this,SLOT(Listen()));
    connect(Server,&QTcpServer::newConnection,this,&MainServer::Status);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timer_Refresh()));
    timer->start(1);
    Server_Setbackground();
    Server_Table();
    Server_Layout();
}

MainServer::~MainServer()
{
    delete Title;
    delete information;
    delete IPAddress;
    delete Port;
    delete Day;
    delete Hour;
    delete State;
    delete Server;
    delete ServerBackGround;
    delete GridLayout;
    delete Eixt;
    delete Message;
}

void MainServer::Server_Table()
{
    //布局
    QStringList header;
    header<<"姓名"<<"年级"<<"专业"<<"电话"<<"QQ"<<"邮箱"<<"方向"<<"选择题"<<"判断题"<<"填空题"<<"打码题"<<"总成绩";
    TAB->setHorizontalHeaderLabels(header);
    QPalette pll = TAB->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    TAB->setPalette(pll);
    TAB->verticalHeader()->setVisible(false);
    TAB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    TAB->horizontalHeader()->setStretchLastSection(true);
    TAB->setSelectionBehavior(QAbstractItemView::SelectRows);
    TAB->setSelectionMode(QAbstractItemView::SingleSelection);
    TAB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TAB->setShowGrid(false);
    TAB->horizontalHeader()->setFixedHeight(30);  //修改表头合适的高度
    TAB->setColumnWidth(2,120);
    TAB->setColumnWidth(3,130);
    TAB->setColumnWidth(4,130);
    TAB->setColumnWidth(5,130);
    TAB->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:gray;color: white;padding-left: 0px;border: 0px solid #6c6c6c;}");
}

void MainServer::Server_Layout()
{
    Title->setAlignment(Qt::AlignCenter);
    Day->setAlignment(Qt::AlignCenter);
    Week->setAlignment(Qt::AlignCenter);
    Hour->setAlignment(Qt::AlignCenter);
    State->setAlignment(Qt::AlignCenter);
    GridLayout->addWidget(TAB,0,0,10,1);
    GridLayout->addWidget(Title,0,1);
    GridLayout->addWidget(IPAddress,1,1);
    GridLayout->addWidget(Port,2,1);
    GridLayout->addWidget(Monitor,3,1);
    GridLayout->addWidget(Day,4,1);
    GridLayout->addWidget(Week,5,1);
    GridLayout->addWidget(Hour,6,1);
    GridLayout->addWidget(State,7,1);
    GridLayout->addWidget(Message,8,1);
    Message->setMaximumSize(200,600);
    GridLayout->addWidget(Eixt,9,1);
    this->setLayout(GridLayout);
}

void MainServer::Server_Setbackground()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    ServerBackGround->SetBackGround(this,":/Logo/Public");
}

void MainServer::Exit_Click()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出服务端"),
        QString(tr("是否确认无误，退出服务端?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        return;
    }
    else if (button == QMessageBox::Yes)
    {
        Excel(TAB,"编程社纳新机试成绩");
        this->close();
    }
}

void MainServer::Listen()
{
    if(Server->isListening())
    {
          Message->append("已经在监听了！！！");
          return;
    }
    if(Server->listen(QHostAddress::AnyIPv4,PortCode))
    {
          Message->append("监听成功！！！");
    }
    else
    {
          Message->append("监听失败！！！");

    }
}
void MainServer::Status()
{
    Total++;
    QString i=QString::number(Total);
    Message->append("有新连接!当前连接："+i+"个");
    clientConnection = Server->nextPendingConnection();
    connect(clientConnection,&QTcpSocket::disconnected,this,&MainServer::DisplayDisconnect);
    ClientSocket* CS=new ClientSocket(clientConnection,TAB);
    QThread* Thread=new QThread(this);
    connect(clientConnection,SIGNAL(disconnected()),CS,SLOT(deleteLater()));
    connect(clientConnection,SIGNAL(disconnected()),Thread,SLOT(quit()));
    CS->moveToThread(Thread);
    Thread->start();
}

void MainServer::DisplayDisconnect()
{
    Total--;
    if(0==Total)
    {
        Message->append("当前无客户端连接");
    }
    else
    {
        QString i=QString::number(Total);
        Message->append("退出连接!当前连接："+i+"个");
    }

}

void MainServer::Timer_Refresh()
{
    TAB->update();
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString Days = current_date_time.toString("yyyy-MM-dd");
    QString Weeks = current_date_time.toString("ddd");
    QString Hours = current_date_time.toString("hh:mm:ss");
    Day->setText(Days);
    Week->setText(Weeks);
    Hour->setText(Hours);
}

void MainServer::Excel(QTableWidget *table, QString title)
{
    //以Excel的形式保存
    QString fileName = QFileDialog::getSaveFileName(table, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xlsx *.xls)");
           if (fileName!="")
           {
                QAxObject *excel = new QAxObject;
                if (excel->setControl("Excel.Application")) //连接Excel控件
               {
                   excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
                   excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
                   QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
                   workbooks->dynamicCall("Add");//新建一个工作簿
                   QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
                   QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
                   int i,j,colcount=table->columnCount();
                   QAxObject *cell,*col;
                   //标题行
                   cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
                   cell->dynamicCall("SetValue(const QString&)", title);
                   cell->querySubObject("Font")->setProperty("Size", 18);
                   //调整行高
                   worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
                   //合并标题行
                   QString cellTitle;
                   cellTitle.append("A1:");
                   cellTitle.append(QChar(colcount - 1 + 'A'));
                   cellTitle.append(QString::number(1));
                   QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
                   range->setProperty("WrapText", true);
                   range->setProperty("MergeCells", true);
                   range->setProperty("HorizontalAlignment", -4108);//xlCenter
                   range->setProperty("VerticalAlignment", -4108);//xlCenter
                   //列标题
                   for(i=0;i<colcount;i++)
                   {
                       QString columnName;
                       columnName.append(QChar(i  + 'A'));
                       columnName.append(":");
                       columnName.append(QChar(i + 'A'));
                       col = worksheet->querySubObject("Columns(const QString&)", columnName);
                       col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                       cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                       columnName=table->horizontalHeaderItem(i)->text();
                       cell->dynamicCall("SetValue(const QString&)", columnName);
                       cell->querySubObject("Font")->setProperty("Bold", true);
                       cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                       cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                       cell->setProperty("VerticalAlignment", -4108);//xlCenter
                   }
                    //数据区
                   for(i=0;i<table->rowCount();i++){
                       for (j=0;j<colcount;j++)
                       {
                           worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                       }
                   }
                   //画框线
                   QString lrange;
                   lrange.append("A2:");
                   lrange.append(colcount - 1 + 'A');
                   lrange.append(QString::number(table->rowCount() + 2));
                   range = worksheet->querySubObject("Range(const QString&)", lrange);
                   range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
                   range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
                   //调整数据区行高
                   QString rowsName;
                   rowsName.append("2:");
                   rowsName.append(QString::number(table->rowCount() + 2));
                   range = worksheet->querySubObject("Range(const QString&)", rowsName);
                   range->setProperty("RowHeight", 20);
                   workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
                   workbook->dynamicCall("Close()");//关闭工作簿
                   excel->dynamicCall("Quit()");//关闭excel
                   delete excel;
                   excel=NULL;
                   if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                   {
                      QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
                   }
               }
               else
               {
                   QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
               }
        }
}
