#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::treeDoubleClick() {
    QModelIndex index = treeView->currentIndex();

    if (!index.isValid()) {
        QMessageBox msgBox(QMessageBox::Icon::Question, "Get folder index error", "Get folder index error");
        msgBox.exec();
        return;
    }
    addItemToTableHandler(dirmodel->fileInfo(index).isDir(),
                        dirmodel->fileInfo(index).absoluteFilePath(),
                        dirmodel->fileInfo(index).fileName());
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
        editSongWidget->hide();
        lineEditArtist->clear();
        lineEditTitle->clear();
        lineEditAlbum->clear();
        lineEditGenre->clear();
        lineEditFilePath->clear();
        lineEditYear->clear();
        lineEditTrack->clear();
        lineEditComment->clear();
        infoLabel->show();
        audioFilesMap.clear();
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
        if(a.isNull() && audioFilesMap.count(a.filePath) == 0) {
            int column = 0;

            a.fileName = qfileName.toStdString();
            audioFilesMap.emplace(qfilePath.toStdString(), a);
            m_filesTable->insertRow(m_filesTable->rowCount());
            curEditableFilePath = "";
            curSelectedRow = -1;
            // if (row % 2 == 0) {
            //     m_filesTable->setFrameStyle();
            // }
            QTableWidgetItem *filename = new QTableWidgetItem(tr(a.getProperty("ARTIST").c_str()));
            QTableWidgetItem *TITLE = new QTableWidgetItem(tr(a.getProperty("TITLE").c_str()));
            QTableWidgetItem *ALBUM = new QTableWidgetItem(tr(a.getProperty("ALBUM").c_str()));
            QTableWidgetItem *GENRE = new QTableWidgetItem(tr(a.getProperty("GENRE").c_str()));
            QTableWidgetItem *filePath = new QTableWidgetItem(qfilePath);
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
