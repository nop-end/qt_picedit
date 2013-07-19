#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagedisp.h"
#include "selfdraw.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QString>
#include <QMdiArea>
#include <QLabel>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

protected:


    /*--------------- Private SLOTS ---------------*/
private slots:
    void updateActions();
    void newDraw();
    void openPic();
    void openVideo();
    bool save();
    bool saveAs();
    void preStep();
    void nextStep();
    void openRecentFile();
    void updateStatusBar();
    void picModified();
    void about();

    /*--------------- Private Functions ---------------*/
private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createLayOut();
    void createStatusBar();
    void updateRecentFileActions();
    void loadFiles();
    bool okToContinue();
    void addImageDisp(ImageDisp* imgd);
    void addNewDraw(SelfDraw* selfd);

    /*--------------- Private Members ---------------*/
private:
    // widgets
    QMdiArea *mdiArea;

    // recent file
    QString curFile;
    static QStringList recentFiles;
    enum{MaxRecentFiles = 10};
    QAction* recentFileActions[MaxRecentFiles];

    // menu
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolsMenu;
    QMenu* optionsMenu;
    QMenu* helpMenu;

    // toolbar
    QToolBar* fileToolBar;
    QToolBar* editToolBar;

    // statusbar
    QLabel* pixLocation;
    QLabel* pixValue;

    // actions
    QAction* newDrawAction;
    QAction* openPicAction;
    QAction* openVideoAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;
    QAction* exitAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* selectSequareAction;
    QAction* zoomAction;
    QAction* shrinkAction;
    QAction* aboutAction;
    QAction* aboutQtAction;

};

#endif // MAINWINDOW_H