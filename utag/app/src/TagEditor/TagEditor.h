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
    void treeDoubleClick();
    void addItemToTable(QString &&qfilePath, QString &&qfileName);
    void addItemToTableHandler(bool isDir, QString absoluteFilePath, QString fileName);
    void createEditSongLayout();
    void cmdLineArgHandler();

    std::map<const std::string, AudioFile> audioFilesMap;

    QString curEditableFilePath;
    int curSelectedRow = -1;

    QWidget* editSongWidget;
    QLineEdit *lineEditArtist;
    QLineEdit *lineEditTitle;
    QLineEdit *lineEditAlbum;
    QLineEdit *lineEditGenre;
    QLineEdit *lineEditFilePath;
    QLineEdit *lineEditComment;
    QLineEdit *lineEditYear;
    QLineEdit *lineEditTrack;

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
    QLabel *m_plug;
    QTableWidget *m_filesTable;
    QPushButton* saveButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* aboutButton;
    QPushButton* aboutQtButton;
    QPushButton* cleanButton;
    QLabel* imageLabel;

    QLabel *infoLabel;

private slots:
    void save();
    void undo();
    void redo();
    void eventOpenFileFromTable(int row);
    void clean();
    // void copy();
    // void paste();
    void about();
};
