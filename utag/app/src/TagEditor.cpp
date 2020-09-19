#include "TagEditor.h"

TagEditor::TagEditor(QWidget *parent) :
    QWidget(parent)
{
   button_ = new QPushButton(tr("Push Me!"));
   textBrowser_ = new QTextBrowser();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   mainLayout->addWidget(textBrowser_,1,0);
   setLayout(mainLayout);
   setWindowTitle(tr("Connecting buttons to processes.."));
}

TagEditor::~TagEditor() {
    delete(button_);
    delete(textBrowser_);
}