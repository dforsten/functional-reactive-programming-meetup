#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>

#include "ExampleMainWindow.h"

#include "SLabel.h"
#include "SButton.h"
#include "SLineEdit.h"

using namespace sodium;
using namespace std;

QString reverse(const QString& s)
{
    QString out;
    for (auto c = s.rbegin(); c != s.rend(); ++c)
        out += *c;
    return out;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    install_debug_message_handler();

    ///////////////////////////////////////////////////////////////////////
    // Sodium Setup

    SButton* plus = new SButton("+");
    SButton* minus = new SButton("-");

    stream<int> plus_delta = plus->sClicked.map([](const unit& u) { return 1; });
    stream<int> minus_delta = minus->sClicked.map([](const unit& u) { return -1; });
    stream<int> delta = plus_delta.or_else(minus_delta);

    // SLineEdit takes an optional stream of strings to update its value programmatically
    // In this case the stream is dependent on the stream defined subsequently, so we use
    // a stream_loop.
    stream_loop<int> set_value;
    SLineEdit* l1 = new SLineEdit(set_value.map([](int i) { return QString::number(i); }), "0");

    // We convert the SLineEdit string to an integer
    cell<int> value = l1->edit_cell.map([](const QString& s) { return s.toInt(); });

    // And add the delta to it in case of a + or - event
    stream<int> update = delta.snapshot(value, [](int d, int v) { return d + v; });

    // And initialize the stream provided to SLineEdit with that new value
    set_value.loop(update);

    ///////////////////////////////////////////////////////////////////////

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(l1);
    hLayout->addWidget(plus);
    hLayout->addWidget(minus);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hLayout);

    QWidget *w = new QWidget();
    w->setLayout(mainLayout);

    ExampleMainWindow mw("simple_hold", w);
    mw.show();
    return app.exec();
}
