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
#include <qpalette.h>
#include <qtoolbutton.h>
#include <qbrush.h>
#include <qcolor.h>
#include <qpixmap.h>
#include <vector>
#include <string>
#include "Service.h"
#include "Repository.h"
#include "RetetaGUI.h"
#include "Observer.h"
#include "CosReadOnlyGUI.h"
#include "RaportGUI.h" 

using namespace std;

class ProductGUI : public QWidget, public Observer
{
private:
	Service& s;
	Reteta& ret;
	FileRepo& r;

	void update() override
	{
		loadData(this->s.getMeds(), "#2e2eb8");
	}

	vector<QPushButton*> butoane;

	// lista cu produse
	QListWidget* lst = new QListWidget;

	// butoanele
	QPushButton* butonExit = new QPushButton{ "&Exit" };
	QPushButton* butonAdauga = new QPushButton{ "&Adauga" };
	QPushButton* butonSterge = new QPushButton{ "&Sterge" };
	QPushButton* butonActualizeaza = new QPushButton{ "&Actualizeaza" };
	QPushButton* butonUndo = new QPushButton{ "&Undo" };
	QPushButton* butonCauta = new QPushButton{ "&Cauta" };
	QPushButton* butonFiltreaza = new QPushButton{ "&Filtreaza" };
	QPushButton* butonSorteazaDenumire = new QPushButton{ "&Sorteaza dupa denumire" };
	QPushButton* butonSorteazaProducator = new QPushButton{ "&Sorteaza dupa producator" };
	QPushButton* butonSorteazaPretSubst = new QPushButton{ "&Sorteaza dupa pret+subst activa" };

	QPushButton* butonReteta = new QPushButton{ "&CosCRUDGUI" };
	QPushButton* butonReadOnly = new QPushButton{ "&CosReadOnlyGUI" };
	QPushButton* butonAdaugaReteta = new QPushButton{ "&Adauga in reteta" };
	QPushButton* butonGolesteReteta = new QPushButton{ "&Goleste reteta" };
	QPushButton* butonGenereaza = new QPushButton{ "&Genereaza" };
	QPushButton* butonDTO = new QPushButton{ "&DTO" };

	// campurile de citire
	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtSubstantaActiva = new QLineEdit;
	QLineEdit* txtGenerare = new QLineEdit;

	QVBoxLayout* lyBtnDyn = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	// initializeaza interfata grafica
	void initGUI();

	// incarca medicamentele in lista
	void loadData(const vector<Medicament>& meds, const QColor& color);

	// stabileste conexiunea dintre semnal si butoane
	void initConnect();

	// coloreaza interfata grafica
	void styleForm();

	// adauga dinamic butoane
	void adaugaButoane(const vector<Medicament>& meds);

public:
	ProductGUI(Service& s, Reteta& ret, FileRepo& r) :s{ s }, ret{ ret }, r{ r }
	{
		initGUI();
		loadData(this->s.getMeds(), "#2e2eb8");
		initConnect();
		adaugaButoane(this->s.getMeds());
	}
};