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

    std::map<const std::string, AudioFile> m_audioFilesMap;

    QString m_curEditableFilePath;
    int m_curSelectedRow = -1;

    QWidget* m_editSongWidget;
    QLineEdit *m_lineEditArtist;
    QLineEdit *m_lineEditTitle;
    QLineEdit *m_lineEditAlbum;
    QLineEdit *m_lineEditGenre;
    QLineEdit *m_lineEditFilePath;
    QLineEdit *m_lineEditComment;
    QLineEdit *m_lineEditYear;
    QLineEdit *m_lineEditTrack;

    QSplitter* m_contentVSplitter;
    QWidget* m_rightTopWidget;
    QWidget* m_rightBotWidget;
    QWidget* m_buttonWidget;
    QVBoxLayout* m_topVLayout;
    QHBoxLayout* m_butttonLayout;
    QVBoxLayout* m_botLayout;

    QSplitter* m_mainSplitter;
    QString m_projectPath;
    QFileSystemModel* m_dirmodel;
    QTreeView* m_treeView;
    QLabel *m_plug;
    QTableWidget *m_filesTable;
    QPushButton* m_saveButton;
    QPushButton* m_undoButton;
    QPushButton* m_redoButton;
    QPushButton* m_aboutButton;
    QPushButton* m_aboutQtButton;
    QPushButton* m_cleanTableButton;
    QPushButton* m_cleanContentButton;
    QLabel* m_imageLabel;

    QLabel *m_infoLabel;

private slots:
    void save();
    void undo();
    void redo();
    void eventOpenFileFromTable(int row);
    void cleanTable();
    void cleanContent();
    void about();
};
