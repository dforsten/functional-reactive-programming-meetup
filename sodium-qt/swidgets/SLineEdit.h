#pragma once

#include <QLineEdit>

#include <sodium/sodium.h>

namespace sodium
{
    class SLineEdit : public QLineEdit
    {
    public:
        SLineEdit(const QString& s = QString(), QWidget *parent = Q_NULLPTR);

        cell_sink<QString> edit_cell;

    public slots:
        void on_edited(const QString& t);
    };
}