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

    void settitle(const QString& fileName = 0);

protected:
//    void closeEvent(QCloseEvent *event);

private:
    ImgDisp* curImgDisp;
    QString* curFile;
    bool isUntitled;

};

#endif // PICEDITWINDOW_H
