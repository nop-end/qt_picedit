#ifndef PICEDITWINDOW_H
#define PICEDITWINDOW_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QCloseEvent>
#include <QSize>

class PicEditWindow : public QScrollArea
{
    Q_OBJECT

signals:
    void saveImgFile(const QString& fileName);
    void reSizePicEdit(const QSize& size);
    void reZoomPicEdit(int newZoom);

public:
    explicit PicEditWindow(const QString& fileName = 0, QScrollArea* parent = 0);

    void settitle(const QString& fileName = 0);
    bool save();
    bool saveAs();

    bool okToClose();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);


private slots:
    void setPicEditModified();


private:
    bool saveFile(const QString& fileName);

    QString* curFile;
    QString* fulCurFile;
    bool isUntitled;

};

#endif // PICEDITWINDOW_H
