#include "SLineEdit.h"

using namespace sodium;

SLineEdit::SLineEdit(const QString& s, QWidget * parent) : QLineEdit(s, parent),
    edit_cell(s)
{
    edit_cell = sUserChanges.hold(s);
    connect(this, &QLineEdit::textEdited, this, &SLineEdit::on_edited);
}

SLineEdit::SLineEdit(stream<QString> sText, const QString& s, QWidget * parent) : QLineEdit(s, parent),
    edit_cell(s)
{
    sText.listen([this](const QString& s) { this->setText(s); });
    edit_cell = sUserChanges.or_else(sText).hold(s);

    connect(this, &QLineEdit::textEdited, this, &SLineEdit::on_edited);
}

void SLineEdit::on_edited(const QString& t)
{
    sUserChanges.send(t);
}