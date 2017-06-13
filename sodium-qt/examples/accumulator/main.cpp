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

    stream<int> plus_delta = plus->clicks.map([](const unit& u) { return 1; });
    stream<int> minus_delta = minus->clicks.map([](const unit& u) { return -1; });
    stream<int> delta = plus_delta.or_else(minus_delta);

    // Circular dependency on declaration, use a "loop" to defer initializing the cell
    cell_loop<int> value;
    stream<int> update = delta.snapshot(value, [](int d, int v) { return d + v; });
    value.loop(update.hold(0));

    SLabel* l1 = new SLabel(value.map([](int i) { return QString::number(i); }));

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
