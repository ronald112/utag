#pragma once

// #include <QtCore/QCoreApplication>
// #include <QApplication>
// #include <QtWidgets/QMainWindow>
// #include <QtCore/QObject>
#include <QtWidgets>
#include <QtCore>
// #include <QAction>
// #include <QTextEdit>
// #include <QPushButton>
// #include <QTextBrowser>
// #include <QGridLayout>

class QPushButton;
class QTextBrowser;

class TagEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TagEditor(QWidget *parent = 0); //Constructor
    ~TagEditor(); // Destructor

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
};
