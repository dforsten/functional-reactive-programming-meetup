#include "ExampleMainWindow.h"
#include <QSettings>
#include <QShortcut>
#include <qlogging.h>

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext& ctx, const QString& str)
{
    std::cout << str.toLatin1().constData();
#ifdef _WIN32
    OutputDebugStringA(str.toLatin1().constData());
#endif
}

void install_debug_message_handler()
{
    qInstallMessageHandler(debugMessageDisplayFunc);
}

ExampleMainWindow::ExampleMainWindow(const QString& name, QWidget* center_widget)
{
    setWindowTitle("Sodium Qt Example: " + name);

    setCentralWidget(center_widget);

    QSettings settings("davidf", "airline1");
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("state", saveState()).toByteArray());
    settings.endGroup();

    QShortcut* quit_shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    quit_shortcut->setContext(Qt::ApplicationShortcut);
    connect(quit_shortcut, &QShortcut::activated, this, &ExampleMainWindow::on_esc);
}

ExampleMainWindow::~ExampleMainWindow()
{
    QSettings settings("davidf", "airline1");
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
}

void ExampleMainWindow::on_esc()
{
    close();
}
