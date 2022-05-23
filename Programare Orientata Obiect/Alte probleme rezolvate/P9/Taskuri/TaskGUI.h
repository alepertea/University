#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include <qlistwidget.h>
#include <qicon.h>
#include <qpixmap.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qtableview.h>
#include "Service.h"
#include "TableModel.h"

class TaskGUI :public QWidget
{
private:
	Service& s;

	// tabelul cu task-urile
	QTableView* table = new QTableView;
	TableModel* model;

	// campurile de text
	QLineEdit* txtID = new QLineEdit;
	QLineEdit* txtDescriere = new QLineEdit;
	QLineEdit* txtProgramator = new QLineEdit;
	QLineEdit* txtStare = new QLineEdit;
	QLineEdit* txtCautare = new QLineEdit;

	// butoane
	QPushButton* butonAdaugare = new QPushButton{ "&Adauga" };
	QPushButton* butonExit = new QPushButton{ "&Exit" };

	// initializeaza interfata grafica
	void initGUI();

	// face legatura dintre butoane si semnale
	void initConnect();

	// incarca task-urile in tabel
	void loadData(vector<Task> tasks);

public:
	TaskGUI(Service& s) :s{ s }
	{
		this->initGUI();
		this->model = new TableModel{ s.sortByState() };
		this->table->setModel(model);
		this->initConnect();
		this->loadData(s.sortByState());
	}

	void reloadDataAfterModification()
	{
		this->loadData(this->s.sortByState());
	}
};