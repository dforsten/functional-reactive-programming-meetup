#pragma once

#include <QLabel>
#include <sodium/sodium.h>

namespace sodium
{
    class SLabel : public QLabel
    {
    public:
        explicit SLabel(cell<QString> text_in, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

        cell<QString> text;
    };
}
