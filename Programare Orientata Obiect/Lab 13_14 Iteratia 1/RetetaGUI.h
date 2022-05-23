#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>
#include <qcolor.h>
#include <qspinbox.h>
#include <vector>
#include <string>
#include "Service.h"
#include "Observer.h"

using namespace std;

class RetetaGUI : public QWidget, public Observer
{
private:
	Service& s;
	Reteta& ret;
	Repo& r;

	void update() override
	{
		loadDataMeds(this->s.getMeds(), "#000000");
		loadDataReteta(this->s.getReteta(), "#000000");
	}

	// listele cu produse
	QListWidget* lst1 = new QListWidget;
	QListWidget* lst2 = new QListWidget;

	// pentru generare de medicamente random
	QSpinBox* spinbox = new QSpinBox;

	// butoanele
	QPushButton* butonExit = new QPushButton{ "&Exit" };
	QToolButton* butonAdauga = new QToolButton;
	QPushButton* butonGoleste = new QPushButton{ "&Goleste reteta" };
	QPushButton* butonGenereaza = new QPushButton{ "&Genereaza" };
	QPushButton* butonUndo = new QPushButton{ "&Undo" };
	QPushButton* butonExportHTML = new QPushButton{ "&Export to HTML" };
	QPushButton* butonExportCSV = new QPushButton{ "&Export to CSV" };

	// campurile cu informatia
	QLineEdit* txtDenumire1 = new QLineEdit;
	QLineEdit* txtProducator1 = new QLineEdit;
	QLineEdit* txtPret1 = new QLineEdit;
	QLineEdit* txtSubstantaActiva1 = new QLineEdit;

	QLineEdit* txtDenumire2 = new QLineEdit;
	QLineEdit* txtProducator2 = new QLineEdit;
	QLineEdit* txtPret2 = new QLineEdit;
	QLineEdit* txtSubstantaActiva2 = new QLineEdit;

	// initializeaza interfata grafica
	void initGUI();

	// incarca medicamentele in lista
	void loadDataMeds(const vector<Medicament>& meds, const QColor& color);

	// incarca reteta in lista
	void loadDataReteta(const vector<Medicament>& meds, const QColor& color);

	// stabileste conexiunea dintre semnal si butoane
	void initConnect();

	// coloreaza interfata grafica
	void styleForm();

public:
	RetetaGUI(Service& s, Reteta& ret, Repo& r) :s{ s }, ret{ ret }, r{ r }
	{
		initGUI();
		loadDataMeds(s.getMeds(), "#000000");
		initConnect();
	}
};