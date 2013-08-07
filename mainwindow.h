#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QString>
#include <QStringList>
#include <QMdiArea>
#include <QLabel>
#include <QCloseEvent>
#include "piceditwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

    /*--------------- Private SLOTS ---------------*/
private slots:
    void updateActions();
    void newEdit();
    void openPic();
    void openVideo();
    bool save();
    bool saveAs();
    void preStep();
    void nextStep();
    void openRecentFile();
    void updateStatusBar();
    void about();

    /*--------------- Private Functions ---------------*/
private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createSubWindowLayOut();
    void createDockWindowLayOut();
    void createStatusBar();
    void updateRecentFileActions();
    PicEditWindow* activePicEdit();
    bool nonSavedSubwindowExisit();
    bool okToClose();
    void addNewPicEdit(const QString& fileName = 0);
    void readSettings();
    void writeSettings();


    /*--------------- Private Members ---------------*/
private:
    // widgets
    QMdiArea* mdiArea;
    QDockWidget* handleDockWidget;

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
    QMenu* viewMenu;
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
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* aboutAction;
    QAction* aboutQtAction;

};

#endif // MAINWINDOW_H
