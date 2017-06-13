#pragma once

#include <QPushButton>
#include <sodium/sodium.h>
#include <sodium/unit.h>

namespace sodium
{
    class SButton : public QPushButton
    {
    public:
        explicit SButton(const QString &text, QWidget *parent = Q_NULLPTR);

        stream_sink<unit> clicks;

    public slots:
        void on_clicked();
    };
}
