/****************************************************************************
** SasoaPilotBase meta object code from reading C++ file 'SasoaPilotBase.h'
**
** Created: Thu Jan 24 18:34:58 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "SasoaPilotBase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SasoaPilotBase::className() const
{
    return "SasoaPilotBase";
}

QMetaObject *SasoaPilotBase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SasoaPilotBase( "SasoaPilotBase", &SasoaPilotBase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SasoaPilotBase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SasoaPilotBase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SasoaPilotBase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SasoaPilotBase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SasoaPilotBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"run", 0, 0 };
    static const QUMethod slot_1 = {"clean", 0, 0 };
    static const QUMethod slot_2 = {"debug", 0, 0 };
    static const QUMethod slot_3 = {"uninstall", 0, 0 };
    static const QUMethod slot_4 = {"quitSasoa", 0, 0 };
    static const QUMethod slot_5 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "run()", &slot_0, QMetaData::Public },
	{ "clean()", &slot_1, QMetaData::Public },
	{ "debug()", &slot_2, QMetaData::Public },
	{ "uninstall()", &slot_3, QMetaData::Public },
	{ "quitSasoa()", &slot_4, QMetaData::Public },
	{ "languageChange()", &slot_5, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"SasoaPilotBase", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SasoaPilotBase.setMetaObject( metaObj );
    return metaObj;
}

void* SasoaPilotBase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SasoaPilotBase" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool SasoaPilotBase::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: run(); break;
    case 1: clean(); break;
    case 2: debug(); break;
    case 3: uninstall(); break;
    case 4: quitSasoa(); break;
    case 5: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SasoaPilotBase::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SasoaPilotBase::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool SasoaPilotBase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
