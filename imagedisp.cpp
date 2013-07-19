#include "imagedisp.h"
#include <QLayout>
#include <QPixmap>
#include <QMargins>
#include <QFileDialog>
#include <QSizePolicy>
#include <QMessageBox>
#include <QScreen>

ImageDisp::ImageDisp(const QString& fileName, QWidget *parent) :QWidget(parent)
{  
    createLayout(fileName);
    setAttribute(Qt::WA_DeleteOnClose);
}

void ImageDisp::createLayout(const QString& fileName){
    srcImgDispArea = new QLabel;
    srcImgDispArea->setScaledContents(false);   // label will not scall the image size to fill the avaliable space
    curImgDispArea = new QLabel;
    curImgDispArea->setScaledContents(false);   // label will not scall the image size to fill the avaliable space
    srcImgDispArea->setAlignment(Qt::AlignCenter);
    srcImgDispArea->setText("Show the picture you want to handle here");
    curImgDispArea->setAlignment(Qt::AlignCenter);
    curImgDispArea->setText("Show the current result of your picture here");

    if(fileName != 0){
        srcImg = new QImage(fileName);
        curImg = new QImage(fileName);
        srcImgDispArea->setPixmap(QPixmap::fromImage(*srcImg));
        curImgDispArea->setPixmap(QPixmap::fromImage(*curImg));
     }


    srcLabel = new QLabel(tr("&Source Image"));
    curLabel = new QLabel(tr("&Current Modified Image"));
    srcImgDispAreaScroll = new QScrollArea;
    srcImgDispAreaScroll->setWidgetResizable(true);   // scoll area will auto resize the widget in order to avoid scoll bars where they can be avoided
    srcImgDispAreaScroll->viewport()->setBackgroundRole(QPalette::Light);
    srcImgDispAreaScroll->viewport()->setAutoFillBackground(true);
    srcImgDispAreaScroll->setAlignment(Qt::AlignCenter);
    srcImgDispAreaScroll->setWidget(srcImgDispArea);
    srcLabel->setBuddy(srcImgDispAreaScroll);
    curImgDispAreaScroll = new QScrollArea;
    curImgDispAreaScroll->setWidgetResizable(true);   // scoll area will auto resize the widget in order to avoid scoll bars where they can be avoided
    curImgDispAreaScroll->viewport()->setBackgroundRole(QPalette::Light);
    curImgDispAreaScroll->viewport()->setAutoFillBackground(true);
    curImgDispAreaScroll->setAlignment(Qt::AlignCenter);
    curImgDispAreaScroll->setWidget(curImgDispArea);
    curLabel->setBuddy(curImgDispAreaScroll);

    imgLayout = new QVBoxLayout;
    imgLayout->addWidget(srcLabel);
    imgLayout->addWidget(srcImgDispAreaScroll);
    imgLayout->addWidget(curLabel);
    imgLayout->addWidget(curImgDispAreaScroll);
    leftLayout = new QHBoxLayout;
    leftLayout->addLayout(imgLayout);
    leftLayout->addStretch();

    setLayout(leftLayout);
}
