#pragma once

#include <QLineEdit>

#include <sodium/sodium.h>

namespace sodium
{
    class SLineEdit : public QLineEdit
    {
    public:
        SLineEdit(const QString& initial_value = QString(), QWidget *parent = Q_NULLPTR);
        SLineEdit(stream<QString> stream_in, const QString& initial_value = QString(), QWidget *parent = Q_NULLPTR);

        /// The Cell representing user edits
        cell<QString> edits;

    public slots:
        void on_edited(const QString& t);

    private:
        stream_sink<QString> user_changes;
    };
}