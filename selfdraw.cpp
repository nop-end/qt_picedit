#include "selfdraw.h"

#include <QPainter>

SelfDraw::SelfDraw(QWidget *parent) :QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);    // Indicates that the widget contents are north-west aligned and static.
                                            // On resize, such a widget will receive paint events only for parts of
                                            // itself that are newly visible.
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);   // Indicates that no more smaller size is acceptable

    curColor = Qt::black;
    curZoom = 8;
    curImage = QImage(16, 16, QImage::Format_ARGB32);
    curImage.fill(qRgba(0,0,0,0));
}

QSize SelfDraw::sizeHint() const{
    QSize size = curZoom * curImage.size();
    if(curZoom > 3){
        size += QSize(1,1);
    }
    return size;
}

void SelfDraw::setPenColor(const QColor &newColor){
    curColor = newColor;
}

void SelfDraw::setSelfDrawImage(const QImage &newImage){
    if(newImage != curImage){
        curImage = newImage.convertToFormat(QImage::Format_ARGB32);
        update();   // new draw to this window by using newImage to replace curImage
        updateGeometry();   // new self-adapt to arrange the layout with new size and position
    }
}

void SelfDraw::setZoomFactor(int newZoom){
    if(newZoom < 1)     // avoid "0" in the divider
        newZoom = 1;
    if(newZoom != curZoom){
        curZoom = newZoom;
        update();
        updateGeometry();
    }
}

void SelfDraw::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    if(curZoom >= 3){
        painter.setPen(palette().foreground().color());   // every widget is occupied with a palette that divided into 3 groups: Active/Inactive/Disable
        for(int i = 0; i <= curImage.width(); ++i){
            painter.drawLine(curZoom * i, 0, curZoom * i, curZoom * curImage.height());    // draw grid
        }
        for(int j = 0; j <= curImage.height(); ++j){
            painter.drawLine(0, curZoom * j, curZoom * curImage.width(), curZoom * j);
        }
    }

    for(int i = 0; i < curImage.width(); ++i){
        for(int j = 0; j < curImage.height(); ++j){
            QRect rect = pixelRect(i,j);    // one rect represents one zoomed pixel
            // QRegion is the best tool for minimizing the amount of screen area to be updated by a repaint
            if( !event->region().intersected(rect).isEmpty()){   // "event-> region" returns the region to be repaint, intersected returns the intersected
                                                                 // region of this region and rect
                QColor color = QColor::fromRgba(curImage.pixel(i,j));   // get current pixel color
                if(color.alpha() < 255){    // not full opaque then fill white background first
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}

// returns the zoomed rect of one pixel
QRect SelfDraw::pixelRect(int i, int j) const{
    if(curZoom >= 3){
        return QRect(curZoom * i + 1, curZoom * j + 1, curZoom - 1, curZoom - 1);
    }else{
        return QRect(curZoom * i, curZoom * j , curZoom, curZoom);
    }
}

void SelfDraw::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        setImagePixel(event->pos(), true);
    }else if(event->button() == Qt::RightButton){
        setImagePixel(event->pos(), false);
    }
}

void SelfDraw::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){      // "&" is used to verify the release of corresponding button
        setImagePixel(event->pos(), true);
    }else if(event->buttons() & Qt::RightButton){
        setImagePixel(event->pos(), false);
    }
}

void SelfDraw::setImagePixel(const QPoint &pos, bool opaque){
    int i = pos.x() / curZoom;
    int j = pos.y() / curZoom;

    if(curImage.rect().contains(i,j)){  // contains(i,j) : verify the existance of pix(i,j) within the image
        if(opaque){
            curImage.setPixel(i, j, penColor().rgba());
        }else{
            curImage.setPixel(i, j, qRgba(0,0,0,0));
        }

        update(pixelRect(i, j));
    }
}




