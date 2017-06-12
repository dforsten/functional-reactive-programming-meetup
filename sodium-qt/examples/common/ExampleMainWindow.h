#pragma once

#include <QMainWindow>

void install_debug_message_handler();

class ExampleMainWindow : public QMainWindow
{
public:
    ExampleMainWindow(const QString& name, QWidget* center_widget);
    ~ExampleMainWindow();

public slots:
    void on_esc();
};
