#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createTreeView() {
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(QDir::homePath());
    treeView = new QTreeView(this);
    treeView->setModel(dirmodel);
    treeView->setRootIndex(dirmodel->index(QDir::homePath()));
    treeView->setExpandsOnDoubleClick(false);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    treeView->setMinimumWidth(350);
    treeView->header()->hideSection(2);
    treeView->setColumnWidth(0, 160);
    treeView->setColumnWidth(1, 80);
    treeView->setAnimated(true);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(treeView, &QTreeView::doubleClicked, this, &TagEditor::treeDoubleClick);

    infoLabel = new QLabel(tr("<i>(nothing to display)</i>"), this);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
}
