/****************************************************************************
** Meta object code from reading C++ file 'p10_chargebyauto_dialog.h'
**
** Created: Wed Dec 31 14:58:02 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "p10_chargebyauto_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'p10_chargebyauto_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_p10_chargebyauto_dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      54,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   24,   24,   24, 0x08,
      91,   24,   24,   24, 0x08,
     107,   24,   24,   24, 0x08,
     121,   24,   24,   24, 0x08,
     136,   24,   24,   24, 0x08,
     152,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_p10_chargebyauto_dialog[] = {
    "p10_chargebyauto_dialog\0\0"
    "signal_enable_p11dlg_timer()\0"
    "signal_exit_p10dlg()\0init_page_dlg()\0"
    "init_page_val()\0start_timer()\0"
    "timer_handle()\0exit_page_dlg()\0"
    "call_p11_dlg()\0"
};

void p10_chargebyauto_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        p10_chargebyauto_dialog *_t = static_cast<p10_chargebyauto_dialog *>(_o);
        switch (_id) {
        case 0: _t->signal_enable_p11dlg_timer(); break;
        case 1: _t->signal_exit_p10dlg(); break;
        case 2: _t->init_page_dlg(); break;
        case 3: _t->init_page_val(); break;
        case 4: _t->start_timer(); break;
        case 5: _t->timer_handle(); break;
        case 6: _t->exit_page_dlg(); break;
        case 7: _t->call_p11_dlg(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData p10_chargebyauto_dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject p10_chargebyauto_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_p10_chargebyauto_dialog,
      qt_meta_data_p10_chargebyauto_dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &p10_chargebyauto_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *p10_chargebyauto_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *p10_chargebyauto_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_p10_chargebyauto_dialog))
        return static_cast<void*>(const_cast< p10_chargebyauto_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int p10_chargebyauto_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void p10_chargebyauto_dialog::signal_enable_p11dlg_timer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void p10_chargebyauto_dialog::signal_exit_p10dlg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
