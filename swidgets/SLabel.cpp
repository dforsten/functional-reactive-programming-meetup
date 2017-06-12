#include "SLabel.h"

using namespace sodium;

SLabel::SLabel(cell<QString> text_in, QWidget * parent, Qt::WindowFlags f) : QLabel(text_in.sample(), parent, f),
text(text_in)
{
    text.listen([this](const QString& s) { this->setText(s); });
}
