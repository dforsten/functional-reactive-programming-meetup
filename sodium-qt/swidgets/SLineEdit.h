#pragma once

#include <QLineEdit>

#include <sodium/sodium.h>

namespace sodium
{
    class SLineEdit : public QLineEdit
    {
    public:
        SLineEdit(const QString& s = QString(), QWidget *parent = Q_NULLPTR);
        SLineEdit(stream<QString> sText, const QString& s = QString(), QWidget *parent = Q_NULLPTR);

        cell<QString> edit_cell;

        stream_sink<QString> sUserChanges;

    public slots:
        void on_edited(const QString& t);
    };
}