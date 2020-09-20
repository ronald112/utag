#include "TagEditor.h"
#include <iostream>

TagEditor::TagEditor()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    m_menuBar = new QMenuBar(this);

    treeView = new QTreeView(this);
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath("");
    treeView->setModel(dirmodel);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    treeView->setMinimumWidth(350);
    treeView->setMaximumWidth(350);

    treeView->header()->hideSection(2);
    treeView->setColumnWidth(0, 160);
    treeView->setColumnWidth(1, 80);

    infoLabel = new QLabel(tr("<i>(nothing to display)</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layoutV = new QVBoxLayout();
    m_filesTable = new QTableWidget(this);
    m_filesFoundLabel = new QLabel(tr("<i>0 files</i>"));

    layoutV->addWidget(m_menuBar);
    layoutV->addWidget(m_filesFoundLabel);
    layoutV->addWidget(m_filesTable);
    layoutV->addWidget(infoLabel);

    QHBoxLayout *layoutH = new QHBoxLayout();
    layoutH->setMargin(7);
    layoutH->setSpacing(3);
    layoutH->addWidget(treeView);
    layoutH->addLayout(layoutV);
    widget->setLayout(layoutH);

    createActions();
    createMenus();
    

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);


    setWindowTitle(tr("uTag"));
    setMinimumSize(800, 500);
    resize(800, 500);
}

void TagEditor::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &TagEditor::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &TagEditor::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, &QAction::triggered, this, &TagEditor::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit"));
    connect(exitAct, &QAction::triggered, this, &QCoreApplication::exit);
}

void TagEditor::newFile() {

}

void TagEditor::open() {
    
}

void TagEditor::save() {
    
}

void TagEditor::createMenus()
{
    fileMenu = m_menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    m_menuBar->setNativeMenuBar(false);
    m_menuBar->show();
}

#ifndef QT_NO_CONTEXTMENU
void TagEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    // menu.addAction(cutAct);
    // menu.addAction(copyAct);
    // menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

TagEditor::~TagEditor() {
}