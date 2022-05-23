#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include "Observer.h"
#include "TaskGUI.h"
#include "Service.h"

using namespace std;

class InProgressGUI :public QWidget, public Observer
{
private:
	Service& s;
	TaskGUI& gui;

	// lista cu task-urile
	QListWidget* lst = new QListWidget;

	QPushButton* butonOpen = new QPushButton{ "&Open" };
	QPushButton* butonClosed = new QPushButton{ "&Closed" };
	QPushButton* butonInProgress = new QPushButton{ "&In Progress" };

	void update() override
	{
		this->loadData(s.getTasksByState("inprogress"));
	}

	void initGUI();
	void loadData(const vector<Task>& tasks);
	void initConnect();

public:
	InProgressGUI(Service& s, TaskGUI& gui) :s{ s }, gui{ gui }
	{
		this->initGUI();
		this->s.addObserver(this);
		this->loadData(s.getTasksByState("inprogress"));
		this->initConnect();
	}
};