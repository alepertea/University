#include "ProductGUI.h"

void ProductGUI::initConnect()
{
	QObject::connect(butonExit, &QPushButton::clicked, [&]() { close(); });

	QObject::connect(radioAdd, &QRadioButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();
			auto pret = txtPret->text();
			auto substantaActiva = txtSubstantaActiva->text();

			try
			{
				s.addMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt());
				loadData();
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::information(nullptr, "Date invalide", "Medicamentul deja exista!");
			}
		});

	QObject::connect(butonSterge, &QPushButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();

			try
			{
				s.deleteMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData());
				loadData();
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::information(nullptr, "Date invalide", "Medicamentul nu exista");
			}
		});

	QObject::connect(radioActualizeaza, &QRadioButton::clicked, [&]()
		{
			auto denumire = txtDenumire->text();
			auto producator = txtProducator->text();
			auto pret = txtPret->text();
			auto substantaActiva = txtSubstantaActiva->text();

			try
			{
				s.modifyMed(denumire.toLocal8Bit().constData(), producator.toLocal8Bit().constData(), pret.toDouble(), substantaActiva.toInt(), 3);
				loadData();
			}
			catch (ValidateException&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Medicament invalid");
			}
			catch (RepositoryException&)
			{
				QMessageBox::information(nullptr, "Date invalide", "Medicamentul nu exista");
			}
		});

	QObject::connect(butonUndo, &QPushButton::clicked, [&]()
		{
			try
			{
				s.undo();
				loadData();
			}
			catch (RepositoryException&)
			{
				QMessageBox::information(nullptr, "Undo", "Nu se mai poate face undo!");
			}
		});

	QObject::connect(radioCauta, &QRadioButton::clicked, [&]()
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

void ProductGUI::loadData()
{
	lst->clear();
	auto allMeds = s.getMeds();

	for (const auto& med : allMeds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		lst->addItem(medicament);
	}
}

void ProductGUI::initGUI()
{
	QHBoxLayout* mainLy = new QHBoxLayout();
	setLayout(mainLy);

	mainLy->addWidget(lst);

	auto formLy = new QFormLayout;
	formLy->addRow("Denumire", txtDenumire);
	formLy->addRow("Producator", txtProducator);
	formLy->addRow("Pret", txtPret);
	formLy->addRow("Substanta Activa", txtSubstantaActiva);

	auto lyBtnsLab = new QGridLayout;
	lyBtnsLab->addWidget(radioAdd);
	lyBtnsLab->addWidget(butonSterge);
	lyBtnsLab->addWidget(radioActualizeaza);
	lyBtnsLab->addWidget(butonUndo);
	lyBtnsLab->addWidget(radioCauta);
	lyBtnsLab->addWidget(butonExit);

	/*
	auto lyBtns = new QHBoxLayout;
	lyBtns->addWidget(butonAdauga);
	lyBtns->addWidget(butonSterge);
	lyBtns->addWidget(butonActualizeaza);
	lyBtns->addWidget(butonExit);

	auto lyBtns2 = new QHBoxLayout;
	lyBtns2->addWidget(butonUndo);
	lyBtns2->addWidget(butonCauta);
	*/
	auto layoutInput = new QVBoxLayout;
	layoutInput->addLayout(formLy);
	layoutInput->addLayout(lyBtnsLab);
	//layoutInput->addLayout(lyBtns2);

	mainLy->addLayout(layoutInput);
}