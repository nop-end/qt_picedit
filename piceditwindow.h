#ifndef PICEDITWINDOW_H
#define PICEDITWINDOW_H

#include "imgDisp.h"
#include <QWidget>
#include <QString>

class PicEditWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PicEditWindow(const QString& fileName = 0, QWidget* parent = 0);

private:
    ImgDisp* curImgDisp;

};

#endif // PICEDITWINDOW_H
