#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qtableview.h>
#include "TableModel.h"
#include "Service.h"

class JocGUI : public QWidget
{
private:
	Service& s;
	QTableView* tabel = new QTableView;
	TableModel* model;

	vector<QPushButton*> butoane;

	// layout-uri
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* layoutSus = new QHBoxLayout;
	QVBoxLayout* layoutJos = new QVBoxLayout;

	// butoane
	QPushButton* butonAdaugare = new QPushButton{ "&Adauga" };
	QPushButton* butonModificare = new QPushButton{ "&Modifica" };

	// textfield-uri
	QLineEdit* txtDim = new QLineEdit;
	QLineEdit* txtTabla = new QLineEdit;
	QLineEdit* txtJucator = new QLineEdit;

	QLineEdit* txtID = new QLineEdit;
	QLineEdit* txtDimensiune = new QLineEdit;
	QLineEdit* txtTablaJoc = new QLineEdit;
	QLineEdit* txtJucatorCurent = new QLineEdit;
	QLineEdit* txtStare = new QLineEdit;

	QVBoxLayout* creareTabla(const int& dim,const string& tabla);

	void initGUI();
	void initConnect();
	void loadData(const vector<Joc>& jocuri);

public:
	JocGUI(Service& s) :s{ s }
	{
		this->model = new TableModel{ s.getAll() };
		this->tabel->setModel(this->model);
		this->initGUI();
		this->initConnect();
		this->loadData(s.getAll());
	}
};