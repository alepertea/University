#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab13.h"

class Lab13 : public QMainWindow
{
    Q_OBJECT

public:
    Lab13(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab13Class ui;
};
