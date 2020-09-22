#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createLayouts()
{
    QHBoxLayout *layoutH = new QHBoxLayout();
    QVBoxLayout* layoutV = new QVBoxLayout();
    QHBoxLayout* layoutButttons = new QHBoxLayout();
    m_filesTable = new QTableWidget(0, 5, this);
    m_filesFoundLabel = new QLabel(tr("<i>0 files</i>"), this);

    layoutButttons->setAlignment(Qt::AlignLeft);
    layoutButttons->addWidget(saveButton);
    layoutButttons->addWidget(undoButton);
    layoutButttons->addWidget(redoButton);
    layoutButttons->addWidget(aboutButton);
    layoutButttons->addWidget(aboutQtButton);

    m_filesTable->setSortingEnabled(true);
    m_filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_filesTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_filesTable->setHorizontalHeaderLabels(QStringList({"Artist", "Title", "Album", "Genre", "Path"}));
    m_filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_filesTable->verticalHeader()->hide();
    m_filesTable->setShowGrid(false);
    m_filesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_filesTable, &QTableWidget::doubleClicked,
            this, &TagEditor::openFileOfItem);

    layoutV->addLayout(layoutButttons);
    layoutV->addWidget(m_filesFoundLabel);
    layoutV->addWidget(m_filesTable, Qt::AlignBottom);
    layoutV->addWidget(infoLabel, Qt::AlignBottom);

    layoutH->setMargin(7);
    layoutH->setSpacing(3);
    layoutH->addWidget(treeView, Qt::AlignLeft);
    layoutH->addLayout(layoutV, Qt::AlignLeft);

    mainWidget->setLayout(layoutH);
}
