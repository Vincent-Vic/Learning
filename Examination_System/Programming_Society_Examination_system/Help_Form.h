/*************************************************************************
    > File Name: Help_Form.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年08月13日 星期日 13时18分16秒
    > Functional： Software information
 ************************************************************************/

#ifndef HELP_FORM_H
#define HELP_FORM_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QBitmap>
#include <QPixmap>
#include <QMouseEvent>
#include <QRect>
#include <QMessageBox>
#include "../Library/MyPicTure.h"
#include "../Library/BackGround.h"
#include "../Library/MyLabel.h"
#include "../Library/MyButton.h"

class Help_Form : public QWidget
{
    Q_OBJECT
public:
    explicit Help_Form(QWidget *parent = nullptr);
    ~Help_Form();
private:
    void NewHelpForm();
    MyPicTure* Picture_Logo;
    MyPicTure* Picture_QR_Code;
    MyPicTure* Picture_QR_offical;
    BackGround* Help_BackGround;
    MyLabel* Information;
    MyLabel* Website;
    MyButton* OK;
protected:
    void  mouseMoveEvent(QMouseEvent *event);
    void  mousePressEvent(QMouseEvent *event);
    void  mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint mouseMovePos;
signals:

public slots:
};

#endif // HELP_FORM_H
