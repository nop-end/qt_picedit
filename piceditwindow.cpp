#include "piceditwindow.h"
#include <QPalette>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

// constructor
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

    // once close, delete all heap memory
    setAttribute(Qt::WA_DeleteOnClose);
}
