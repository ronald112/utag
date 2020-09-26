#include "TagEditor.h"
#include <MiscHeaders.h>

void TagEditor::createTreeView() {
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setRootPath(QDir::homePath());

    QStringList filters;
    filters << "*.mp3" << "*.ogg" << "*.oga" << "*.mogg" << "*.flac"
        << "*.mpc" << "*.wav" << "*.mp4" << "*.asf" << "*.tta" << "*.aiff"
        << "*.spx" << "*.wv";
    m_dirmodel->setNameFilters(filters);
    m_dirmodel->setNameFilterDisables(false);

    m_treeView = new QTreeView(this);
    m_treeView->setModel(m_dirmodel);
    m_treeView->setRootIndex(m_dirmodel->index(QDir::homePath()));
    m_treeView->setExpandsOnDoubleClick(false);
    m_treeView->setMinimumWidth(250);
    m_treeView->header()->hideSection(2);
    m_treeView->setColumnWidth(0, 160);
    m_treeView->setColumnWidth(1, 80);
    m_treeView->setAnimated(true);
    m_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_treeView, &QTreeView::doubleClicked, this, &TagEditor::treeDoubleClick);

    m_infoLabel = new QLabel(tr("<i>(nothing to display)</i>"), this);
    m_infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    m_infoLabel->setAlignment(Qt::AlignCenter);
}
