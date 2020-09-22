#include "TagEditor.h"
#include <MiscHeaders.h>

TagEditor::TagEditor()
{
    setlocale(LC_ALL, "");
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    m_projectPath = QFileSystemModel(this).rootDirectory().absolutePath();

    createTreeView();
    createButtons();
    createLayouts();

    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
        qApp, &QApplication::quit);
    // shortcut to fast quit
    QString message = tr("Hints will be there >");
    statusBar()->showMessage(message);

    setWindowTitle(tr("uTag"));
    setMinimumSize(1200, 500);
    resize(1200, 500);
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