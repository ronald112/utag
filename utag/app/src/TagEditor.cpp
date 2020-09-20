#include "TagEditor.h"
#include <iostream>

TagEditor::TagEditor()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFilter = new QWidget;
    topFilter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFilter = new QWidget;
    bottomFilter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFilter);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFilter);
    widget->setLayout(layout);

    createActions();
    createMenus();
    

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);


    setWindowTitle(tr("uTag"));
    setMinimumSize(260, 400);
    resize(320, 480);
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

void TagEditor::exit() {
    
}


void TagEditor::createMenus()
{
    // std::cerr << "[dbg 1]\n";
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    menuBar()->setNativeMenuBar(false);
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