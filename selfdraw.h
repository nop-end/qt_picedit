#ifndef SELFDRAW_H
#define SELFDRAW_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QRect>
#include <QSize>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

class SelfDraw : public QWidget
{
    Q_OBJECT

    // declare three properties of selfdraw and the corresponding read & write functions
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage selfDrawImage READ selfDrawImage WRITE setSelfDrawImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit SelfDraw(QWidget *parent = 0);

    // property related functions
    void setPenColor(const QColor &newColor);
    QColor penColor() const { return curColor; }
    void setSelfDrawImage(const QImage &newImage);
    QImage selfDrawImage() const { return curImage; }
    void setZoomFactor(int newZoom);
    int zoomFactor() const { return curZoom; }

    QSize sizeHint() const;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage curImage;
    int curZoom;
};

#endif // SELFDRAW_H
