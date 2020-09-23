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
    void addItemToTable(QString &&qfilePath, QString &&qfileName);
    void addItemToTableHandler(bool isDir, QString absoluteFilePath, QString fileName);
    void createEditSongLayout();

    int row = 0;
    int column = 0;

    QFormLayout *editSongLayout;

    QSplitter* contentVSplitter;
    QWidget* rightTopWidget;
    QWidget* rightBotWidget;
    QWidget* buttonWidget;
    QVBoxLayout* topVLayout;
    QHBoxLayout* butttonLayout;
    QVBoxLayout* botLayout;

    QSplitter* mainSplitter;
    QString m_projectPath;
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
    void save();
    void undo();
    void redo();
    // void cut();
    // void copy();
    // void paste();
    void about();
};
