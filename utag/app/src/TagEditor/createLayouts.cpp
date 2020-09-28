#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createLayouts() {
    m_contentVSplitter = new QSplitter(Qt::Vertical, m_mainSplitter);
    m_rightTopWidget = new QWidget(m_contentVSplitter);
    m_rightBotWidget = new QWidget(m_contentVSplitter);
    m_buttonWidget = new QWidget(m_contentVSplitter);
    m_topVLayout = new QVBoxLayout(m_rightTopWidget);
    m_butttonLayout = new QHBoxLayout(m_buttonWidget);
    m_botLayout = new QVBoxLayout(m_rightBotWidget);
    m_plug = new QLabel(this);
    m_filesTable = new QTableWidget(0, 5, this);

    m_butttonLayout->setMargin(0);
    m_butttonLayout->setSpacing(5);
    m_butttonLayout->addWidget(m_saveButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_undoButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_redoButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_cleanTableButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_aboutButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_aboutQtButton, Qt::AlignLeft);
    m_butttonLayout->addWidget(m_plug, Qt::AlignRight);

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

    m_topVLayout->setMargin(0);
    m_topVLayout->setSpacing(0);
    m_topVLayout->addWidget(m_buttonWidget);
    m_topVLayout->addWidget(m_filesTable, Qt::AlignTop);

    m_botLayout->setMargin(0);
    m_botLayout->setSpacing(0);
    m_botLayout->addWidget(m_infoLabel, Qt::AlignTop);

    m_contentVSplitter->addWidget(m_rightTopWidget);
    m_contentVSplitter->addWidget(m_rightBotWidget);
    m_rightBotWidget->setFixedHeight(150);

    m_mainSplitter->setContentsMargins(5, 5, 5, 5);
    m_mainSplitter->addWidget(m_treeView);
    m_mainSplitter->addWidget(m_contentVSplitter);
    m_mainSplitter->setSizes(QList<int>({ 1, 400}));
    // m_mainSplitter->setStyleSheet("background-color:silver;");
    createEditSongLayout();
}

void TagEditor::createEditSongLayout() {
    m_editSongWidget = new QWidget(m_contentVSplitter);
    QGridLayout* editSongGridLayout = new QGridLayout(m_editSongWidget);
    m_editSongWidget->hide();
    m_lineEditArtist = new QLineEdit(m_contentVSplitter);
    m_lineEditTitle = new QLineEdit(m_contentVSplitter);
    m_lineEditAlbum = new QLineEdit(m_contentVSplitter);
    m_lineEditGenre = new QLineEdit(m_contentVSplitter);
    m_lineEditFilePath = new QLineEdit(m_contentVSplitter);
    m_lineEditYear = new QLineEdit(m_contentVSplitter);
    m_lineEditTrack = new QLineEdit(m_contentVSplitter);
    m_lineEditComment = new QLineEdit(m_contentVSplitter);
    QLabel *label1 = new QLabel("Artist");
    QLabel *label2 = new QLabel("Title");
    QLabel *label3 = new QLabel("Album");
    QLabel *label4 = new QLabel("Genre");
    QLabel *label5 = new QLabel("Path");
    QLabel *label6 = new QLabel("Year");
    QLabel *label7 = new QLabel("Track");
    QLabel *label8 = new QLabel("Comment");
    m_imageLabel = new QLabel();

    // set validators
    m_lineEditYear->setValidator(new QIntValidator(0, 2020, this));
    m_lineEditTrack->setValidator(new QIntValidator(0, 100, this));

    editSongGridLayout->addWidget(label1, 0, 0);
    editSongGridLayout->addWidget(m_lineEditArtist, 0, 1);
    editSongGridLayout->addWidget(label2, 1, 0);
    editSongGridLayout->addWidget(m_lineEditTitle, 1, 1);
    editSongGridLayout->addWidget(label3, 2, 0);
    editSongGridLayout->addWidget(m_lineEditAlbum, 2, 1);
    editSongGridLayout->addWidget(label4, 3, 0);
    editSongGridLayout->addWidget(m_lineEditGenre, 3, 1);
    editSongGridLayout->addWidget(label5, 4, 0);
    editSongGridLayout->addWidget(m_lineEditFilePath, 4, 1, 1, 3);
    editSongGridLayout->addWidget(label6, 0, 2);
    editSongGridLayout->addWidget(m_lineEditYear, 0, 3);
    editSongGridLayout->addWidget(label7, 1, 2);
    editSongGridLayout->addWidget(m_lineEditTrack, 1, 3);
    editSongGridLayout->addWidget(label8, 2, 2);
    editSongGridLayout->addWidget(m_lineEditComment, 2, 3);
    editSongGridLayout->addWidget(m_imageLabel, 0, 4, 4, 1, Qt::AlignCenter);
    editSongGridLayout->addWidget(m_cleanContentButton, 4, 4);
    m_botLayout->addWidget(m_editSongWidget, Qt::AlignTop);
}


