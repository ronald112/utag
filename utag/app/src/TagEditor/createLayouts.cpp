#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createLayouts() {
    contentVSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    rightTopWidget = new QWidget(contentVSplitter);
    rightBotWidget = new QWidget(contentVSplitter);
    buttonWidget = new QWidget(contentVSplitter);
    topVLayout = new QVBoxLayout(rightTopWidget);
    butttonLayout = new QHBoxLayout(buttonWidget);
    botLayout = new QVBoxLayout(rightBotWidget);
    m_filesFoundLabel = new QLabel(this);
    m_filesTable = new QTableWidget(0, 5, this);

    butttonLayout->setMargin(0);
    butttonLayout->addWidget(saveButton, Qt::AlignLeft);
    butttonLayout->addWidget(undoButton, Qt::AlignLeft);
    butttonLayout->addWidget(redoButton, Qt::AlignLeft);
    butttonLayout->addWidget(aboutButton, Qt::AlignLeft);
    butttonLayout->addWidget(aboutQtButton, Qt::AlignLeft);
    butttonLayout->addWidget(m_filesFoundLabel, Qt::AlignRight);

    m_filesTable->setSortingEnabled(true);
    m_filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_filesTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_filesTable->setHorizontalHeaderLabels(QStringList({"Artist", "Title", "Album", "Genre", "Path"}));
    m_filesTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    m_filesTable->verticalHeader()->hide();
    m_filesTable->setShowGrid(true);
    m_filesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_filesTable, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(eventOpenFileFromTable(int)));

    topVLayout->setMargin(0);
    topVLayout->setSpacing(0);
    topVLayout->addWidget(buttonWidget);
    topVLayout->addWidget(m_filesTable, Qt::AlignTop);

    botLayout->setMargin(0);
    botLayout->setSpacing(0);
    botLayout->addWidget(infoLabel, Qt::AlignTop);

    contentVSplitter->addWidget(rightTopWidget);
    contentVSplitter->addWidget(rightBotWidget);
    rightBotWidget->setFixedHeight(150);

    mainSplitter->setContentsMargins(5, 5, 5, 5);
    mainSplitter->addWidget(treeView);
    mainSplitter->addWidget(contentVSplitter);
    mainSplitter->setSizes(QList<int>({ 1, 400}));
    mainSplitter->setStyleSheet("background-color:silver;");
    createEditSongLayout();
}

void TagEditor::createEditSongLayout() {
    editSongWidget = new QWidget(contentVSplitter);
    editSongLayout = new QFormLayout(editSongWidget);
    editSongWidget->hide();
    lineEditArtist = new QLineEdit();
    lineEditTitle = new QLineEdit();
    lineEditAlbum = new QLineEdit();
    lineEditGenre = new QLineEdit();
    lineEditFilePath = new QLineEdit();
    QLabel *label1 = new QLabel("Artist");
    QLabel *label2 = new QLabel("Title");
    QLabel *label3 = new QLabel("Album");
    QLabel *label4 = new QLabel("Genre");
    QLabel *label5 = new QLabel("Path");

    editSongLayout->addRow(label1, lineEditArtist);
    editSongLayout->addRow(label2, lineEditTitle);
    editSongLayout->addRow(label3, lineEditAlbum);
    editSongLayout->addRow(label4, lineEditGenre);
    editSongLayout->addRow(label5, lineEditFilePath);
    botLayout->addWidget(editSongWidget, Qt::AlignTop);
}


