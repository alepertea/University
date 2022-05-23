#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qapplication.h>
#include "Observer.h"
#include "Repository.h"

class CosReadOnlyGUI : public QWidget, public Observer
{
private:
	Reteta& ret;
public:
	CosReadOnlyGUI(Reteta& ret) : ret{ ret }
	{
		ret.addObserver(this);
		this->setStyleSheet("background-image: url(fundalretetaGUI.jpg)");
		this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
		this->setWindowTitle("CosReadOnlyGUI");
	}

	void update() override;
	void paintEvent(QPaintEvent* ev) override;
};