#include "RetetaGUI.h"

void RetetaGUI::styleForm()
{
	this->setStyleSheet("background-color:#b3c4ff");
	lst1->setStyleSheet("background-color:#d4ddff");
	lst2->setStyleSheet("background-color:#d4ddff");

	txtDenumire1->setStyleSheet("background-color:#d4ddff");
	txtDenumire2->setStyleSheet("background-color:#d4ddff");
	txtProducator1->setStyleSheet("background-color:#d4ddff");
	txtProducator2->setStyleSheet("background-color:#d4ddff");
	txtPret1->setStyleSheet("background-color:#d4ddff");
	txtPret2->setStyleSheet("background-color:#d4ddff");
	txtSubstantaActiva1->setStyleSheet("background-color:#d4ddff");
	txtSubstantaActiva2->setStyleSheet("background-color:#d4ddff");

	butonAdauga->setStyleSheet("background-color:#5e80ff");
	butonGoleste->setStyleSheet("background-color:#5e80ff");
	butonGenereaza->setStyleSheet("background-color:#5e80ff");
	butonUndo->setStyleSheet("background-color:#5e80ff");
	butonExportHTML->setStyleSheet("background-color:#5e80ff");
	butonExportCSV->setStyleSheet("background-color:#5e80ff");
	butonExit->setStyleSheet("background-color:#3e5ed6");

	spinbox->setStyleSheet("background-color:#d4ddff");
}

void RetetaGUI::initGUI()
{
	styleForm();

	this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
	this->setWindowTitle("Retetaaaaaaaaaaaaaaaaaaaaaaaaa");

	QHBoxLayout* mainLy = new QHBoxLayout();
	setLayout(mainLy);

	auto formMeds = new QFormLayout;
	formMeds->addRow("DENUMIRE:", txtDenumire1);
	formMeds->addRow("PRODUCATOR:", txtProducator1);
	formMeds->addRow("PRET:", txtPret1);
	formMeds->addRow("SUBSTANTA ACTIVA:", txtSubstantaActiva1);

	auto formReteta = new QFormLayout;
	formReteta->addRow("DENUMIRE:", txtDenumire2);
	formReteta->addRow("PRODUCATOR:", txtProducator2);
	formReteta->addRow("PRET:", txtPret2);
	formReteta->addRow("SUBSTANTA ACTIVA:", txtSubstantaActiva2);

	butonAdauga->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
	butonAdauga->setText(">>");
	spinbox->setRange(0, 100);

	auto lyBtnsGrid = new QGridLayout;
	lyBtnsGrid->addWidget(butonAdauga);

	auto lyBtns = new QVBoxLayout;
	lyBtns->addWidget(spinbox);
	lyBtns->addWidget(butonGenereaza);
	lyBtns->addWidget(butonGoleste);
	lyBtns->addWidget(butonUndo);
	lyBtns->addWidget(butonExportHTML);
	lyBtns->addWidget(butonExportCSV);
	lyBtns->addWidget(butonExit);

	auto lyDreapta = new QVBoxLayout;
	lyDreapta->addWidget(lst2);
	lyDreapta->addLayout(formReteta);

	auto lyStanga = new QVBoxLayout;
	lyStanga->addWidget(lst1);
	lyStanga->addLayout(formMeds);

	auto lyMijloc = new QVBoxLayout;
	lyMijloc->addLayout(lyBtnsGrid);

	auto lyButoane = new QHBoxLayout;
	lyButoane->addLayout(lyBtns);

	auto layoutInput = new QHBoxLayout;
	layoutInput->addLayout(lyStanga);
	layoutInput->addLayout(lyMijloc);
	layoutInput->addLayout(lyDreapta);
	layoutInput->addLayout(lyButoane);

	mainLy->addLayout(layoutInput);
}

void RetetaGUI::initConnect()
{
	QObject::connect(butonExit, &QPushButton::clicked, [&](){ close(); });

	QObject::connect(butonExportHTML, &QPushButton::clicked, [&]()
		{
			s.exportHTML("reteta.html"); 
			QMessageBox::information(nullptr, "Export", "Datele au fost exportate in fisierul 'reteta.html'");
		});

	QObject::connect(butonExportCSV, &QPushButton::clicked, [&]() 
		{
			s.exportCSV("reteta.csv"); 
			QMessageBox::information(nullptr, "Export", "Datele au fost exportate in fisierul 'reteta.csv'");
		});

	QObject::connect(butonAdauga, &QToolButton::clicked, [&]()
		{
			try
			{
				auto sel = lst1->selectedItems();
				auto denumire = sel.at(0)->text().toStdString();
				auto producator = txtProducator1->text().toStdString();
				auto pret = txtPret1->text().toDouble();
				auto substantaActiva = txtSubstantaActiva1->text().toInt();

				s.addReteta(denumire, producator, pret, substantaActiva);
				loadDataReteta(s.getReteta(), "#1e3a96");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Atentie", "Medicament inexistent");
			}
		});

	QObject::connect(butonGoleste, &QPushButton::clicked, [&]()
		{
			s.clearAll();
			loadDataReteta(s.getReteta(), "#1e3a96");
		});

	QObject::connect(butonUndo, &QPushButton::clicked, [&]()
		{
			try
			{
				s.undo();
				loadDataReteta(s.getReteta(), "#1e3a96");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Undo", "Nu se mai poate face undo!");
			}
		});

	QObject::connect(butonGenereaza, &QPushButton::clicked, [&]()
		{
			int numar = spinbox->value();
			s.random(numar);
			loadDataReteta(s.getReteta(), "#1e3a96");
		});

	QObject::connect(lst1, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = lst1->selectedItems();
			if (sel.isEmpty())
			{
				txtDenumire1->setText("");
				txtProducator1->setText("");
				txtPret1->setText("");
				txtSubstantaActiva1->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				txtDenumire1->setText(denumire);

				auto med = s.findMed(denumire.toStdString());
				txtProducator1->setText(QString::fromStdString(med.getProducator()));
				txtPret1->setText(QString::number(med.getPret()));
				txtSubstantaActiva1->setText(QString::number(med.getSubstantaActiva()));
			}
		});

	QObject::connect(lst2, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = lst2->selectedItems();
			if (sel.isEmpty())
			{
				txtDenumire2->setText("");
				txtProducator2->setText("");
				txtPret2->setText("");
				txtSubstantaActiva2->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				txtDenumire2->setText(denumire);

				auto med = s.findMedReteta(denumire.toStdString());
				txtProducator2->setText(QString::fromStdString(med.getProducator()));
				txtPret2->setText(QString::number(med.getPret()));
				txtSubstantaActiva2->setText(QString::number(med.getSubstantaActiva()));
			}
		});
}

void RetetaGUI::loadDataMeds(const vector<Medicament>& meds, const QColor& color)
{
	lst1->clear();

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogYesButton));
		medicament->setTextColor(color);
		lst1->addItem(medicament);
	}
}

void RetetaGUI::loadDataReteta(const vector<Medicament>& meds, const QColor& color)
{
	lst2->clear();

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
		medicament->setTextColor(color);
		lst2->addItem(medicament);
	}
}