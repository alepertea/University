#pragma once
#include <QtWidgets/QApplication>
#include <qwidget.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qstyle.h>
#include <string>
#include "Service.h"
#include "Observer.h"

using namespace std;

class RaportGUI : public QWidget, public Observer
{
private:
	Service& s;

	QListWidget* lst = new QListWidget;
	void initGUI();
	void loadData(const vector<DTO> dto);
	void update() override;

public:
	RaportGUI(Service& s) : s{ s } 
	{
		this->initGUI();
		this->loadData(this->s.makeDTOVector());
	}
};