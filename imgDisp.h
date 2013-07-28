#ifndef IMGDISP_H
#define IMGDISP_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>

class ImgDisp : public QWidget
{
    Q_OBJECT
    // declare three attributes of picDisp widget and the corresponding read & write functions
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage curImgDisp READ curImgDisp WRITE setCurImgDisp)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit ImgDisp(const QString& fileName = 0, QWidget *parent = 0);

    // ImgDisp attributes operation functions
    QColor penColor() const {return curColor;}
    void setPenColor(const QColor& newColor);
    QImage* curImgDisp() const {return curImg;}
    void setCurImgDisp(const QImage& newImg);
    int zoomFactor() const {return curZoom;}
    void setZoomFactor(const int newZoom);

    // redef of event functions
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;

private:
    // private functions
    void setImgPix(const QPoint& point, bool opaque);
    QRect pixRect(int x, int y) const;

    // private attributes
    QColor curColor;
    QImage* srcImg;
    QImage* curImg;
    int curZoom;
    
};

#endif // PICDISP_H
