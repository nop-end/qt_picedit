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
    bool save();
    bool saveAs();

    bool okToClose();

protected:
    void closeEvent(QCloseEvent *event);


private slots:
    void setPicEditModified();


private:
    bool saveFile(const QString& fileName);


    ImgDisp* curImgDisp;
    QString* curFile;
    QString* fulCurFile;
    bool isUntitled;

};

#endif // PICEDITWINDOW_H
