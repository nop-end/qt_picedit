#ifndef IMAGEDISP_H
#define IMAGEDISP_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ImageDisp : public QWidget
{
    Q_OBJECT
public:
    explicit ImageDisp(const QString& fileName = 0, QWidget *parent = 0);


private:
    QImage* srcImg;
    QImage* curImg;
    QLabel* srcLabel;
    QLabel* srcImgDispArea;
    QLabel* curLabel;
    QLabel* curImgDispArea;
    QScrollArea* srcImgDispAreaScroll;
    QScrollArea* curImgDispAreaScroll;
    QVBoxLayout* imgLayout;
    QHBoxLayout* leftLayout;

    void createLayout(const QString& fileName);
};

#endif // IMAGEDISP_H
