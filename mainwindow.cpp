#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QMdiSubWindow>
#include <QScrollArea>

#include "mainwindow.h"
#include "picEdit.h"

/*--------------------------------------- public functions -----------------------------------------*/
// constructor
MainWindow::MainWindow(){
    // set the components and layouts of actions,menus,contextmenus,toolbars and statusbars
    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    createLayOut();

    // remove the "set the initial plain picEdit widget and display on the mdiArea"
    // initial without a new untitled file
    //newEdit();

    // set mainwindow title
    setWindowTitle(QString(tr("%1   copyrights: %2").arg("picEdit").arg("nop-end")));
    setWindowIcon(QIcon(":/icon/mainIcon.png"));

    // wipe out the heap storage on delete of the mainwindow
    setAttribute(Qt::WA_DeleteOnClose);
}


/*--------------------------------------- Protect events -----------------------------------------*/
void MainWindow::closeEvent(QCloseEvent *event){
    // if the whole program is ok to close
    if(okToClose()){
        // close all the subwindow first, and this will encounter the save action of those documents
        mdiArea->closeAllSubWindows();

        // if successfully closed all the subwindow, event will be accept
        if(!mdiArea->subWindowList().isEmpty()){
            event->ignore();
        }else{
            event->accept();
        }
    }
}


/*--------------------------------------- Private SLOTS -----------------------------------------*/
void MainWindow::updateActions(){


}


void MainWindow::newEdit(){
    // new a picEdit widget, which is outlined by a QScrollArea
    PicEdit* newImgEdit = new PicEdit;
    PicEditWindow* newImgContainer = new PicEditWindow;
    newImgContainer->setWidget(newImgEdit);
    newImgContainer->setWidgetResizable(false);

    // signals and slots
    connect(newImgEdit,SIGNAL(curImgWasModified()),newImgContainer,SLOT(setPicEditModified()));
    connect(newImgContainer,SIGNAL(saveImgFile(const QString&)),newImgEdit,SLOT(saveFile(const QString&)));

    // add the new picEdit widget to the mdiArea
    QMdiSubWindow* subWindow = mdiArea->addSubWindow(newImgContainer);
    subWindow->setContentsMargins(0,0,0,0);

    subWindow->show();
}

void MainWindow::openPic(){
    // if the current picEdit widget is saved or not edited, then you can open a pic to display on it
    // if you replace the "/home/hupanhust" with ".", it will guide you to the debug file folder
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"E:/Qtproj/picEdit/image",
                                                    tr("Image Files (*.*)"));

    // if file is existed and valid filename selected
    if(!fileName.isEmpty()){
        // to fill the current selected picEdit widget with selected images, and once select more than
        // one picture(x pictures), then new x-1 picEdit widgets to load the rest and add then all
        PicEdit* newImgEdit = new PicEdit(fileName);
        PicEditWindow* newImgContainer = new PicEditWindow(fileName);
        newImgContainer->setWidget(newImgEdit);
        newImgContainer->setWidgetResizable(false);

        // signals and slots
        connect(newImgEdit,SIGNAL(curImgWasModified()),newImgContainer,SLOT(setPicEditModified()));
        connect(newImgContainer,SIGNAL(saveImgFile(const QString&)),newImgEdit,SLOT(saveFile(const QString&)));

        // add the new picEdit widget to the mdiArea
        QMdiSubWindow* subWindow = mdiArea->addSubWindow(newImgContainer);
        subWindow->setContentsMargins(0,0,0,0);
        subWindow->show();
    }
}

void MainWindow::openVideo(){

}


bool MainWindow::save(){
    if(activePicEdit()){
        return activePicEdit()->save();
    }else{
        return false;
    }
}

bool MainWindow::saveAs(){
    if(activePicEdit()){
        return activePicEdit()->saveAs();
    }else{
        return false;
    }
}

void MainWindow::preStep(){

}

void MainWindow::nextStep(){

}

void MainWindow::openRecentFile(){

}

void MainWindow::updateStatusBar(){

}


void MainWindow::about(){

}


/*--------------------------------------- Private functions -----------------------------------------*/
void MainWindow::createActions(){
    newDrawAction = new QAction(tr("&New"), this);
    newDrawAction->setIcon(QIcon(":/icon/newFile6.png"));
    newDrawAction->setShortcut(QKeySequence::New);
    newDrawAction->setStatusTip(tr("Create a new drawing"));
    connect(newDrawAction, SIGNAL(triggered()), this, SLOT(newEdit()));

    openPicAction = new QAction(tr("&Open"), this);
    openPicAction->setIcon(QIcon(":/icon/newFile7.png"));
    openPicAction->setShortcut(QKeySequence::Open);
    openPicAction->setStatusTip(tr("Open an existing pic"));
    connect(openPicAction, SIGNAL(triggered()), this, SLOT(openPic()));

    for(int i = 0;i < MaxRecentFiles;i ++){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/icon/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current editting file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"),this);
    saveAsAction->setIcon(QIcon(":/icon/saveAs.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the current file as another type of file"));
    connect(saveAsAction, SIGNAL(triggered()), this ,SLOT(saveAs()));

    closeAction = new QAction(tr("&Close"),this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close this window"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Alt+F4"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/icon/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/icon/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the clipboard"));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/icon/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/icon/delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's contents"));

    selectSequareAction = new QAction(tr("Se&lect"), this);
    selectSequareAction->setIcon(QIcon(":/icon/select.png"));
    selectSequareAction->setShortcut(tr("Ctrl+Q"));
    selectSequareAction->setStatusTip(tr("Select the choosen sequare area to the clipboard"));

    zoomInAction = new QAction(tr("&ZoomIn"), this);
    zoomInAction->setIcon(QIcon(":/icon/zoomIn.png"));
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomInAction->setStatusTip(tr("Zoom in the picture"));

    zoomOutAction = new QAction(tr("Zoom&Out"), this);
    zoomOutAction->setIcon(QIcon(":/icon/zoomOut.png"));
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    zoomOutAction->setStatusTip(tr("Zoom out the picture"));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newDrawAction);
    fileMenu->addAction(openPicAction);
    fileMenu->addSeparator();
    for(int i = 0;i < MaxRecentFiles; i ++){
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(selectSequareAction);
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));

    optionsMenu = menuBar()->addMenu(tr("&Options"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createContextMenu(){

}

void MainWindow::createToolBars(){
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newDrawAction);
    fileToolBar->addAction(openPicAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(selectSequareAction);
    editToolBar->addAction(zoomInAction);
    editToolBar->addAction(zoomOutAction);
}

void MainWindow::createStatusBar(){
    pixLocation = new QLabel("Row:960  Column:1440");
    pixLocation->setAlignment(Qt::AlignHCenter);
    pixLocation->setMinimumSize(pixLocation->sizeHint());

    pixValue = new QLabel("R:000  G:000  B:000 ");
    pixValue->setIndent(3);

    statusBar()->addWidget(pixLocation);
    statusBar()->addWidget(pixValue,1);

    updateStatusBar();
}

void MainWindow::createLayOut(){
    // set the mdiarea of mainwindow, if set tab view, use setdocumentmode & settabview
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateActions()));
    // set the subwindow in a tab view mode
//    mdiArea->setViewMode(QMdiArea::TabbedView);
//    mdiArea->setTabShape(QTabWidget::Triangular);
//    mdiArea->setTabsMovable(true);
//    mdiArea->setTabsClosable(true);

    // set the window to be maximized when open up
    setWindowState(Qt::WindowMaximized);
}


void MainWindow::updateRecentFileActions(){

}


PicEditWindow* MainWindow::activePicEdit(){
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    if(subWindow){
        return qobject_cast<PicEditWindow*>(subWindow->widget());
    }else{
        return 0;
    }
}


// testify if there is unsaved documents among all the subwindows
bool MainWindow::nonSavedSubwindowExisit(){
    int subWindowNum = mdiArea->subWindowList().size();
    for(int i = 0; i < subWindowNum; i ++){
        if(mdiArea->subWindowList().at(i)->isWindowModified() == true){
            return true;
        }
    }

    return false;
}


// to display a warning while close the whole program
bool MainWindow::okToClose(){
    if (nonSavedSubwindowExisit()) {
        int r = QMessageBox::warning(this, tr("Close picEdit"),
                                     tr("There are images that has been modified.\n Do you want to close?"),
                                     QMessageBox::Yes |  QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return true;
        }else if (r == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}
