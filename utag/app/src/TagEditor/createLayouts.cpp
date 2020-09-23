#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createLayouts()
{
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

    connect(m_filesTable, &QTableWidget::doubleClicked,
            this, &TagEditor::openFileOfItem);

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
    QLabel *label1 = new QLabel("Artist");
    QLineEdit *lineEdit1 = new QLineEdit();
    QLabel *label2 = new QLabel("Title");
    QLineEdit *lineEdit2 = new QLineEdit();
    QLabel *label3 = new QLabel("Album");
    QLineEdit *lineEdit3 = new QLineEdit();
    QLabel *label4 = new QLabel("Album");
    QLineEdit *lineEdit4 = new QLineEdit();
    QLabel *label5 = new QLabel("Album");
    QLineEdit *lineEdit5 = new QLineEdit();

    editSongLayout = new QFormLayout();
    editSongLayout->addRow(label1, lineEdit1);
    editSongLayout->addRow(label2, lineEdit2);
    editSongLayout->addRow(label3, lineEdit3);
    editSongLayout->addRow(label4, lineEdit4);
    editSongLayout->addRow(label5, lineEdit5);
    // rightBotWidget->setLayout(editSongLayout);
}


