#include "SLineEdit.h"

using namespace sodium;

SLineEdit::SLineEdit(const QString& initial_value, QWidget * parent) : QLineEdit(initial_value, parent),
    edits(initial_value)
{
    edits = user_changes.hold(initial_value);
    connect(this, &QLineEdit::textEdited, this, &SLineEdit::on_edited);
}

SLineEdit::SLineEdit(stream<QString> stream_in, const QString& initial_value, QWidget * parent) : QLineEdit(initial_value, parent),
    edits(initial_value)
{
    stream_in.listen([this](const QString& new_value) { this->setText(new_value); });
    edits = user_changes.or_else(stream_in).hold(initial_value);

    connect(this, &QLineEdit::textEdited, this, &SLineEdit::on_edited);
}

void SLineEdit::on_edited(const QString& new_value)
{
    user_changes.send(new_value);
}
