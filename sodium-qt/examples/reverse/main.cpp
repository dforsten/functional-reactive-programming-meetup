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

    SLineEdit* e1 = new SLineEdit();
    cell<QString> reversed = e1->edit_cell.map([](const QString& s) { return reverse(s); });
    SLabel* l1 = new SLabel(reversed);

    ///////////////////////////////////////////////////////////////////////

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(e1);
    hLayout->addWidget(l1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hLayout);

    QWidget *w = new QWidget();
    w->setLayout(mainLayout);

    ExampleMainWindow mw("simple_hold", w);
    mw.show();
    return app.exec();
}
