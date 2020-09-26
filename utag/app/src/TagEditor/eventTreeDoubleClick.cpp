#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::treeDoubleClick() {
    QModelIndex index = m_treeView->currentIndex();

    if (!index.isValid()) {
        QMessageBox msgBox(QMessageBox::Icon::Question, "Get folder index error", "Get folder index error");
        msgBox.exec();
        return;
    }
    addItemToTableHandler(m_dirmodel->fileInfo(index).isDir(),
                        m_dirmodel->fileInfo(index).absoluteFilePath(),
                        m_dirmodel->fileInfo(index).fileName());
}

void TagEditor::addItemToTableHandler(bool isDir, QString absoluteFilePath, QString fileName) {
    if (QFileInfo(QDir::homePath()).owner() != QFileInfo(absoluteFilePath).owner()) {
        QMessageBox::warning(this, tr("uTag"),
            tr("You  have no rights to open this folder:\n")
            + fileName, QMessageBox::Ok);
        return;
    }

    m_filesTable->setSortingEnabled(false);
    if (isDir && (QMessageBox::question(this, tr("uTag"),
        tr("Do you want try to open this directory?\n")
        + fileName, QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok) == QMessageBox::Ok)) {
        QDirIterator subs(absoluteFilePath,
            QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
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
        m_audioFilesMap.clear();
        m_filesTable->clearContents();
        m_filesTable->setRowCount(0);
        while(subs.hasNext())
        {
            addItemToTable(subs.filePath(), subs.fileName());
            subs.next();
        }
        addItemToTable(subs.filePath(), subs.fileName());
    }
    else {
        addItemToTable(std::move(absoluteFilePath), std::move(fileName));
    }
    m_filesTable->setSortingEnabled(true);
}

void TagEditor::addItemToTable(QString &&qfilePath, QString &&qfileName) {
    const regex pattern(R"(^.+.(mp3|ogg|oga|mogg|flac|mpc|wav|mp4|asf|tta|aiff|spx|wv)$)");
    cmatch match;

    if (std::regex_match(qfileName.toStdString().c_str(), match, pattern)) {
        AudioFile a(TagLib::FileRef(qfilePath.toStdString().c_str()), qfilePath.toStdString());
        if(a.isNull() && m_audioFilesMap.count(a.filePath) == 0) {
            int column = 0;

            a.fileName = qfileName.toStdString();
            m_audioFilesMap.emplace(qfilePath.toStdString(), a);
            m_filesTable->insertRow(m_filesTable->rowCount());
            m_curEditableFilePath = "";
            m_curSelectedRow = -1;
            QTableWidgetItem *filename = new QTableWidgetItem(tr(a.getProperty("ARTIST").c_str()));
            QTableWidgetItem *TITLE = new QTableWidgetItem(tr(a.getProperty("TITLE").c_str()));
            QTableWidgetItem *ALBUM = new QTableWidgetItem(tr(a.getProperty("ALBUM").c_str()));
            QTableWidgetItem *GENRE = new QTableWidgetItem(tr(a.getProperty("GENRE").c_str()));
            QTableWidgetItem *filePath = new QTableWidgetItem(qfilePath);
            // if (m_filesTable->rowCount() % 2 == 0) {
            //     filename->setBackground(QColor(211,211,211, 127));
            //     TITLE->setBackground(QColor(211,211,211, 127));
            //     ALBUM->setBackground(QColor(211,211,211, 127));
            //     GENRE->setBackground(QColor(211,211,211, 127));
            //     filePath->setBackground(QColor(211,211,211, 127));
            // }
            m_filesTable->setItem(m_filesTable->rowCount() - 1, column++, filename);
            m_filesTable->setItem(m_filesTable->rowCount() - 1, column++, TITLE);
            m_filesTable->setItem(m_filesTable->rowCount() - 1, column++, ALBUM);
            m_filesTable->setItem(m_filesTable->rowCount() - 1, column++, GENRE);
            m_filesTable->setItem(m_filesTable->rowCount() - 1, column, filePath);
        }
        else {
            QMessageBox::warning(this, tr("uTag"),
            tr("File ") + qfileName + tr(" already added or doesn't exist"), QMessageBox::Ok);
        }
    }
}
