/****************************************************************************
** Form implementation generated from reading ui file 'code/sasoapilot.ui'
**
** Created: Wed Feb 13 11:12:54 2008
**      by: The User Interface Compiler ($Id: sasoapilot.cpp,v 1.2 2008/02/13 12:42:57 agile_cvs Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "sasoapilot.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a SasoaPilotBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SasoaPilotBase::SasoaPilotBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "SasoaPilotBase" );

    SasoaBG1 = new QButtonGroup( this, "SasoaBG1" );
    SasoaBG1->setGeometry( QRect( 30, 30, 106, 290 ) );

    runButton = new QPushButton( SasoaBG1, "runButton" );
    runButton->setGeometry( QRect( 10, 30, 81, 41 ) );
    runButton->setPaletteBackgroundColor( QColor( 255, 170, 127 ) );

    debugButton = new QPushButton( SasoaBG1, "debugButton" );
    debugButton->setGeometry( QRect( 10, 90, 81, 41 ) );
    debugButton->setPaletteBackgroundColor( QColor( 85, 255, 127 ) );

    cleanButton = new QPushButton( SasoaBG1, "cleanButton" );
    cleanButton->setGeometry( QRect( 10, 150, 81, 41 ) );
    cleanButton->setPaletteBackgroundColor( QColor( 170, 255, 255 ) );

    uninstallButton = new QPushButton( SasoaBG1, "uninstallButton" );
    uninstallButton->setGeometry( QRect( 10, 210, 81, 41 ) );
    uninstallButton->setPaletteBackgroundColor( QColor( 254, 88, 88 ) );
    languageChange();
    resize( QSize(176, 366).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
SasoaPilotBase::~SasoaPilotBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SasoaPilotBase::languageChange()
{
    setCaption( tr( "SasoaPilot", "Pilots SuperAGILE Standard Analysis Pipeline" ) );
    SasoaBG1->setTitle( tr( "Selection" ) );
    runButton->setText( tr( "Run" ) );
    debugButton->setText( tr( "Debug" ) );
    cleanButton->setText( tr( "Clean" ) );
    uninstallButton->setText( tr( "Uninstall" ) );
}

