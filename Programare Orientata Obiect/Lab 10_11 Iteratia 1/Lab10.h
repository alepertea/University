#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10.h"

class Lab10 : public QMainWindow
{
	Q_OBJECT

public:
	Lab10(QWidget *parent = Q_NULLPTR);

private:
	Ui::Lab10Class ui;
};
