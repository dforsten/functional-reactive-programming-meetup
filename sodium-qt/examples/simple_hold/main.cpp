#include <QApplication>
#include <QHBoxLayout>

#include "ExampleMainWindow.h"

#include "SLabel.h"
#include "SButton.h"

using namespace sodium;
using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    install_debug_message_handler();

    ///////////////////////////////////////////////////////////////////////
    // Sodium Setup

    SButton *b1 = new SButton("A");
    cell<QString> mapped_button = b1->clicks.map([](const unit& u) { return QString("Test"); }).hold("A");
    SLabel* l1 = new SLabel(mapped_button);

    ///////////////////////////////////////////////////////////////////////

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(b1);
    hLayout->addWidget(l1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hLayout);

    QWidget *w = new QWidget();
    w->setLayout(mainLayout);

    ExampleMainWindow mw("simple_hold", w);
    mw.show();
    return app.exec();
}
