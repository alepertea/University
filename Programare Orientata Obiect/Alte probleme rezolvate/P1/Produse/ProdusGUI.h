#pragma once
#include <map>
#include <qwidget.h>
#include <qtableview.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qboxlayout.h>
#include <qicon.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qslider.h>
#include "TableModel.h"
#include "Service.h"
#include "TipGUI.h"

class ProdusGUI : public QWidget
{
private:
	Service& s;

	QTableView* table = new QTableView;
	TableModel* model;

	QSlider* slider = new QSlider;

	// butoane
	QPushButton* butonAdaugare = new QPushButton{ "&Adauga" };
	QPushButton* butonExit = new QPushButton{ "&Exit" };

	// textfield-uri
	QLineEdit* txtID = new QLineEdit;
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;

	void initGUI();
	void initConnect();
	void loadData(const vector<Produs>& prod);

public:
	ProdusGUI(Service& s) :s{ s }
	{
		this->model = new TableModel{ s.sortByPrice() };
		this->table->setModel(this->model);
		this->initGUI();
		this->initConnect();
		this->loadData(s.sortByPrice());
	}
};