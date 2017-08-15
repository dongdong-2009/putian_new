/****************************************************************************
** Meta object code from reading C++ file 'p21_leftmoney_dialog.h'
**
** Created: Sat Jan 3 11:22:40 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "p21_leftmoney_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'p21_leftmoney_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_p21_leftmoney_dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   21,   21,   21, 0x08,
      59,   21,   21,   21, 0x08,
      75,   21,   21,   21, 0x08,
      89,   21,   21,   21, 0x08,
     104,   21,   21,   21, 0x08,
     120,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_p21_leftmoney_dialog[] = {
    "p21_leftmoney_dialog\0\0signal_exit_p21dlg()\0"
    "init_page_dlg()\0init_page_val()\0"
    "start_timer()\0timer_handle()\0"
    "exit_page_dlg()\0on_pbtn_cancel_clicked()\0"
};

void p21_leftmoney_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        p21_leftmoney_dialog *_t = static_cast<p21_leftmoney_dialog *>(_o);
        switch (_id) {
        case 0: _t->signal_exit_p21dlg(); break;
        case 1: _t->init_page_dlg(); break;
        case 2: _t->init_page_val(); break;
        case 3: _t->start_timer(); break;
        case 4: _t->timer_handle(); break;
        case 5: _t->exit_page_dlg(); break;
        case 6: _t->on_pbtn_cancel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData p21_leftmoney_dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject p21_leftmoney_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_p21_leftmoney_dialog,
      qt_meta_data_p21_leftmoney_dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &p21_leftmoney_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *p21_leftmoney_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *p21_leftmoney_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_p21_leftmoney_dialog))
        return static_cast<void*>(const_cast< p21_leftmoney_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int p21_leftmoney_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void p21_leftmoney_dialog::signal_exit_p21dlg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
