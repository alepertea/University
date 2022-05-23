#include "ProductGUI.h"

void ProductGUI::styleForm()
{
	//this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
	QPixmap pixmap("pill.png");
	QIcon icon(pixmap);
	this->setWindowIcon(icon);
	this->setWindowTitle("Medicamenteeeeeeeeeeeeeeeeee");
	this->setStyleSheet("background-image: url(fundalProductGUI.jpg)");
}

void ProductGUI::initConnect()
{
	QObject::connect(this->butonExit, &QPushButton::clicked, [&]() { close(); });

	QObject::connect(this->butonAdauga, &QPushButton::clicked, [&]()
		{
			auto denumire = this->txtDenumire->text();
			auto producator = this->txtProducator->text();
			auto pret = this->txtPret->text();
			auto substantaActiva = this->txtSubstantaActiva->text();

			try
			{
				this->s.addMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt());
				loadData(this->s.getMeds(), "#2e2eb8");
				adaugaButoane(this->s.getMeds());
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

	QObject::connect(this->butonSterge, &QPushButton::clicked, [&]()
		{
			auto denumire = this->txtDenumire->text();
			auto producator = this->txtProducator->text();

			try
			{
				this->s.deleteMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData());
				loadData(this->s.getMeds(), "#2e2eb8");
				adaugaButoane(this->s.getMeds());
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

	QObject::connect(this->butonActualizeaza, &QPushButton::clicked, [&]()
		{
			auto denumire = this->txtDenumire->text();
			auto producator = this->txtProducator->text();
			auto pret = this->txtPret->text();
			auto substantaActiva = this->txtSubstantaActiva->text();

			try
			{
				this->s.modifyMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt(), 3);
				loadData(this->s.getMeds(), "#2e2eb8");
				adaugaButoane(this->s.getMeds());
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

	QObject::connect(this->butonUndo, &QPushButton::clicked, [&]()
		{
			try
			{
				this->s.undo();
				loadData(this->s.getMeds(), "#2e2eb8");
				adaugaButoane(this->s.getMeds());
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Undo", "Nu se mai poate face undo!");
			}
		});

	QObject::connect(this->butonCauta, &QPushButton::clicked, [&]()
		{
			auto denumire = this->txtDenumire->text();
			try
			{
				auto med = this->s.findMed(denumire.toLocal8Bit().constData());
				QMessageBox::information(nullptr, "Info", "Medicamentul are pretul " + QString::fromStdString(std::to_string(med.getPret())) + " si cantitatea de substanta activa " + QString::fromStdString(std::to_string(med.getSubstantaActiva())));
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Oof!", "Medicamentul cautat nu exista!");
			}
		});

	QObject::connect(this->butonFiltreaza, &QPushButton::clicked, [&]()
		{
			auto pret = this->txtPret->text();
			auto substantaActiva = this->txtSubstantaActiva->text();
			vector<Medicament> meds;
			if (pret != 0 && substantaActiva == 0)
			{
				meds = this->s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 1);
			}
			if (pret == 0 && substantaActiva != 0)
			{
				meds = this->s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 2);
			}
			if (pret != 0 && substantaActiva != 0)
			{
				meds = this->s.filterMeds(pret.toDouble(), substantaActiva.toInt(), 1);
			}
			if (meds.size() == 0)
			{
				if (this->txtPret->text() == "" && this->txtSubstantaActiva->text() == "")
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

	QObject::connect(this->butonSorteazaDenumire, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = this->s.sortByDenumire();
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

	QObject::connect(this->butonSorteazaProducator, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = this->s.sortByProducator();
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

	QObject::connect(this->butonSorteazaPretSubst, &QPushButton::clicked, [&]()
		{
			vector<Medicament> meds = this->s.sortBySubstantaSiPret();
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

	// RETETA

	QObject::connect(this->butonReteta, &QPushButton::clicked, [&]()
		{
			RetetaGUI* reteta = new RetetaGUI{ this->s, this->ret, this->r };
			reteta->show();
		});

	QObject::connect(this->butonReadOnly, &QPushButton::clicked, [&]()
		{
			CosReadOnlyGUI* cosReadOnly = new CosReadOnlyGUI{ this->ret };
			cosReadOnly->show();
		});

	QObject::connect(this->butonDTO, &QPushButton::clicked, [&]()
		{
			RaportGUI* raport = new RaportGUI{ this->s };
			raport->show();
		});

	QObject::connect(this->butonAdaugaReteta, &QToolButton::clicked, [&]()
		{
			try
			{
				auto sel = lst->selectedItems();
				auto denumire = sel.at(0)->text().toStdString();
				auto producator = this->txtProducator->text().toStdString();
				auto pret = this->txtPret->text().toDouble();
				auto substantaActiva = this->txtSubstantaActiva->text().toInt();

				this->s.addReteta(denumire, producator, pret, substantaActiva);
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Atentie", "Medicament inexistent");
			}
		});

	QObject::connect(this->butonGolesteReteta, &QPushButton::clicked, [&]()
		{
			this->s.clearAll();
		});

	QObject::connect(this->butonGenereaza, &QPushButton::clicked, [&]()
		{
			int numar = this->txtGenerare->text().toInt();
			this->s.random(numar);
		});

	QObject::connect(this->lst, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = this->lst->selectedItems();
			if (sel.isEmpty())
			{
				this->txtDenumire->setText("");
				this->txtProducator->setText("");
				this->txtPret->setText("");
				this->txtSubstantaActiva->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				this->txtDenumire->setText(denumire);

				auto med = this->s.findMed(denumire.toStdString());
				this->txtProducator->setText(QString::fromStdString(med.getProducator()));
				this->txtPret->setText(QString::number(med.getPret()));
				this->txtSubstantaActiva->setText(QString::number(med.getSubstantaActiva()));
			}
		});
}

void ProductGUI::loadData(const vector<Medicament>& meds, const QColor& color)
{
	this->lst->clear();
	QPixmap pixmap("pills.png");
	QIcon icon(pixmap);

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(icon);
		medicament->setTextColor(color);
		this->lst->addItem(medicament);
	}
}

void ProductGUI::initGUI()
{
	this->styleForm();

	QHBoxLayout* mainLy = new QHBoxLayout();
	this->setLayout(mainLy);

	auto formLy = new QFormLayout;
	formLy->addRow("DENUMIRE:", this->txtDenumire);
	formLy->addRow("PRODUCATOR:", this->txtProducator);
	formLy->addRow("PRET:", this->txtPret);
	formLy->addRow("SUBSTANTA ACTIVA:", this->txtSubstantaActiva);
	formLy->addRow("GENERARE RANDOM:", this->txtGenerare);

	auto lyBtnsGrid = new QGridLayout;
	lyBtnsGrid->addWidget(this->butonUndo);
	lyBtnsGrid->addWidget(this->butonExit);

	auto lyBtns = new QHBoxLayout;
	lyBtns->addWidget(this->butonAdauga);
	lyBtns->addWidget(this->butonSterge);
	lyBtns->addWidget(this->butonActualizeaza);
	lyBtns->addWidget(this->butonCauta);

	auto lyBtnRetetaMare = new QVBoxLayout;
	auto lyBtnReteta1 = new QHBoxLayout;
	auto lyBtnReteta2 = new QHBoxLayout;
	lyBtnReteta1->addWidget(this->butonAdaugaReteta);
	lyBtnReteta1->addWidget(this->butonGolesteReteta);
	lyBtnReteta1->addWidget(this->butonGenereaza);
	lyBtnReteta2->addWidget(this->butonReteta);
	lyBtnReteta2->addWidget(this->butonReadOnly);
	lyBtnReteta2->addWidget(this->butonDTO);


	lyBtnRetetaMare->addLayout(lyBtnReteta1);
	lyBtnRetetaMare->addLayout(lyBtnReteta2);

	auto lyDreapta = new QVBoxLayout;
	lyDreapta->addLayout(formLy);
	lyDreapta->addLayout(lyBtnRetetaMare);
	lyDreapta->addLayout(lyBtns);
	lyDreapta->addLayout(lyBtnsGrid);

	auto lyBtnsSrv = new QHBoxLayout;
	lyBtnsSrv->addWidget(this->butonSorteazaDenumire);
	lyBtnsSrv->addWidget(this->butonSorteazaProducator);
	lyBtnsSrv->addWidget(this->butonSorteazaPretSubst);
	auto lySrv2 = new QHBoxLayout;
	lySrv2->addWidget(this->butonFiltreaza);

	auto lyStanga = new QVBoxLayout;
	lyStanga->addWidget(lst);
	lyStanga->addLayout(lyBtnsSrv);
	lyStanga->addLayout(lySrv2);

	auto layoutInput = new QHBoxLayout;
	layoutInput->addLayout(lyStanga);
	layoutInput->addLayout(lyDreapta);
	layoutInput->addLayout(this->lyBtnDyn);

	mainLy->addLayout(layoutInput);
}

void ProductGUI::adaugaButoane(const vector<Medicament>& meds)
{
	for (auto buton : this->butoane)
		delete buton;
	this->butoane.clear();

	for (auto med : meds)
	{
		auto btn = new QPushButton{ QString::fromStdString(med.getDenumire()) };
		this->butoane.push_back(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, btn, med]()
			{
				s.deleteMed(med.getDenumire(), med.getProducator());
				adaugaButoane(s.getMeds());
				loadData(s.getMeds(), "#7070db");
			});
		for (auto buton : this->butoane)
		{
			this->lyBtnDyn->addWidget(buton);
		}
	}
}