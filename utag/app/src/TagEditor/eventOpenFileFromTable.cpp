#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::eventOpenFileFromTable(int row) {
    QTableWidgetItem *item = m_filesTable->item(row, 4);
    std::string filePath = item->data(0).toString().toStdString();
    auto it = audioFilesMap.find(filePath);

    if (it != audioFilesMap.end()) {
        infoLabel->hide();
        lineEditArtist->clear();
        lineEditTitle->clear();
        lineEditAlbum->clear();
        lineEditGenre->clear();
        lineEditFilePath->clear();
        lineEditArtist->setText(tr(it->second.getProperty("ARTIST").c_str()));
        lineEditTitle->setText(tr(it->second.getProperty("TITLE").c_str()));
        lineEditAlbum->setText(tr(it->second.getProperty("ALBUM").c_str()));
        lineEditGenre->setText(tr(it->second.getProperty("GENRE").c_str()));
        lineEditFilePath->setText(tr(filePath.c_str()));
        curEditableFilePath = tr(filePath.c_str());
        curSelectedRow = row;
        editSongWidget->show();
    }
    else {
        QMessageBox::critical(this, tr("uTag"),
        tr("Error opening file"), QMessageBox::Ok | QMessageBox::Cancel);
    }
}
