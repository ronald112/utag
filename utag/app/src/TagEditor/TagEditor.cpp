#include "TagEditor.h"
#include <MiscHeaders.h>

TagEditor::TagEditor()
{
    setlocale(LC_ALL, "");
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(mainSplitter);
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
    setMinimumSize(1000, 500);
    resize(1000, 500);
}

// static inline void openFile(const QString &fileName)
// {
//     QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
// }

void TagEditor::undo() {
    
}

void TagEditor::redo() {
    
}

void TagEditor::about() {
    
}

TagEditor::~TagEditor() {
}