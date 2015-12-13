#include "window.h"
#include "ui_window.h"
#include "myhelper.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    MyHelper::FormInCenter(this);
    this->Init();
}

Window::~Window()
{
    delete ui;
}
