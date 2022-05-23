#pragma once
#include <qtabwidget.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qicon.h>
#include <qpixmap.h>
#include <qformlayout.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qslider.h>
#include <qmessagebox.h>
#include <qtableview.h>
#include "Service.h"
#include "TableModel.h"

class MyWidget : public QWidget
{
private:
	Service& s;
public:
	MyWidget(Service& s) :s{ s } {}
	void paintEvent(QPaintEvent* ev) override;
};

class MelodieGUI : public QWidget
{
private:
	Service& s;

	QTableView* table = new QTableView;
	TableModel* model;

	MyWidget* tab;

	// slider
	QSlider* slider = new QSlider;

	// butoanele
	QPushButton* butonModificare = new QPushButton{ "&Update" };
	QPushButton* butonStergere = new QPushButton{ "&Delete" };

	// textfield-ul
	QLineEdit* txtTitlu = new QLineEdit;

	void initGUI();
	void initConnect();
	void loadData(const vector<Melodie>& songs);

public:
	MelodieGUI(Service& s) :s{ s }
	{
		this->tab = new MyWidget{ s };
		this->model = new TableModel{ s.getSongs() };
		this->table->setModel(this->model);
		this->initGUI();
		this->initConnect();
		this->loadData(s.getSongs());
	}
};