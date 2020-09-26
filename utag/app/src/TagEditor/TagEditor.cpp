#include "TagEditor.h"
#include <MiscHeaders.h>

TagEditor::TagEditor()
{
    setlocale(LC_ALL, "");
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(m_mainSplitter);
    m_projectPath = QFileSystemModel(this).rootDirectory().absolutePath();

    createTreeView();
    createButtons();
    createLayouts();

    // shortcut to fast quit
    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
        qApp, &QApplication::quit);

    statusBar()->showMessage(tr("Hints will be there >"));

    setWindowTitle(tr("uTag"));
    setMinimumSize(1000, 500);
    resize(1000, 500);
    cmdLineArgHandler();
}

void TagEditor::cmdLineArgHandler() {
    if (QCoreApplication::arguments().size() == 2) {
        std::regex pattern(R"(^.*\/([^.]+)$)");
        std::cmatch match;
        if (std::regex_match(QCoreApplication::arguments().at(1).toStdString().c_str(), match, pattern)) {
            addItemToTableHandler(true, QCoreApplication::arguments().at(1), tr(match.str(1).c_str()));
        }
    }
}

void TagEditor::cleanContent() {
    m_lineEditArtist->clear();
    m_lineEditTitle->clear();
    m_lineEditAlbum->clear();
    m_lineEditGenre->clear();
    m_lineEditFilePath->clear();
    m_lineEditYear->clear();
    m_lineEditTrack->clear();
    m_lineEditComment->clear();
    m_imageLabel->clear();
    m_editSongWidget->hide();
    m_infoLabel->show();
}

void TagEditor::cleanTable() {
    m_audioFilesMap.clear();
    m_filesTable->clearContents();
    m_filesTable->setRowCount(0);
    cleanContent();
}

void TagEditor::undo() {
    m_lineEditArtist->undo();
    m_lineEditTitle->undo();
    m_lineEditAlbum->undo();
    m_lineEditGenre->undo();
    m_lineEditFilePath->undo();
    m_lineEditYear->redo();
    m_lineEditTrack->redo();
    m_lineEditComment->redo();
}

void TagEditor::redo() {
    m_lineEditArtist->redo();
    m_lineEditTitle->redo();
    m_lineEditAlbum->redo();
    m_lineEditGenre->redo();
    m_lineEditFilePath->redo();
    m_lineEditYear->undo();
    m_lineEditTrack->undo();
    m_lineEditComment->undo();
}

void TagEditor::about() {
    QMessageBox::information(this, tr("uTag"),
        QString("This is a simple audio tag editor program.\n"
        "It can work with the following extensions:\n"
        "mp3|ogg|oga|mogg|flac|mpc|wav|mp4|asf|tta|aiff|spx|wv.\n"
        "You can change artist, title, album, genre, comment, "
        "year and track of the song.\nEnjoy!"),
        QMessageBox::Ok);
}


TagEditor::~TagEditor() {
}