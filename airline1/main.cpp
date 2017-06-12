#include <memory>
#include <cassert>
#include <iostream>

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
#include <QKeyEvent>
#include <QShortcut>
#include <QHBoxLayout>
#include <qlogging.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "SLabel.h"
#include "SButton.h"

using namespace sodium;
using namespace std;

class MainWindow : public QMainWindow
{

public:
    MainWindow()
    {
        setWindowTitle("Sodium Example: airline1");

        ///////////////////////////////////////////////////////////////////////
        // Sodium Setup

        SButton *b1 = new SButton("A");
        cell<QString> mapped_button = b1->sClicked.map([](const unit& u) { return QString("Test"); }).hold("A");
        SLabel* l1 = new SLabel(mapped_button);

        ///////////////////////////////////////////////////////////////////////

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(b1);
        hLayout->addWidget(l1);
        
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(hLayout);
        
        QWidget *w = new QWidget();
        w->setLayout(mainLayout);
        setCentralWidget(w);

        QSettings settings("davidf", "airline1");
        settings.beginGroup("MainWindow");
        restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
        restoreState(settings.value("state", saveState()).toByteArray());
        settings.endGroup();

		QShortcut* quit_shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
		quit_shortcut->setContext(Qt::ApplicationShortcut);
		connect(quit_shortcut, &QShortcut::activated, this, &MainWindow::on_esc);
    }

    ~MainWindow()
    {
        QSettings settings("davidf", "airline1");
        settings.beginGroup("MainWindow");
        settings.setValue("geometry", saveGeometry());
        settings.setValue("state", saveState());
        settings.endGroup();        
    }

	public slots:
	void on_esc()
	{
		close();
	}
};

void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext& ctx, const QString& str)
{
    std::cout << str.toLatin1().constData();
#ifdef _WIN32
    OutputDebugStringA(str.toLatin1().constData());
#endif

}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qInstallMessageHandler(debugMessageDisplayFunc);

    MainWindow mw;
    mw.show();
    return app.exec();
}
