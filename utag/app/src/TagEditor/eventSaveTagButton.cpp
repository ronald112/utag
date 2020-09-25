#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::save() {
    if ((QMessageBox::question(this, tr("uTag"),
    tr("Do you really want to save changes?"),
    QMessageBox::Ok | QMessageBox::Cancel),
    QMessageBox::Ok) == QMessageBox::Ok) {
        auto edit = audioFilesMap.find(curEditableFilePath.toStdString());
        if (edit != audioFilesMap.end() && curSelectedRow != -1) {
            if (lineEditArtist->isModified()) {
                edit->second.saveFieldWithValue('a', lineEditArtist->text().toStdString());
            }
            if (lineEditTitle->isModified()) {
                edit->second.saveFieldWithValue('t', lineEditTitle->text().toStdString());
            }
            if (lineEditAlbum->isModified()) {
                edit->second.saveFieldWithValue('A', lineEditAlbum->text().toStdString());
            }
            if (lineEditGenre->isModified()) {
                edit->second.saveFieldWithValue('g', lineEditGenre->text().toStdString());
            }
            if (lineEditYear->isModified()) {
                edit->second.saveFieldWithValue('y', lineEditYear->text().toStdString());
            }
            if (lineEditTrack->isModified()) {
                edit->second.saveFieldWithValue('T', lineEditTrack->text().toStdString());
            }
            if (lineEditComment->isModified()) {
                edit->second.saveFieldWithValue('c', lineEditComment->text().toStdString());
            }
            m_filesTable->removeRow(curSelectedRow);
            audioFilesMap.erase(edit);
            addItemToTableHandler(false, curEditableFilePath, tr(edit->second.fileName.c_str()));
            editSongWidget->hide();
            lineEditArtist->clear();
            lineEditTitle->clear();
            lineEditAlbum->clear();
            lineEditGenre->clear();
            lineEditFilePath->clear();
            lineEditYear->clear();
            lineEditTrack->clear();
            lineEditComment->clear();
            imageLabel->clear();
            infoLabel->show();
        }
    }

}
