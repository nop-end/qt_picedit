#include "picEdit.h"

#include <QPainter>
#include <QPixmap>
#include <QSizePolicy>
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
PicEdit::PicEdit(const QString& fileName, QWidget *parent) :QWidget(parent)
{
    // indicates that the widget contents are north-west aligned and static.
    // on resize, such a widget will receive paint events only for parts of
    // itself that are newly visible.
    setAttribute(Qt::WA_StaticContents);

    // initial color and zoom factor
    curColor = Qt::black;
    curZoom = 4;

    // blank fill or image fill
    if(fileName != 0){
        srcImg = new QImage(fileName);
    }else{
        srcImg = new QImage(40,30,QImage::Format_ARGB32);
        srcImg->fill(qRgba(0,0,0,0));
    }
    curImg = new QImage(*srcImg);


    // file name
    curFile = new QString;
    fulCurFile = new QString;

    // set title and icon
    settitle(fileName);

    // once close, delete all heap memory
    setAttribute(Qt::WA_DeleteOnClose);
}

// returns the zoomed size
QSize PicEdit::sizeHint() const{
    QSize size = curZoom * curImg->size();
    return size;
}

// set new color
void PicEdit::setPenColor(const QColor& newColor){
    curColor = newColor;
}

// set new image to display on the choosen(active) widget
void PicEdit::setCurImgFile(const QImage& newImg){
    if(newImg != *curImg){
        // if curImg has already been newed, delete it  first
        if(!curImg->isNull()){
            delete curImg;
        }
        *curImg = newImg.convertToFormat(QImage::Format_ARGB32);

        // new draw to this window by using newImage to replace curImage
        update();
        // new self-adapt to arrange the layout with new size and position
        updateGeometry();
    }
}

// set new zoom factor
void PicEdit::setZoomFactor(int newZoom){
    // avoid "0" in the divider
    if(newZoom < 1)
        newZoom = 1;
    if(newZoom != curZoom){
        curZoom = newZoom;
        update();
        updateGeometry();
    }
}


// set the mutil doc title
void PicEdit::settitle(const QString &fileName){
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
bool PicEdit::save(){
    if(isUntitled){
        return saveAs();
    }else{
        // so that the file will be saved in the first-saved place since full file path is applied
        return saveFile(*fulCurFile);
    }
}

// save file as
bool PicEdit::saveAs(){
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

bool PicEdit::okToClose(){
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

/*--------------------------------------- protected events -----------------------------------------*/
// reload the paintevent function to draw zoomed images on the hint area
void PicEdit::paintEvent(QPaintEvent *event){
    // temp a painter
    QPainter painter(this);
    for(int i = 0; i < curImg->width(); i++){
        for(int j = 0; j < curImg->height(); j++){
            // one rect represents one zoomed pixel
            QRect rect = pixRect(i,j);
            // QRegion is the best tool for minimizing the amount of screen area to be updated by a repaint
            // "event-> region" returns the region to be repaint, intersected returns the intersected
            // region of this region and rect
            if( !event->region().intersected(rect).isEmpty()){
                // get current pixel color
                QColor color = QColor::fromRgba(curImg->pixel(i,j));
                // not full opaque then fill white background first
                if(color.alpha() < 255){
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}

// set points color by click the mouse left or right button
void PicEdit::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        setImgPix(event->pos(), true);
    }else if(event->button() == Qt::RightButton){
        setImgPix(event->pos(), false);
    }
}

// set points color of dragging image points by mouse move
void PicEdit::mouseMoveEvent(QMouseEvent *event){
    // "&" is used to verify the release of corresponding button
    if(event->buttons() & Qt::LeftButton){
        setImgPix(event->pos(), true);
    }else if(event->buttons() & Qt::RightButton){
        setImgPix(event->pos(), false);
    }
}

void PicEdit::closeEvent(QCloseEvent *event){
    if(okToClose()){
        event->accept();
    }else{
        event->ignore();
    }
}


/*--------------------------------------- private functions -----------------------------------------*/
// set color of every pix of the real image not the zoomed area
void PicEdit::setImgPix(const QPoint &pos, bool opaque){
    QImage* preImg = new QImage(*curImg);

    int i = pos.x() / curZoom;
    int j = pos.y() / curZoom;
    // contains(i,j) : verify the existance of pix(i,j) within the image
    if(curImg->rect().contains(i,j)){
        if(opaque){
            curImg->setPixel(i, j, penColor().rgba());
        }else{
            curImg->setPixel(i, j, qRgba(0,0,0,0));
        }
        // this will lead a paintEvent
        update(pixRect(i, j));

        // indicate that the image was modified
        if(*curImg != *preImg){
            setWindowModified(true);
        }
    }
}

// returns the zoomed rect of one pixel
QRect PicEdit::pixRect(int i, int j) const{
    return QRect(curZoom * i, curZoom * j , curZoom, curZoom);
}

bool PicEdit::saveFile(const QString &fileName){
    // !!! if here the cursor state change hasn't been used, the program will announce abnormal ending
    // once close the program ??? why
    // set cursor as wait state
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // method 1: save file directly
    curImg->save(fileName,"png",100);
    settitle(fileName);

    // method 2: write into byte array, not fully realized yet -- filename
    /*QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    curImgDisp->curImgFile()->save(&buffer,"PNG",100);*/

    // restore cursor state
    QApplication::restoreOverrideCursor();

    // restore window modify state
    setWindowModified(false);

    return true;
}


