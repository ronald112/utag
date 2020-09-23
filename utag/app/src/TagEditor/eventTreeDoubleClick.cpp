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
    if (isDir && (QMessageBox::question(this, tr("uTag"),
        tr("Do you want try to open this directory?\n")
        + fileName, QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok) == QMessageBox::Ok)) {

        QDirIterator subs(absoluteFilePath,
            QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
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
}

void TagEditor::addItemToTable(QString &&qfilePath, QString &&qfileName) {
    const regex pattern(R"(^.*\.(mp3|flac|waw|ogg)$)");
    cmatch match;

    if (std::regex_match(qfileName.toStdString().c_str(), match, pattern)) {
        AudioFile a(TagLib::FileRef(qfilePath.toStdString().c_str()));
        if(a.isNull()) {
            row = m_filesTable->rowCount();
            m_filesTable->insertRow(row);
            // if (row % 2 == 0) {
            //     m_filesTable->setFrameStyle();
            // }
            QTableWidgetItem *filename = new QTableWidgetItem(tr(a.getProperty("ARTIST").c_str()));
            QTableWidgetItem *TITLE = new QTableWidgetItem(tr(a.getProperty("TITLE").c_str()));
            QTableWidgetItem *ALBUM = new QTableWidgetItem(tr(a.getProperty("ALBUM").c_str()));
            QTableWidgetItem *GENRE = new QTableWidgetItem(tr(a.getProperty("GENRE").c_str()));
            QTableWidgetItem *filePath = new QTableWidgetItem(qfilePath);
            m_filesTable->setItem(row, column++, filename);
            m_filesTable->setItem(row, column++, TITLE);
            m_filesTable->setItem(row, column++, ALBUM);
            m_filesTable->setItem(row, column++, GENRE);
            m_filesTable->setItem(row, column, filePath);
            column = 0;
        }
    }
}
