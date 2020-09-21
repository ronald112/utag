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
    void createButtons();
    void createLayouts();
    void createTreeView();
    void createActions();

    QString m_projectPath;
    QWidget* mainWidget;
    QFileSystemModel* dirmodel;
    QTreeView* treeView;
    // QMenuBar *m_menuBar;
    QLabel *m_filesFoundLabel;
    QTableWidget *m_filesTable;
    QPushButton* saveButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* aboutButton;
    QPushButton* aboutQtButton;


    QActionGroup *alignmentGroup;
    QLabel *infoLabel;

private slots:
    void open();
    void save();
    void undo();
    void redo();
    // void cut();
    // void copy();
    // void paste();
    void about();
};
