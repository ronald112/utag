#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::eventOpenFileFromTable(int row) {
    QTableWidgetItem *item = m_filesTable->item(row, 4);
    std::string filePath = item->data(0).toString().toStdString();
    auto it = m_audioFilesMap.find(filePath);

    if (it != m_audioFilesMap.end()) {
        m_infoLabel->hide();
        m_lineEditArtist->clear();
        m_lineEditTitle->clear();
        m_lineEditAlbum->clear();
        m_lineEditGenre->clear();
        m_lineEditFilePath->clear();
        m_lineEditYear->clear();
        m_lineEditTrack->clear();
        m_lineEditComment->clear();
        m_imageLabel->clear();
        QPixmap pixmap;
        QImage image = it->second.getAlbumArt();
        image = image.scaled(100, 100);
        pixmap = pixmap.fromImage(image);
        if (image.sizeInBytes() > 0 && pixmap.isNull() == false) {
            m_imageLabel->setPixmap(pixmap);
        }
        else {
            m_imageLabel->setText("No Image");
        }
        m_lineEditArtist->setText(tr(it->second.getProperty("ARTIST").c_str()));
        m_lineEditTitle->setText(tr(it->second.getProperty("TITLE").c_str()));
        m_lineEditAlbum->setText(tr(it->second.getProperty("ALBUM").c_str()));
        m_lineEditGenre->setText(tr(it->second.getProperty("GENRE").c_str()));
        m_lineEditFilePath->setText(tr(filePath.c_str()));
        m_lineEditYear->setText(tr(it->second.getProperty("YEAR").c_str()));
        m_lineEditTrack->setText(tr(it->second.getProperty("TRACKNUMBER").c_str()));
        m_lineEditComment->setText(tr(it->second.getProperty("COMMENT").c_str()));
        m_curEditableFilePath = tr(filePath.c_str());
        m_curSelectedRow = row;
        m_editSongWidget->show();
    }
    else {
        QMessageBox::critical(this, tr("uTag"),
        tr("Error opening file"), QMessageBox::Ok | QMessageBox::Cancel);
    }
}
