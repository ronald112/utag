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
    m_plug = new QLabel(this);
    m_filesTable = new QTableWidget(0, 5, this);

    butttonLayout->setMargin(0);
    butttonLayout->addWidget(saveButton, Qt::AlignLeft);
    butttonLayout->addWidget(undoButton, Qt::AlignLeft);
    butttonLayout->addWidget(redoButton, Qt::AlignLeft);
    butttonLayout->addWidget(cleanButton, Qt::AlignLeft);
    butttonLayout->addWidget(aboutButton, Qt::AlignLeft);
    butttonLayout->addWidget(aboutQtButton, Qt::AlignLeft);
    butttonLayout->addWidget(m_plug, Qt::AlignRight);

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
    QGridLayout* editSongGridLayout = new QGridLayout(editSongWidget);
    editSongWidget->hide();
    lineEditArtist = new QLineEdit(contentVSplitter);
    lineEditTitle = new QLineEdit(contentVSplitter);
    lineEditAlbum = new QLineEdit(contentVSplitter);
    lineEditGenre = new QLineEdit(contentVSplitter);
    lineEditFilePath = new QLineEdit(contentVSplitter);
    lineEditYear = new QLineEdit(contentVSplitter);
    lineEditTrack = new QLineEdit(contentVSplitter);
    lineEditComment = new QLineEdit(contentVSplitter);
    QLabel *label1 = new QLabel("Artist");
    QLabel *label2 = new QLabel("Title");
    QLabel *label3 = new QLabel("Album");
    QLabel *label4 = new QLabel("Genre");
    QLabel *label5 = new QLabel("Path");
    QLabel *label6 = new QLabel("Year");
    QLabel *label7 = new QLabel("Track");
    QLabel *label8 = new QLabel("Comment");
    imageLabel = new QLabel();

    editSongGridLayout->addWidget(label1, 0, 0);
    editSongGridLayout->addWidget(lineEditArtist, 0, 1);
    editSongGridLayout->addWidget(label2, 1, 0);
    editSongGridLayout->addWidget(lineEditTitle, 1, 1);
    editSongGridLayout->addWidget(label3, 2, 0);
    editSongGridLayout->addWidget(lineEditAlbum, 2, 1);
    editSongGridLayout->addWidget(label4, 3, 0);
    editSongGridLayout->addWidget(lineEditGenre, 3, 1);
    editSongGridLayout->addWidget(label5, 4, 0);
    editSongGridLayout->addWidget(lineEditFilePath, 4, 1, 1, 3);
    editSongGridLayout->addWidget(label6, 0, 2);
    editSongGridLayout->addWidget(lineEditYear, 0, 3);
    editSongGridLayout->addWidget(label7, 1, 2);
    editSongGridLayout->addWidget(lineEditTrack, 1, 3);
    editSongGridLayout->addWidget(label8, 2, 2);
    editSongGridLayout->addWidget(lineEditComment, 2, 3);
    editSongGridLayout->addWidget(imageLabel, 0, 4, 4, 1);
    botLayout->addWidget(editSongWidget, Qt::AlignTop);
}


