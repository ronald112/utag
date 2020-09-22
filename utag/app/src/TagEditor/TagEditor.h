#pragma once

#include <QtWidgets>
#include <QtCore>
#include <AudioFile/AudioFile.h>

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
    void openFileOfItem();
    void treeDoubleClick();
    void addItemToTable(QString &&filePath, QString &&fileName);

    int row = 0;
    int column = 0;

    QString m_projectPath;
    QWidget* mainWidget;
    QFileSystemModel* dirmodel;
    QTreeView* treeView;
    QLabel *m_filesFoundLabel;
    QTableWidget *m_filesTable;
    QPushButton* saveButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* aboutButton;
    QPushButton* aboutQtButton;

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
