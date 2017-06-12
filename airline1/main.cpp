#include <memory>
#include <cassert>
#include <iostream>

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
#include <QKeyEvent>
#include <QShortcut>
#include <QPushButton>
#include <QHBoxLayout>
#include <qlogging.h>

#ifdef _WIN32
#include <Windows.h>
#endif

class MainWindow : public QMainWindow
{

public:
    MainWindow()
    {
        setWindowTitle("Sodium Example: airline1");
        QHBoxLayout *hLayout = new QHBoxLayout;
        QPushButton *b1 = new QPushButton("A");
        QPushButton *b2 = new QPushButton("B");
        QPushButton *b3 = new QPushButton("C");
        hLayout->addWidget(b1);
        hLayout->addWidget(b2);
        hLayout->addWidget(b3);
        
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
