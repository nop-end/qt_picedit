#include "piceditwindow.h"
#include <QPalette>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QBuffer>
#include <QApplication>

/*--------------------------------------- public funtions -----------------------------------------*/
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

    // signals and slots
    connect(curImgDisp,SIGNAL(curImgWasModified()),this,SLOT(setPicEditModified()));

    // set title and icon
    settitle(fileName);

    // once close, delete all heap memory
    setAttribute(Qt::WA_DeleteOnClose);
}

// set the mutil doc title
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
    setWindowTitle(*curFile + "[*]");
}

// save file
bool PicEditWindow::save(){
    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(*curFile);
    }
}

// save file as
bool PicEditWindow::saveAs(){
    QString* selectedFilter = new QString("*.jpg");
    // set c:/ as the default file save path
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),"C:/",
                                                    tr("(*.png) ;;(*.bmp);; (*.jpg);;(*.*)"),
                                                    selectedFilter);
    delete selectedFilter;
    if(fileName.isEmpty()){
        return false;
    }else{
        return saveFile(fileName);
    }
}

bool PicEditWindow::okToClose(){
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("PicEdit"),
                                     tr("The images has been modified.\n Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

/*--------------------------------------- Protect events -----------------------------------------*/
void PicEditWindow::closeEvent(QCloseEvent *event){
    if(okToClose()){
        event->accept();
    }else{
        event->ignore();
    }
}


/*--------------------------------------- Private functions -----------------------------------------*/
bool PicEditWindow::saveFile(const QString &fileName){
    // !!! if here the cursor state change hasn't been used, the program will announce abnormal ending
    // once close the program ??? why
    // set cursor as wait state
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // method 1: save file directly
    curImgDisp->curImgFile()->save(fileName,"png",100);
    settitle(fileName);

    // method 2: write into byte array, not fully realized yet -- filename
    /*QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    curImgDisp->curImgFile()->save(&buffer,"PNG",100);*/

    // restore cursor state
    QApplication::restoreOverrideCursor();

    return true;
}

void PicEditWindow::setPicEditModified(){
    setWindowModified(true);
}








