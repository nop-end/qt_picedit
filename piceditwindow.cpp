#include "piceditwindow.h"
#include <QPalette>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QBuffer>
#include <QApplication>


/*--------------------------------------- public funtions -----------------------------------------*/
// constructor
PicEditWindow::PicEditWindow(const QString& fileName, QScrollArea *parent) :QScrollArea(parent){
    // file name
    curFile = new QString;
    fulCurFile = new QString;

    // set title and icon
    settitle(fileName);
    setBackgroundRole(QPalette::Dark);

    // once close, delete all heap memory
    setAttribute(Qt::WA_DeleteOnClose);
}

// set the mutil doc title
void PicEditWindow::settitle(const QString &fileName){
    static int documentNumber = 1;
    if(fileName != 0){
        *curFile = QFileInfo(fileName).fileName();
        *fulCurFile = fileName;
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
        // so that the file will be saved in the first-saved place since full file path is applied
        return saveFile(*fulCurFile);
    }
}

// save file as
bool PicEditWindow::saveAs(){
    QString* selectedFilter = new QString("*.jpg");
    // set c:/ as the default file save path
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),
                                                    "C:/" + QFileInfo(*curFile).fileName(),
                                                    tr("(*.png) ;;(*.bmp);; (*.jpg);;(*.*)"),
                                                    selectedFilter);
    delete selectedFilter;
    if(fileName.isEmpty()){
        return false;
    }else{
        return saveFile(fileName);
    }
}

// check if the current single document is saved that ok to close
bool PicEditWindow::okToClose(){
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("PicEdit"),
                                     QFileInfo(*curFile).fileName() + tr("has been modified.\n Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        }else if (r == QMessageBox::No){
            return true;
        }else if (r == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

/*--------------------------------------- Protect events -----------------------------------------*/
// indicate to save the unsaved and untitiled
void PicEditWindow::closeEvent(QCloseEvent *event){
    if(okToClose()){
        event->accept();
    }else{
        event->ignore();
    }
}

// indicate to resize the picEdit area
void PicEditWindow::resizeEvent(QResizeEvent *event){
    const QSize size = event->size();
    emit reSizePicEdit(size);
}

// set the zoomIn and zoomOut
void PicEditWindow::wheelEvent(QWheelEvent *event){
    int wheelStep = event->delta() / 120;
    emit reZoomPicEdit(wheelStep);
}


/*--------------------------------------- Private functions -----------------------------------------*/
bool PicEditWindow::saveFile(const QString &fileName){
    // !!! if here the cursor state change hasn't been used, the program will announce abnormal ending
    // once close the program ??? why
    // set cursor as wait state
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // emit save file signal
    emit saveImgFile(fileName);
    settitle(fileName);

    // restore cursor state
    QApplication::restoreOverrideCursor();

    // restore window modify state
    setWindowModified(false);

    return true;
}

// set that the current active picEdit subwindow has been modified
void PicEditWindow::setPicEditModified(){
    setWindowModified(true);
}
