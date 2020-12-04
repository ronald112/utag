#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createButtons() {
    // create menu buttons
    m_saveButton = new QPushButton(this);
    m_undoButton = new QPushButton(this);
    m_redoButton = new QPushButton(this);
    m_aboutButton = new QPushButton(this);
    m_aboutQtButton = new QPushButton(this);
    m_cleanTableButton = new QPushButton(this);
    m_cleanContentButton = new QPushButton("Clean content", this);

    // customize buttons
    m_saveButton->setFixedWidth(40);
    m_saveButton->setIconSize(QSize(15, 15));
    m_saveButton->setIcon(QIcon( "./utag/resources/save.ico"));
    m_undoButton->setFixedWidth(40);
    m_undoButton->setIconSize(QSize(15, 15));
    m_undoButton->setIcon(QIcon("./utag/resources/undo.png"));
    m_redoButton->setFixedWidth(40);
    m_redoButton->setIconSize(QSize(15, 15));
    m_redoButton->setIcon(QIcon("./utag/resources/redo.png"));
    m_aboutButton->setFixedWidth(40);
    m_aboutButton->setIconSize(QSize(15, 15));
    m_aboutButton->setIcon(QIcon("./utag/resources/about.png"));
    m_aboutQtButton->setFixedWidth(40);
    m_aboutQtButton->setIconSize(QSize(15, 15));
    m_aboutQtButton->setIcon(QIcon("./utag/resources/about_qt.png"));
    m_cleanTableButton->setFixedWidth(40);
    m_cleanTableButton->setIconSize(QSize(15, 15));
    m_cleanTableButton->setIcon(QIcon("./utag/resources/clean.png"));

    // connect menu buttons
    connect(m_saveButton, &QAbstractButton::clicked, this, &TagEditor::save);
    connect(m_undoButton, &QAbstractButton::clicked, this, &TagEditor::undo);
    connect(m_redoButton, &QAbstractButton::clicked, this, &TagEditor::redo);
    connect(m_aboutButton, &QAbstractButton::clicked, this, &TagEditor::about);
    connect(m_aboutQtButton, &QAbstractButton::clicked, this, &QApplication::aboutQt);
    connect(m_cleanTableButton, &QAbstractButton::clicked, this, &TagEditor::cleanTable);
    connect(m_cleanContentButton, &QAbstractButton::clicked, this, &TagEditor::cleanContent);

    // set up shortcuts
    m_saveButton->setShortcut(QKeySequence::Save);
    m_undoButton->setShortcut(QKeySequence::Undo);
    m_redoButton->setShortcut(QKeySequence::Redo);

    // set up tips
    m_aboutQtButton->setStatusTip(tr("Show the Qt library's About box"));
    m_aboutButton->setStatusTip(tr("Show the Application's About box"));
    m_saveButton->setStatusTip(tr("Save a file"));
    m_undoButton->setStatusTip(tr("Undo changes"));
    m_redoButton->setStatusTip(tr("Redo changes"));
    m_cleanTableButton->setStatusTip(tr("Remove selection"));
}
