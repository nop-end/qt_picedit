#ifndef PICEDIT_H
#define PICEDIT_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


class PicEdit : public QWidget
{
    Q_OBJECT
    // declare three attributes of picDisp widget and the corresponding read & write functions
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage curImgFile READ curImgFile WRITE setCurImgFile)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit PicEdit(const QString& fileName = 0, QWidget *parent = 0);

    // ImgDisp attributes operation functions
    QColor penColor() const {return curColor;}
    void setPenColor(const QColor& newColor);
    QImage* curImgFile() const {return curImg;}
    void setCurImgFile(const QImage& newImg);
    int zoomFactor() const {return curZoom;}
    void setZoomFactor(const int newZoom);

    void settitle(const QString& fileName = 0);
    bool save();
    bool saveAs();
    bool okToClose();

    // redef of event functions
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    QSize sizeHint() const;

private:
    // private functions
    void setImgPix(const QPoint& point, bool opaque);
    QRect pixRect(int x, int y) const;


    bool saveFile(const QString& fileName);

    // private attributes
    QColor curColor;
    QImage* srcImg;
    QImage* curImg;
    int curZoom;

    QLabel* curImgDisp;
    QString* curFile;
    QString* fulCurFile;
    bool isUntitled;
    
};

#endif // PICDISP_H
