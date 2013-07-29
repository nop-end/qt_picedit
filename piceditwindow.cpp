#include "piceditwindow.h"
#include <QPalette>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFile>
#include <QFileInfo>

/*--------------------------------------- construct -----------------------------------------*/
PicEditWindow::PicEditWindow(const QString& fileName, QWidget *parent) :QWidget(parent){
    // new a ImgDisp -- blank or fill with image
    curImgDisp = new ImgDisp(fileName);

    // new a scrollArea as the image frame
    QScrollArea* curImgFrame = new QScrollArea;
    curImgFrame->setAlignment(Qt::AlignCenter);
    curImgFrame->setWidgetResizable(false);
    curImgFrame->viewport()->setAutoFillBackground(true);
    curImgFrame->viewport()->setBackgroundRole(QPalette::Dark);
    curImgFrame->setWidget(curImgDisp);

    // set the layout
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(curImgFrame);
    setLayout(hLayout);

    // set title and icon
    settitle(fileName);

    // once close, delete all heap memory
    setAttribute(Qt::WA_DeleteOnClose);
}


void PicEditWindow::settitle(const QString &fileName){
    static int documentNumber = 1;
    if(fileName != 0){
        curFile = new QString(QFileInfo(fileName).fileName());
        isUntitled = false;
    }else{
        curFile = new QString(tr("Untitled%1.png").arg(documentNumber));
        isUntitled = true;
        ++documentNumber;
    }
    setWindowTitle(*curFile);
}

/*--------------------------------------- Protect events -----------------------------------------*/
//void PicEditWindow::closeEvent(QCloseEvent *event){

//}
