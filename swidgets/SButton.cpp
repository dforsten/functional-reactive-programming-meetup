#include "SButton.h"

using namespace sodium;

SButton::SButton(const QString & text, QWidget * parent) : QPushButton(text, parent)
{
    connect(this, &QPushButton::clicked, this, &SButton::on_clicked);
}

void SButton::on_clicked()
{
    sClicked.send(unit());
}

