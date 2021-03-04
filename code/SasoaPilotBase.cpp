


#include "moc_SasoaPilotBase.cpp"

/****************************************************************************
** Form implementation generated from reading ui file 'SasoaPilotBase.ui'
**
** Created: Thu Jan 24 18:34:58 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "SasoaPilotBase.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qtextedit.h>
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
    SasoaBG1->setGeometry( QRect( 50, 20, 670, 60 ) );

    uninstallButton = new QPushButton( SasoaBG1, "uninstallButton" );
    uninstallButton->setGeometry( QRect( 571, 21, 88, 30 ) );
    uninstallButton->setPaletteBackgroundColor( QColor( 254, 88, 88 ) );

    cleanButton = new QPushButton( SasoaBG1, "cleanButton" );
    cleanButton->setGeometry( QRect( 382, 21, 71, 30 ) );
    cleanButton->setPaletteBackgroundColor( QColor( 170, 255, 255 ) );

    runButton = new QPushButton( SasoaBG1, "runButton" );
    runButton->setGeometry( QRect( 11, 21, 61, 30 ) );
    runButton->setPaletteBackgroundColor( QColor( 255, 170, 127 ) );

    debugButton = new QPushButton( SasoaBG1, "debugButton" );
    debugButton->setGeometry( QRect( 190, 21, 75, 30 ) );
    debugButton->setPaletteBackgroundColor( QColor( 85, 255, 127 ) );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setGeometry( QRect( 50, 130, 658, 70 ) );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );

    quitButton = new QPushButton( this, "quitButton" );
    quitButton->setGeometry( QRect( 650, 260, 75, 30 ) );
    quitButton->setPaletteBackgroundColor( QColor( 142, 161, 255 ) );
    languageChange();
    resize( QSize(778, 316).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( runButton, SIGNAL( clicked() ), this, SLOT( run() ) );
    connect( debugButton, SIGNAL( clicked() ), this, SLOT( debug() ) );
    connect( cleanButton, SIGNAL( clicked() ), this, SLOT( clean() ) );
    connect( uninstallButton, SIGNAL( clicked() ), this, SLOT( uninstall() ) );
    connect( quitButton, SIGNAL( clicked() ), this, SLOT( quitSasoa() ) );
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
    uninstallButton->setText( tr( "Uninstall" ) );
    cleanButton->setText( tr( "Clean" ) );
    runButton->setText( tr( "Run" ) );
    debugButton->setText( tr( "Debug" ) );
    textEdit1->setText( QString::null );
    quitButton->setText( tr( "Quit" ) );
}

void SasoaPilotBase::run()
{
    qWarning( "SasoaPilotBase::run(): Not implemented yet" );
}

void SasoaPilotBase::clean()
{
    qWarning( "SasoaPilotBase::clean(): Not implemented yet" );
}

void SasoaPilotBase::debug()
{
    qWarning( "SasoaPilotBase::debug(): Not implemented yet" );
}

void SasoaPilotBase::uninstall()
{
    qWarning( "SasoaPilotBase::uninstall(): Not implemented yet" );
}

void SasoaPilotBase::quitSasoa()
{
    qWarning( "SasoaPilotBase::quitSasoa(): Not implemented yet" );
}

