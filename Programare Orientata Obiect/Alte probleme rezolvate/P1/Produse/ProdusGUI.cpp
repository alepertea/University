#include "ProdusGUI.h"

void ProdusGUI::initGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QPixmap pixmap("flower.png");
	QIcon icon(pixmap);
	this->setWindowIcon(icon);
	this->setStyleSheet("background-image: url(fundal.jpg)");

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("ID PRODUS:", this->txtID);
	formLayout->addRow("NUME PRODUS:", this->txtNume);
	formLayout->addRow("TIP PRODUS:", this->txtTip);
	formLayout->addRow("PRET PRODUS:", this->txtPret);

	QVBoxLayout* layoutStanga = new QVBoxLayout;
	QVBoxLayout* layoutDreapta = new QVBoxLayout;

	layoutDreapta->addLayout(formLayout);
	layoutDreapta->addWidget(this->butonAdaugare);
	layoutDreapta->addWidget(this->butonExit);

	mainLayout->addLayout(layoutStanga);
	mainLayout->addLayout(layoutDreapta);

	this->slider->setRange(1, 100);
	this->slider->setOrientation(Qt::Horizontal);

	layoutStanga->addWidget(this->table);
	layoutStanga->addWidget(this->slider);

	mainLayout->addLayout(layoutStanga);
	mainLayout->addLayout(layoutDreapta);

	map<string, int> tipuri;
	for (const auto& d : this->s.getProducts())
		tipuri[d.getTip()]++;
	for (auto d : tipuri)
	{
		TipGUI* gui = new TipGUI{ this->s, d.first, this->s.getNumberOfProducts(d.first) };
		this->s.addObserver(gui);
		gui->show();
	}
}

void ProdusGUI::initConnect()
{
	QObject::connect(this->butonExit, &QPushButton::clicked, [&]()
		{
			this->close();
		});

	QObject::connect(this->butonAdaugare, &QPushButton::clicked, [&]()
		{
			int id = this->txtID->text().toInt();
			string nume = this->txtNume->text().toStdString();
			string tip = this->txtTip->text().toStdString();
			double pret = this->txtPret->text().toDouble();

			int errorCode = this->s.addProduct(id, nume, tip, pret);
			this->loadData(this->s.sortByPrice());
			this->model->refresh();

			if (this->s.getNumberOfProducts(tip) == 1)
			{
				TipGUI* gui = new TipGUI{ this->s, tip, 1 };
				this->s.addObserver(gui);
				gui->show();
			}

			if (errorCode == 1)
			{
				QMessageBox::warning(nullptr, "ID existent", "ID existent!");
			}
			if (errorCode == 2)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Nume invalid!");
			}
			if (errorCode == 3)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Pret invalid!");
			}
			if (errorCode == 6)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Nume invalid!\n Pret invalid!");
			}
		});

	QObject::connect(this->slider, &QSlider::valueChanged, [&]()
		{
			/*
			double value = this->slider->value();
			vector<Produs> rez = this->s.filterProducts(value);
			this->loadData(rez);
			this->model->refresh();
			if (this->slider->value() == 50)
				this->model->setValoareSlider(50);
			else
				this->model->setValoareSlider(0);
				*/
			double value = this->slider->value();
			this->model->setValoareSlider(value);
			this->loadData(this->s.sortByPrice());
			this->model->refresh();
		});
}

void ProdusGUI::loadData(const vector<Produs>& prod)
{
	this->model->setProducts(prod);
}