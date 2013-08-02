#ifndef PICEDITWINDOW_H
#define PICEDITWINDOW_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QCloseEvent>

class PicEditWindow : public QScrollArea
{
    Q_OBJECT

signals:
    void saveImgFile(const QString& fileName);

public:
    explicit PicEditWindow(const QString& fileName = 0, QScrollArea* parent = 0);

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

    QScrollArea* curImgFrame;
    QString* curFile;
    QString* fulCurFile;
    bool isUntitled;

};

#endif // PICEDITWINDOW_H
