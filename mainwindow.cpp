#include "mainwindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QMdiSubWindow>


MainWindow::MainWindow(){
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateActions()));

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    createLayOut();

    setWindowTitle(QString(tr("%1   copyrights: %2").arg("picEdit").arg("nop-end")));
    setAttribute(Qt::WA_DeleteOnClose);
    loadFiles();
}

/*--------------- Private SLOTS ---------------*/
void MainWindow::updateActions(){

}


void MainWindow::newDraw(){
//    ImageDisp* imageDispUnfilled = new ImageDisp();
//    addImageDisp(imageDispUnfilled);
    SelfDraw* newSelfDraw = new SelfDraw();
    addNewDraw(newSelfDraw);
}

void MainWindow::openPic(){
    if(okToContinue()){
        // if you replace the "/home/hupanhust" with ".", it will guide you to the debug file folder
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home/hupanhust", tr("Image Files (*.*)"));
        if(!fileName.isEmpty()){
            ImageDisp* imageDispFilled = new ImageDisp(fileName);
            addImageDisp(imageDispFilled);
        }
    }

}

void MainWindow::openVideo(){

}

void MainWindow::loadFiles(){
    newDraw();
}

bool MainWindow::save(){

    return true;
}

bool MainWindow::saveAs(){

    return true;
}

void MainWindow::preStep(){

}

void MainWindow::nextStep(){

}

void MainWindow::openRecentFile(){

}

void MainWindow::updateStatusBar(){

}

void MainWindow::picModified(){

}

void MainWindow::about(){

}


/*--------------- Private Functions ---------------*/
void MainWindow::createActions(){
    newDrawAction = new QAction(tr("&New Selfdraw"), this);
    newDrawAction->setIcon(QIcon(":/images/new.png"));
    newDrawAction->setShortcut(QKeySequence::New);
    newDrawAction->setStatusTip(tr("Create a new drawing"));
    connect(newDrawAction, SIGNAL(triggered()), this, SLOT(newDraw()));

    openPicAction = new QAction(tr("&Open Image"), this);
    openPicAction->setIcon(QIcon(":/images/open.png"));
    openPicAction->setShortcut(QKeySequence::Open);
    openPicAction->setStatusTip(tr("Open an existing pic"));
    connect(openPicAction, SIGNAL(triggered()), this, SLOT(openPic()));

    for(int i = 0;i < MaxRecentFiles;i ++){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current editting file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"),this);
    saveAsAction->setIcon(QIcon(":/images/saveAs.png"));
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
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the clipboard"));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/images/delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's contents"));

    selectSequareAction = new QAction(tr("S&elect"), this);
    selectSequareAction->setIcon(QIcon(":/images/selectsequare.png"));
    selectSequareAction->setShortcut(tr("Ctrl+Q"));
    selectSequareAction->setStatusTip(tr("Select the choosen sequare area to the clipboard"));

    zoomAction = new QAction(tr("&Zoom"), this);
    zoomAction->setIcon(QIcon(":/images/zoom.png"));
    zoomAction->setShortcut(QKeySequence::ZoomOut);
    zoomAction->setStatusTip(tr("Zoom out the picture"));

    shrinkAction = new QAction(tr("S&hrink"), this);
    shrinkAction->setIcon(QIcon(":/images/shrink.png"));
    shrinkAction->setShortcut(QKeySequence::ZoomIn);
    shrinkAction->setStatusTip(tr("Zoom in the picture"));

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
    editMenu->addAction(zoomAction);
    editMenu->addAction(shrinkAction);

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
    editToolBar->addAction(zoomAction);
    editToolBar->addAction(shrinkAction);
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

}


void MainWindow::updateRecentFileActions(){

}

bool MainWindow::okToContinue(){
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("PicEdit"),tr("The document has been modified.\n Do you want to save your changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

void MainWindow::addImageDisp(ImageDisp* imgd){
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(imgd);
    subWindow->show();
}

void MainWindow::addNewDraw(SelfDraw *selfd){
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(selfd);
    subWindow->show();
}
