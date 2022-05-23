#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QCheckBox>
#include <qtabwidget.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <vector>
#include <string>
#include "Service.h"

using namespace std;

class ProductGUI : public QWidget
{
private:
	Service& s;

	// lista cu produse
	QListWidget* lst = new QListWidget;

	QRadioButton* radioAdd = new QRadioButton("Adauga", nullptr);
	QRadioButton* radioSterge = new QRadioButton("Sterge", nullptr);
	QRadioButton* radioActualizeaza = new QRadioButton("Actualizeaza", nullptr);
	QRadioButton* radioUndo = new QRadioButton("Undo", nullptr);
	QRadioButton* radioCauta = new QRadioButton("Cauta", nullptr);
	QRadioButton* radioExit = new QRadioButton("Exit", nullptr);

	// butoanele
	QPushButton* butonExit = new QPushButton{ "&Exit" };
	QPushButton* butonAdauga = new QPushButton{ "&Adauga" };
	QPushButton* butonSterge = new QPushButton{ "&Sterge" };
	QPushButton* butonActualizeaza = new QPushButton{ "&Actualizeaza" };
	QPushButton* butonUndo = new QPushButton{ "&Undo" };
	QPushButton* butonCauta = new QPushButton{ "&Cauta" };
	
	// campurile de citire
	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtSubstantaActiva = new QLineEdit;

	void initGUI();
	void loadData();
	void initConnect();

public:
	ProductGUI(Service& s) :s{ s }
	{
		// initializare interfata grafica
		initGUI();

		// incarcare lista de medicamente
		loadData();

		// actiuni butoane
		initConnect();
	}
};