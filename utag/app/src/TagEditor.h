#pragma once

#include <QtWidgets>
#include <QtCore>

class QPushButton;
class QTextBrowser;

class TagEditor : public QMainWindow
{
    Q_OBJECT

public:
    TagEditor(); //Constructor
    ~TagEditor(); // Destructor

private:
    QFileSystemModel* dirmodel;
    QTreeView* treeView;
    QMenuBar *m_menuBar;

    QLabel *m_filesFoundLabel;
    QTableWidget *m_filesTable;

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    // QAction *undoAct;
    // QAction *redoAct;
    // QAction *cutAct;
    // QAction *copyAct;
    // QAction *pasteAct;
    // QAction *aboutAct;
    // QAction *aboutQtAct;
    QLabel *infoLabel;

private slots:
    void newFile();
    void open();
    void save();
    // void undo();
    // void redo();
    // void cut();
    // void copy();
    // void paste();
    // void about();
    // void aboutQt();
};
