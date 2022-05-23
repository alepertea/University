#include "RetetaGUI.h"

void RetetaGUI::styleForm()
{
	this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
	this->setWindowTitle("CosCRUDGUI");
	this->setStyleSheet("background-image: url(nuj.png)");
}

void RetetaGUI::initGUI()
{
	this->styleForm();

	this->ret.addObserver(this);
	this->r.addObserver(this);

	QHBoxLayout* mainLy = new QHBoxLayout();
	this->setLayout(mainLy);

	auto formMeds = new QFormLayout;
	formMeds->addRow("DENUMIRE:", this->txtDenumire1);
	formMeds->addRow("PRODUCATOR:", this->txtProducator1);
	formMeds->addRow("PRET:", this->txtPret1);
	formMeds->addRow("SUBSTANTA ACTIVA:", this->txtSubstantaActiva1);

	auto formReteta = new QFormLayout;
	formReteta->addRow("DENUMIRE:", this->txtDenumire2);
	formReteta->addRow("PRODUCATOR:", this->txtProducator2);
	formReteta->addRow("PRET:", this->txtPret2);
	formReteta->addRow("SUBSTANTA ACTIVA:", this->txtSubstantaActiva2);

	this->butonAdauga->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
	this->butonAdauga->setText(">>");
	this->spinbox->setRange(0, 100);

	auto lyBtnsGrid = new QGridLayout;
	lyBtnsGrid->addWidget(this->butonAdauga);

	auto lyBtns = new QVBoxLayout;
	lyBtns->addWidget(this->spinbox);
	lyBtns->addWidget(this->butonGenereaza);
	lyBtns->addWidget(this->butonGoleste);
	lyBtns->addWidget(this->butonUndo);
	lyBtns->addWidget(this->butonExportHTML);
	lyBtns->addWidget(this->butonExportCSV);
	lyBtns->addWidget(this->butonExit);

	auto lyDreapta = new QVBoxLayout;
	lyDreapta->addWidget(this->lst2);
	lyDreapta->addLayout(formReteta);

	auto lyStanga = new QVBoxLayout;
	lyStanga->addWidget(this->lst1);
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
	QObject::connect(this->butonExit, &QPushButton::clicked, [&]() { this->close(); });

	QObject::connect(this->butonExportHTML, &QPushButton::clicked, [&]()
		{
			this->s.exportHTML("reteta.html");
			QMessageBox::information(nullptr, "Export", "Datele au fost exportate in fisierul 'reteta.html'");
		});

	QObject::connect(this->butonExportCSV, &QPushButton::clicked, [&]()
		{
			this->s.exportCSV("reteta.csv");
			QMessageBox::information(nullptr, "Export", "Datele au fost exportate in fisierul 'reteta.csv'");
		});

	QObject::connect(this->butonAdauga, &QToolButton::clicked, [&]()
		{
			try
			{
				auto sel = lst1->selectedItems();
				auto denumire = sel.at(0)->text().toStdString();
				auto producator = this->txtProducator1->text().toStdString();
				auto pret = this->txtPret1->text().toDouble();
				auto substantaActiva = this->txtSubstantaActiva1->text().toInt();

				this->s.addReteta(denumire, producator, pret, substantaActiva);
				loadDataReteta(this->s.getReteta(), "#000000");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Atentie", "Medicament inexistent");
			}
		});

	QObject::connect(this->butonGoleste, &QPushButton::clicked, [&]()
		{
			this->s.clearAll();
			loadDataReteta(this->s.getReteta(), "#000000");
		});

	QObject::connect(this->butonUndo, &QPushButton::clicked, [&]()
		{
			try
			{
				this->s.undo();
				loadDataReteta(this->s.getReteta(), "#000000");
			}
			catch (RepositoryException&)
			{
				QMessageBox::warning(nullptr, "Undo", "Nu se mai poate face undo!");
			}
		});

	QObject::connect(this->butonGenereaza, &QPushButton::clicked, [&]()
		{
			int numar = this->spinbox->value();
			this->s.random(numar);
			loadDataReteta(this->s.getReteta(), "#000000");
		});

	QObject::connect(this->lst1, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = this->lst1->selectedItems();
			if (sel.isEmpty())
			{
				this->txtDenumire1->setText("");
				this->txtProducator1->setText("");
				this->txtPret1->setText("");
				this->txtSubstantaActiva1->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				this->txtDenumire1->setText(denumire);

				auto med = this->s.findMed(denumire.toStdString());
				this->txtProducator1->setText(QString::fromStdString(med.getProducator()));
				this->txtPret1->setText(QString::number(med.getPret()));
				this->txtSubstantaActiva1->setText(QString::number(med.getSubstantaActiva()));
			}
		});

	QObject::connect(this->lst2, &QListWidget::itemSelectionChanged, [&]()
		{
			auto sel = this->lst2->selectedItems();
			if (sel.isEmpty())
			{
				this->txtDenumire2->setText("");
				this->txtProducator2->setText("");
				this->txtPret2->setText("");
				this->txtSubstantaActiva2->setText("");
			}
			else
			{
				auto selItem = sel.at(0);
				auto denumire = selItem->text();
				this->txtDenumire2->setText(denumire);

				auto med = s.findMedReteta(denumire.toStdString());
				this->txtProducator2->setText(QString::fromStdString(med.getProducator()));
				this->txtPret2->setText(QString::number(med.getPret()));
				this->txtSubstantaActiva2->setText(QString::number(med.getSubstantaActiva()));
			}
		});
}

void RetetaGUI::loadDataMeds(const vector<Medicament>& meds, const QColor& color)
{
	this->lst1->clear();
	QPixmap pixmap("pill.png");
	QIcon icon(pixmap);

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(icon);
		medicament->setTextColor(color);
		this->lst1->addItem(medicament);
	}
}

void RetetaGUI::loadDataReteta(const vector<Medicament>& meds, const QColor& color)
{
	this->lst2->clear();
	QPixmap pixmap("recipe.png");
	QIcon icon(pixmap);

	for (const auto& med : meds)
	{
		QListWidgetItem* medicament = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
		medicament->setIcon(icon);
		medicament->setTextColor(color);
		this->lst2->addItem(medicament);
	}
}