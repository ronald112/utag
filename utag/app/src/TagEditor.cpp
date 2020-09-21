#include "TagEditor.h"
#include "AudioFile/AudioFile.h"
#include <MiscHeaders.h>
#include <iostream>

TagEditor::TagEditor()
{
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    m_projectPath = QFileSystemModel().rootDirectory().absolutePath();

    createTreeView();
    createButtons();
    createLayouts();

    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
        qApp, &QApplication::quit);
    // shortcut to fast quit
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("uTag"));
    setMinimumSize(800, 500);
    resize(800, 500);
}

void TagEditor::createTreeView() {
    treeView = new QTreeView(this);
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath("");
    dirmodel->setReadOnly(false);
    treeView->setModel(dirmodel);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    treeView->setMinimumWidth(350);
    treeView->setMaximumWidth(350);
    treeView->header()->hideSection(2);
    treeView->setColumnWidth(0, 160);
    treeView->setColumnWidth(1, 80);
    treeView->setAnimated(true);

    connect(treeView, &QTreeView::doubleClicked, this, &TagEditor::treeDoubleClick);


    infoLabel = new QLabel(tr("<i>(nothing to display)</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
}

void TagEditor::createButtons() {
    // create menu buttons
    saveButton = new QPushButton(this);
    undoButton = new QPushButton(this);
    redoButton = new QPushButton(this);
    aboutButton = new QPushButton(this);
    aboutQtButton = new QPushButton(this);

    // customize buttons
    saveButton->setFixedWidth(40);
    saveButton->setIconSize(QSize(15, 15));
    saveButton->setIcon(QIcon(m_projectPath + "/resources/save.png"));
    undoButton->setFixedWidth(40);
    undoButton->setIconSize(QSize(15, 15));
    undoButton->setIcon(QIcon(m_projectPath + "/resources/undo.png"));
    redoButton->setFixedWidth(40);
    redoButton->setIconSize(QSize(15, 15));
    redoButton->setIcon(QIcon(m_projectPath + "/resources/redo.png"));
    aboutButton->setFixedWidth(40);
    aboutButton->setIconSize(QSize(15, 15));
    aboutButton->setIcon(QIcon(m_projectPath + "/resources/about.png"));
    aboutQtButton->setFixedWidth(40);
    aboutQtButton->setIconSize(QSize(15, 15));
    aboutQtButton->setIcon(QIcon(m_projectPath + "/resources/about_qt.png"));

    // connect menu buttons
    connect(saveButton, &QAbstractButton::clicked, this, &TagEditor::save);
    connect(undoButton, &QAbstractButton::clicked, this, &TagEditor::undo);
    connect(redoButton, &QAbstractButton::clicked, this, &TagEditor::redo);
    connect(aboutButton, &QAbstractButton::clicked, this, &TagEditor::about);
    connect(aboutQtButton, &QAbstractButton::clicked, this, &QApplication::aboutQt);

    // set up shortcuts
    saveButton->setShortcut(QKeySequence::Save);
    undoButton->setShortcut(QKeySequence::Undo);
    redoButton->setShortcut(QKeySequence::Redo);

    // set up tips
    aboutQtButton->setStatusTip(tr("Show the Qt library's About box"));
    aboutButton->setStatusTip(tr("Show the Application's About box"));
    saveButton->setStatusTip(tr("Save a file"));
    undoButton->setStatusTip(tr("Undo changes"));
    redoButton->setStatusTip(tr("Redo changes"));
}

void TagEditor::createLayouts()
{
    QHBoxLayout *layoutH = new QHBoxLayout();
    QVBoxLayout* layoutV = new QVBoxLayout();
    QHBoxLayout* layoutButttons = new QHBoxLayout();
    m_filesTable = new QTableWidget(0, 5);
    m_filesFoundLabel = new QLabel(tr("<i>0 files</i>"));

    layoutButttons->setAlignment(Qt::AlignLeft);
    layoutButttons->addWidget(saveButton);
    layoutButttons->addWidget(undoButton);
    layoutButttons->addWidget(redoButton);
    layoutButttons->addWidget(aboutButton);
    layoutButttons->addWidget(aboutQtButton);

    m_filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_filesTable->setHorizontalHeaderLabels(QStringList({"Artist", "Title", "Album", "Genre", "Path"}));
    // m_filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_filesTable->verticalHeader()->hide();
    m_filesTable->setShowGrid(false);
    connect(m_filesTable, &QTableWidget::doubleClicked,
            this, &TagEditor::openFileOfItem);

    layoutV->addLayout(layoutButttons);
    layoutV->addWidget(m_filesFoundLabel);
    layoutV->addWidget(m_filesTable);
    layoutV->addWidget(infoLabel, Qt::AlignBottom);

    layoutH->setMargin(7);
    layoutH->setSpacing(3);
    layoutH->addWidget(treeView);
    layoutH->addLayout(layoutV);

    mainWidget->setLayout(layoutH);
}

void TagEditor::openFileOfItem() {
    // const QTableWidgetItem *item = m_filesTable->item(row, 0);
    QMessageBox msgBox;
    msgBox.setText("Interacting with file table");
    msgBox.exec();
    // openFile(item->data(1).toString());
}

// static inline void openFile(const QString &fileName)
// {
//     QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
// }

void TagEditor::treeDoubleClick() {
    QModelIndex index = treeView->currentIndex();
    QMessageBox msgBox;
    if (!index.isValid()) {
        msgBox.setText("Get folder index error");
        msgBox.exec();
        return;
    }
    // dirmodel->fileInfo(index).absolutePath()
    // QString name = QInputDialog::getText(this, "Name", "Enter directory name");
    // if (name.isEmpty()) return;
    // index.data(0).toString()
    QString audioFilePath = dirmodel->fileInfo(index).absoluteFilePath();
    AudioFile a(TagLib::FileRef(audioFilePath.toStdString().c_str()));

    a.prettyConsoleOutput();
    msgBox.setText(audioFilePath); // abs path to dir

    msgBox.exec();
}

void TagEditor::open() {
    
}

void TagEditor::undo() {
    
}

void TagEditor::redo() {
    
}

void TagEditor::about() {
    
}

void TagEditor::save() {
    
}


TagEditor::~TagEditor() {
}