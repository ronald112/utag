#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::save() {
    if ((QMessageBox::question(this, tr("uTag"),
    tr("Do you really want to save changes?"),
    QMessageBox::Ok | QMessageBox::Cancel),
    QMessageBox::Ok) == QMessageBox::Ok) {
        auto edit = m_audioFilesMap.find(m_curEditableFilePath.toStdString());
        if (edit != m_audioFilesMap.end() && m_curSelectedRow != -1) {
            if (m_lineEditArtist->isModified()) {
                edit->second.saveFieldWithValue('a', m_lineEditArtist->text().toStdString());
            }
            if (m_lineEditTitle->isModified()) {
                edit->second.saveFieldWithValue('t', m_lineEditTitle->text().toStdString());
            }
            if (m_lineEditAlbum->isModified()) {
                edit->second.saveFieldWithValue('A', m_lineEditAlbum->text().toStdString());
            }
            if (m_lineEditGenre->isModified()) {
                edit->second.saveFieldWithValue('g', m_lineEditGenre->text().toStdString());
            }
            if (m_lineEditYear->isModified()) {
                edit->second.saveFieldWithValue('y', m_lineEditYear->text().toStdString());
            }
            if (m_lineEditTrack->isModified()) {
                edit->second.saveFieldWithValue('T', m_lineEditTrack->text().toStdString());
            }
            if (m_lineEditComment->isModified()) {
                edit->second.saveFieldWithValue('c', m_lineEditComment->text().toStdString());
            }
            m_filesTable->removeRow(m_curSelectedRow);
            m_audioFilesMap.erase(edit);
            addItemToTableHandler(false, m_curEditableFilePath, tr(edit->second.fileName.c_str()));
            m_editSongWidget->hide();
            m_lineEditArtist->clear();
            m_lineEditTitle->clear();
            m_lineEditAlbum->clear();
            m_lineEditGenre->clear();
            m_lineEditFilePath->clear();
            m_lineEditYear->clear();
            m_lineEditTrack->clear();
            m_lineEditComment->clear();
            m_imageLabel->clear();
            m_infoLabel->show();
        }
    }

}
