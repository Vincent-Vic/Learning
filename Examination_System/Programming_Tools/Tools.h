/*************************************************************************
    > File Name: Tools.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月15日 星期二 14时00分14秒
    > Functional： Tools
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
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include <QCoreApplication>
#include <QMessageBox>
#include "../Library/MyLabel.h"
#include "../Library/MyButton.h"
#include "../Library/MyLineEdit.h"
#include "../Library/BackGround.h"
#include "../Library/MyTextBrowser.h"
class Tools : public QWidget
{
    Q_OBJECT
public:
    explicit Tools(QWidget *parent = nullptr);
    ~Tools();
private:

    MyLabel* Tools_Title;
    MyLabel* Tools_Address_Prompt;
    MyTextBrowser* Tools_Text;
    MyLineEdit* Tools_Address;
    QGridLayout *GridLayout;
    MyButton* Exit_Button;
    MyButton* Folder;
    MyButton* Cancel;
    void Tools_Setbackground();
    void Tools_Layout();
protected:
    void  mouseMoveEvent(QMouseEvent *event);
    void  mousePressEvent(QMouseEvent *event);
    void  mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint mouseMovePos;
signals:

public slots:
    void Exit_Click();
    void Folder_Click();
};

#endif // CONFIGURE_SERVER_H
