#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::openFileOfItem() {
    // const QTableWidgetItem *item = m_filesTable->item(row, 0);
    QMessageBox msgBox;
    msgBox.setText("Interacting with file table");
    msgBox.exec();
    // openFile(item->data(1).toString());
}
