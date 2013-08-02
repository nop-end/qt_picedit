#ifndef IMGDISP_H
#define IMGDISP_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLabel>


class ImgDisp : public QWidget
{
    Q_OBJECT
    // declare three attributes of picDisp widget and the corresponding read & write functions
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage curImgFile READ curImgFile WRITE setCurImgFile)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

signals:
    void curImgWasModified();

public:
    explicit ImgDisp(const QString& fileName = 0, QWidget *parent = 0);

    // ImgDisp attributes operation functions
    QColor penColor() const {return curColor;}
    void setPenColor(const QColor& newColor);
    QImage* curImgFile() const {return curImg;}
    void setCurImgFile(const QImage& newImg);
    int zoomFactor() const {return curZoom;}
    void setZoomFactor(const int newZoom);

    // redef of event functions
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    //void resizeEvent(QResizeEvent *event);
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
