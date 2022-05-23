#include "ProductGUI.h"

void ProductGUI::styleForm()
{
	lst->setStyleSheet("background-color:#f7dfdf");
	this->setStyleSheet("background-color:#f09e9e");

	butonUndo->setStyleSheet("background-color:#ff5e5e");
	butonAdauga->setStyleSheet("background-color:#ff5e5e");
	butonSterge->setStyleSheet("background-color:#ff5e5e");
	butonActualizeaza->setStyleSheet("background-color:#ff5e5e");
	butonCauta->setStyleSheet("background-color:#ff5e5e");
	butonExit->setStyleSheet("background-color:#ff3838");
	butonFiltreaza->setStyleSheet("background-color:#ff5e5e");
	butonSorteazaDenumire->setStyleSheet("background-color:#ff5e5e");
	butonSorteazaProducator->setStyleSheet("background-color:#ff5e5e");
	butonSorteazaPretSubst->setStyleSheet("background-color:#ff5e5e");
	butonReteta->setStyleSheet("background-color:#ff3838");

	txtDenumire->setStyleSheet("background-color:#f7dfdf");
	txtProducator->setStyleSheet("background-color:#f7dfdf");
	txtPret->setStyleSheet("background-color:#f7dfdf");
	txtSubstantaActiva->setStyleSheet("background-color:#f7dfdf");
}

void ProductGUI::initConnect()
{
	QObject::connect(butonExit, &QPushButton::clicked, [&]() { close(); });

	QObject::connect(butonAdauga, &QPushButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();
			auto pret = txtPret->text();
			auto substantaActiva = txtSubstantaActiva->text();

			try
			{
				s.addMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt());
				loadData(s.getMeds(), "#940000");
				adaugaButoane(s.getMeds());
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicamentul deja exista!");
			}
		});

	QObject::connect(butonSterge, &QPushButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();

			try
			{
				s.deleteMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData());
				loadData(s.getMeds(), "#940000");
				adaugaButoane(s.getMeds());
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicamentul nu exista");
			}
		});

	QObject::connect(butonActualizeaza, &QPushButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();
			auto pret = txtPret->text();
			auto substantaActiva = txtSubstantaActiva->text();

			try
			{
				s.modifyMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt(), 3);
				loadData(s.getMeds(), "#940000");
				adaugaButoane(s.getMeds());
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicamentul nu exista");
			}
		});

	QObject::connect(butonUndo, &QPushButton::clicked, [&]()
		{
			try
			{
				s.undo();
				loadData(s.getMeds(), "#940000");
				adaugaButoane(s.getMeds());
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Undo", "Nu se mai poate face undo!");
			}
		});

	QObject::connect(butonCauta, &QPushButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			try
			{
				auto med = s.findMed(denumire.toLocal8Bit().constData());
				QMessageBox::information(nullptr, "Info", "Medicamentul are pretul " + QString::fromStdString(std::to_string(med.getPret())) + " si cantitatea de substanta activa " + QString::fromStdString(std::to_string(med.getSubstantaActiva())));
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Oof!", "Medicamentul cautat nu exista!");
			}
		});

	QObject::connect(butonFiltreaza, &QPushButton::clicked, [&]()
		{
			auto pret = txtPret->text();
			auto substantaActiva = txtSubstantaActiva->text();
			vector<Medicament> meds;
			if (pret != 0 && substantaActiva == 0)
			{
				meds = s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 1);
			}
			if (pret == 0 && substantaActiva != 0)
			{
				meds = s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 2);
			}
			if (pret != 0 && substantaActiva != 0)
			{
				meds = s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 1);
			}
			if (meds.size() == 0)
			{
				if (txtPret->text() == "" && txtSubstantaActiva->text() == "")
					QMessageBox::warning(nullptr, "Atentie", "Va rog completati cu valori in casuta de pret sau de substanta activa");
				else
					QMessageBox::information(nullptr, "Filtrare nereusita", "Nu s-au gasit medicamente care sa satisfaca criteriile!");
			}
			else
			{
				loadData(meds, "#2e4e99");
				adaugaButoane(meds);
			}
		});

	QObject::connect(butonSorteazaDenumire, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = s.sortByDenumire();
			if (meds.size() == 0)
			{
				QMessageBox::information(nullptr, "Sortare nereusita", "Nu s-au gasit medicamente pentru sortare!");
			}
			else
			{
				loadData(meds, "#2e4e99");
				adaugaButoane(meds);
			}
		});

	QObject::connect(butonSorteazaProducator, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = s.sortByProducator();
			if (meds.size() == 0)
			{
				QMessageBox::information(nullptr, "Sortare nereusita", "Nu s-au gasit medicamente pentru sortare!");
			}
			else
			{
				loadData(meds, "#2e4e99");
				adaugaButoane(meds);
			}
		});

	QObject::connect(butonSorteazaPretSubst, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = s.sortBySubstantaSiPret();
			if (meds.size() == 0)
			{
				QMessageBox::information(nullptr, "Sortare nereusita", "Nu s-au gasit medicamente pentru sortare!");
			}
			else
			{
				loadData(meds, "#2e4e99");
				adaugaButoane(meds);
			}
		});

	QObject::connect(butonReteta, &QPushButton::clicked, [&]()
		{
			RetetaGUI* reteta = new RetetaGUI{ s };
			reteta->show();
		});

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = lst->selectedItems();
			if (sel.isEmpty())
			{
				txtDenumire->setText("");
				txtProducator->setText("");
				txtPret->setText("");
				txtSubstantaActiva->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				txtDenumire->setText(denumire);

				auto med = s.findMed(denumire.toStdString());
				txtProducator->setText(QString::fromStdString(med.getProducator()));
				txtPret->setText(QString::number(med.getPret()));
				txtSubstantaActiva->setText(QString::number(med.getSubstantaActiva()));
			}
		});
}

void ProductGUI::loadData(const vector<Medicament>& meds, const QColor& color)
{
	lst->clear();

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogNoButton));
		medicament->setTextColor(color);
		lst->addItem(medicament);
	}
}

void ProductGUI::initGUI()
{
	styleForm();

	this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
	this->setWindowTitle("Medicamenteeeeeeeeeeeeeeeeee");

	QHBoxLayout* mainLy = new QHBoxLayout();
	setLayout(mainLy);

	auto formLy = new QFormLayout;
	formLy->addRow("DENUMIRE:", txtDenumire);
	formLy->addRow("PRODUCATOR:", txtProducator);
	formLy->addRow("PRET:", txtPret);
	formLy->addRow("SUBSTANTA ACTIVA:", txtSubstantaActiva);

	auto lyBtnsGrid = new QGridLayout;
	lyBtnsGrid->addWidget(butonUndo);
	lyBtnsGrid->addWidget(butonExit);

	auto lyBtns = new QHBoxLayout;
	lyBtns->addWidget(butonAdauga);
	lyBtns->addWidget(butonSterge);
	lyBtns->addWidget(butonActualizeaza);
	lyBtns->addWidget(butonCauta);

	auto lyDreapta = new QVBoxLayout;
	lyDreapta->addLayout(formLy);
	lyDreapta->addLayout(lyBtns);
	lyDreapta->addLayout(lyBtnsGrid);

	auto lyBtnsSrv = new QHBoxLayout;
	lyBtnsSrv->addWidget(butonSorteazaDenumire);
	lyBtnsSrv->addWidget(butonSorteazaProducator);
	lyBtnsSrv->addWidget(butonSorteazaPretSubst);
	auto lySrv2 = new QHBoxLayout;
	lySrv2->addWidget(butonFiltreaza);
	lySrv2->addWidget(butonReteta);

	auto lyStanga = new QVBoxLayout;
	lyStanga->addWidget(lst);
	lyStanga->addLayout(lyBtnsSrv);
	lyStanga->addLayout(lySrv2);

	auto layoutInput = new QHBoxLayout;
	layoutInput->addLayout(lyStanga);
	layoutInput->addLayout(lyDreapta);
	layoutInput->addLayout(lyBtnDyn);

	mainLy->addLayout(layoutInput);
}

void ProductGUI::adaugaButoane(const vector<Medicament>& meds)
{
	for (auto buton : butoane)
		delete buton;
	butoane.clear();

	for (auto med : meds)
	{
		auto btn = new QPushButton{ QString::fromStdString(med.getDenumire()) };
		butoane.push_back(btn);
		btn->setStyleSheet("background-color:#ff5e5e");
		//lyBtnDyn->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, btn, med]()
			{
				s.deleteMed(med.getDenumire(), med.getProducator());
				adaugaButoane(s.getMeds());
				loadData(s.getMeds(),"#940000");
			});
		for (auto buton : butoane)
		{
			lyBtnDyn->addWidget(buton);
		}
	}
}