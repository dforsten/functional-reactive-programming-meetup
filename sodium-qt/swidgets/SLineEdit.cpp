#include "SLineEdit.h"

using namespace sodium;

SLineEdit::SLineEdit(const QString& s, QWidget * parent) : QLineEdit(s, parent),
    edit_cell(s)
{
    connect(this, &QLineEdit::textEdited, this, &SLineEdit::on_edited);
}

void SLineEdit::on_edited(const QString& t)
{
    edit_cell.send(t);
}