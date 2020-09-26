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
    lineEditArtist->clear();
    lineEditTitle->clear();
    lineEditAlbum->clear();
    lineEditGenre->clear();
    lineEditFilePath->clear();
    lineEditYear->clear();
    lineEditTrack->clear();
    lineEditComment->clear();
    imageLabel->clear();
    editSongWidget->hide();
    infoLabel->show();
}

void TagEditor::cleanTable() {
    audioFilesMap.clear();
    m_filesTable->clearContents();
    m_filesTable->setRowCount(0);
    cleanContent();
}

void TagEditor::undo() {
    lineEditArtist->undo();
    lineEditTitle->undo();
    lineEditAlbum->undo();
    lineEditGenre->undo();
    lineEditFilePath->undo();
    lineEditYear->redo();
    lineEditTrack->redo();
    lineEditComment->redo();
}

void TagEditor::redo() {
    lineEditArtist->redo();
    lineEditTitle->redo();
    lineEditAlbum->redo();
    lineEditGenre->redo();
    lineEditFilePath->redo();
    lineEditYear->undo();
    lineEditTrack->undo();
    lineEditComment->undo();
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