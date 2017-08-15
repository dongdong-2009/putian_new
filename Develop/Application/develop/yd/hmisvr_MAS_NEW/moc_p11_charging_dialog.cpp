/****************************************************************************
** Meta object code from reading C++ file 'p11_charging_dialog.h'
**
** Created: Wed Dec 31 14:58:02 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "p11_charging_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'p11_charging_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_p11_charging_dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      50,   20,   20,   20, 0x05,
      78,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      99,   20,   20,   20, 0x08,
     115,   20,   20,   20, 0x08,
     131,   20,   20,   20, 0x08,
     145,   20,   20,   20, 0x08,
     160,   20,   20,   20, 0x08,
     176,   20,   20,   20, 0x08,
     189,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_p11_charging_dialog[] = {
    "p11_charging_dialog\0\0signal_enable_p12dlg_timer()\0"
    "signal_enable_dlg_2_timer()\0"
    "signal_exit_p11dlg()\0init_page_dlg()\0"
    "init_page_val()\0start_timer()\0"
    "timer_handle()\0exit_page_dlg()\0"
    "call_dlg_2()\0call_p12_dlg()\0"
};

void p11_charging_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        p11_charging_dialog *_t = static_cast<p11_charging_dialog *>(_o);
        switch (_id) {
        case 0: _t->signal_enable_p12dlg_timer(); break;
        case 1: _t->signal_enable_dlg_2_timer(); break;
        case 2: _t->signal_exit_p11dlg(); break;
        case 3: _t->init_page_dlg(); break;
        case 4: _t->init_page_val(); break;
        case 5: _t->start_timer(); break;
        case 6: _t->timer_handle(); break;
        case 7: _t->exit_page_dlg(); break;
        case 8: _t->call_dlg_2(); break;
        case 9: _t->call_p12_dlg(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData p11_charging_dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject p11_charging_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_p11_charging_dialog,
      qt_meta_data_p11_charging_dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &p11_charging_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *p11_charging_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *p11_charging_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_p11_charging_dialog))
        return static_cast<void*>(const_cast< p11_charging_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int p11_charging_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void p11_charging_dialog::signal_enable_p12dlg_timer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void p11_charging_dialog::signal_enable_dlg_2_timer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void p11_charging_dialog::signal_exit_p11dlg()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
