/****************************************************************************
** Form interface generated from reading ui file 'SasoaPilotBase.ui'
**
** Created: Thu Jan 24 18:34:58 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SASOAPILOTBASE_H
#define SASOAPILOTBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QPushButton;
class QTextEdit;

class SasoaPilotBase : public QDialog
{
    Q_OBJECT

public:
    SasoaPilotBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SasoaPilotBase();

    QButtonGroup* SasoaBG1;
    QPushButton* uninstallButton;
    QPushButton* cleanButton;
    QPushButton* runButton;
    QPushButton* debugButton;
    QTextEdit* textEdit1;
    QPushButton* quitButton;

public slots:
    virtual void run();
    virtual void clean();
    virtual void debug();
    virtual void uninstall();
    virtual void quitSasoa();

protected:

protected slots:
    virtual void languageChange();

};

#endif // SASOAPILOTBASE_H
