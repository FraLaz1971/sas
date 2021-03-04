/****************************************************************************
** Form interface generated from reading ui file 'code/sasoapilot.ui'
**
** Created: mar feb 12 16:59:53 2008
**      by: The User Interface Compiler ($Id: sasoapilot.h,v 1.3 2008/02/12 18:32:54 agile_cvs Exp $)
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

class SasoaPilotBase : public QDialog
{
    Q_OBJECT

public:
    SasoaPilotBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SasoaPilotBase();

    QButtonGroup* SasoaBG1;
    QPushButton* runButton;
    QPushButton* debugButton;
    QPushButton* cleanButton;
    QPushButton* uninstallButton;

protected:

protected slots:
    virtual void languageChange();

};

#endif // SASOAPILOTBASE_H
