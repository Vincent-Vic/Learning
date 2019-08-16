/*************************************************************************
    > File Name: MyPicTure.cpp
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created Time: 2017年07月21日 星期五 16时45分40秒
    > Functional： My PicTure package
 ************************************************************************/
#include "MyPicTure.h"

MyPicTure::MyPicTure(QString PictureFile, QWidget *f,QString error)
{
    this->setScaledContents(true);
    QImage* img=new QImage();
    if(! ( img->load(PictureFile) ) ) //加载图像
    {
            QMessageBox::information(NULL, "提示", "图片加载失败，错误代码："+error, QMessageBox::Yes , QMessageBox::Yes);
                delete img;
                img=nullptr;

    }
    this->setPixmap(QPixmap::fromImage(*img));
    this->setParent(f);
}
