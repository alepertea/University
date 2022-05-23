#include "JocGUI.h"

void clearLayout(QLayout* layout) {
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

QVBoxLayout* JocGUI::creareTabla(const int& dim,const string& tabla)
{
	QVBoxLayout* coloana = new QVBoxLayout;
	int cnt = 0;
	for (int i = 0; i < dim; i++)
	{
		QHBoxLayout* linie = new QHBoxLayout;
		for (int j = 0; j < dim; j++)
		{
			string s;
			s.clear();
			s.push_back(tabla[cnt]);
			if (s == "-")
				s = " ";
			QPushButton* buton = new QPushButton{ QString::fromStdString(s) };
			cnt++;
			buton->setFixedHeight(75);
			buton->setFixedWidth(75);
			this->butoane.push_back(buton);
			linie->addWidget(buton);

			if (s == " ")
			{
				QObject::connect(buton, &QPushButton::clicked, [this, buton]()
					{
						string jucator = this->txtJucatorCurent->text().toStdString();
						buton->setText(QString::fromStdString(jucator));

						int id = this->txtID->text().toInt();
						int dim = this->txtDimensiune->text().toInt();
						string tabla = this->txtTablaJoc->text().toStdString();

						for (unsigned int k = 0; k < this->butoane.size(); k++)
						{
							if (this->butoane[k] == buton)
							{
								tabla[k] = jucator[0];
							}
						}

						if (this->txtJucatorCurent->text() == "X")
						{
							this->txtJucatorCurent->setText("O");
							this->txtStare->setText("In derulare");
							this->txtTablaJoc->setText(QString::fromStdString(tabla));

							this->s.modify(this->txtID->text().toInt(), this->txtDimensiune->text().toInt(), tabla, 'O', "InDerulare");
						}
						else
						{
							this->txtJucatorCurent->setText("O");
							this->txtStare->setText("In derulare");
							this->txtTablaJoc->setText(QString::fromStdString(tabla));

							this->s.modify(this->txtID->text().toInt(), this->txtDimensiune->text().toInt(), tabla, 'X', "InDerulare");
						}

						this->loadData(this->s.getAll());
					});
			}
		}
		coloana->addLayout(linie);
	}
	return coloana;
}

void JocGUI::initGUI()
{
	this->setLayout(this->mainLayout);

	this->setStyleSheet("background-image: url(fundal.jpg)");

	QVBoxLayout* layoutStanga = new QVBoxLayout;
	QVBoxLayout* layoutDreapta = new QVBoxLayout;

	layoutStanga->addWidget(this->tabel);

	QFormLayout* layoutTxt = new QFormLayout;
	layoutTxt->addRow("DIM: ", this->txtDim);
	layoutTxt->addRow("TABLA: ", this->txtTabla);
	layoutTxt->addRow("JUCATOR: ", this->txtJucator);
	
	layoutDreapta->addLayout(layoutTxt);
	layoutDreapta->addWidget(this->butonAdaugare);

	QFormLayout* layoutModificare = new QFormLayout;
	layoutModificare->addRow("ID: ", this->txtID);
	layoutModificare->addRow("DIM: ", this->txtDimensiune);
	layoutModificare->addRow("TABLA: ", this->txtTablaJoc);
	layoutModificare->addRow("JUCATOR: ", this->txtJucatorCurent);
	layoutModificare->addRow("STARE: ", this->txtStare);

	layoutDreapta->addLayout(layoutModificare);
	layoutDreapta->addWidget(this->butonModificare);

	this->layoutJos->addLayout(creareTabla(3, "---------"));

	this->layoutSus->addLayout(layoutStanga);
	this->layoutSus->addLayout(layoutDreapta);
	this->mainLayout->addLayout(layoutSus);
	this->mainLayout->addLayout(layoutJos);
}

void JocGUI::initConnect()
{
	QObject::connect(this->butonAdaugare, &QPushButton::clicked, [&]() 
		{
			int dim = this->txtDim->text().toInt();
			string tabla = this->txtTabla->text().toStdString();
			char jucator = this->txtJucator->text().toStdString()[0];

			try
			{
				int id = rand() % 100;
				this->s.add(id, dim, tabla, jucator, "Neinceput");
				this->loadData(this->s.getAll());
			}
			catch (ValidException& e)
			{
				QMessageBox::warning(nullptr, "Date invalide", QString::fromStdString(e.getMessage()));
			}
		});

	QObject::connect(this->butonModificare, &QPushButton::clicked, [&]()
		{
			int id = this->txtID->text().toInt();
			int dim = this->txtDimensiune->text().toInt();
			string tabla = this->txtTablaJoc->text().toStdString();
			char jucator = this->txtJucatorCurent->text().toStdString()[0];
			string stare = this->txtStare->text().toStdString();

			try
			{
				if (stare == "In derulare")
					stare = "InDerulare";
				this->s.modify(id, dim, tabla, jucator, stare);
				this->loadData(this->s.getAll());
			}
			catch (ValidException& e)
			{
				QMessageBox::warning(nullptr, "Date invalide", QString::fromStdString(e.getMessage()));
			}
		});

	QObject::connect(this->tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]()
		{
			if (this->tabel->selectionModel()->selectedIndexes().isEmpty())
			{
				this->txtID->setText("");
				this->txtDimensiune->setText("");
				this->txtTablaJoc->setText("");
				this->txtJucatorCurent->setText("");
				this->txtStare->setText("");
				return;
			}
			int selRow = this->tabel->selectionModel()->selectedIndexes().at(0).row();
			auto cel1Index = this->tabel->model()->index(selRow, 1);
			auto cel0Index = this->tabel->model()->index(selRow, 0);
			auto cel2Index = this->tabel->model()->index(selRow, 2);
			auto cel3Index = this->tabel->model()->index(selRow, 3);
			auto cel4Index = this->tabel->model()->index(selRow, 4);

			auto cel1Value = this->tabel->model()->data(cel1Index, Qt::DisplayRole).toString();
			auto cel2Value = this->tabel->model()->data(cel2Index, Qt::DisplayRole).toString();
			auto cel3Value = this->tabel->model()->data(cel3Index, Qt::DisplayRole).toString();
			auto cel4Value = this->tabel->model()->data(cel4Index, Qt::DisplayRole).toString();
			auto cel0Value = this->tabel->model()->data(cel0Index, Qt::DisplayRole).toString();

			this->txtID->setText(cel0Value);
			this->txtDimensiune->setText(cel1Value);
			this->txtTablaJoc->setText(cel2Value);
			this->txtJucatorCurent->setText(cel3Value);
			this->txtStare->setText(cel4Value);

			for (auto buton : this->butoane)
				delete buton;
			this->butoane.clear();
			this->layoutJos->addLayout(this->creareTabla(this->txtDimensiune->text().toInt(), this->txtTablaJoc->text().toStdString()));
		});
}

void JocGUI::loadData(const vector<Joc>& jocuri)
{
	this->model->setJocuri(jocuri);
	this->model->refresh();
}
