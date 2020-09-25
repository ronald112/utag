#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createButtons() {
    // create menu buttons
    saveButton = new QPushButton(this);
    undoButton = new QPushButton(this);
    redoButton = new QPushButton(this);
    aboutButton = new QPushButton(this);
    aboutQtButton = new QPushButton(this);
    cleanButton = new QPushButton(this);

    // customize buttons
    saveButton->setFixedWidth(30);
    saveButton->setIconSize(QSize(15, 15));
    saveButton->setIcon(QIcon(m_projectPath + "/resources/save.png"));
    undoButton->setFixedWidth(30);
    undoButton->setIconSize(QSize(15, 15));
    undoButton->setIcon(QIcon(m_projectPath + "/resources/undo.png"));
    redoButton->setFixedWidth(30);
    redoButton->setIconSize(QSize(15, 15));
    redoButton->setIcon(QIcon(m_projectPath + "/resources/redo.png"));
    aboutButton->setFixedWidth(30);
    aboutButton->setIconSize(QSize(15, 15));
    aboutButton->setIcon(QIcon(m_projectPath + "/resources/about.png"));
    aboutQtButton->setFixedWidth(30);
    aboutQtButton->setIconSize(QSize(15, 15));
    aboutQtButton->setIcon(QIcon(m_projectPath + "/resources/about_qt.png"));
    cleanButton->setFixedWidth(30);
    cleanButton->setIconSize(QSize(15, 15));
    cleanButton->setIcon(QIcon(m_projectPath + "/resources/clean.png"));

    // connect menu buttons
    connect(saveButton, &QAbstractButton::clicked, this, &TagEditor::save);
    connect(undoButton, &QAbstractButton::clicked, this, &TagEditor::undo);
    connect(redoButton, &QAbstractButton::clicked, this, &TagEditor::redo);
    connect(aboutButton, &QAbstractButton::clicked, this, &TagEditor::about);
    connect(aboutQtButton, &QAbstractButton::clicked, this, &QApplication::aboutQt);
    connect(cleanButton, &QAbstractButton::clicked, this, &TagEditor::clean);

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
    cleanButton->setStatusTip(tr("Remove selection"));
}
