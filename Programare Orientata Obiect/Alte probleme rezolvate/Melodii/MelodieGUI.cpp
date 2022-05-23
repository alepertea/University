#include "MelodieGUI.h"

void MelodieGUI::initGUI()
{
	this->setStyleSheet("background-image: url(fundal.jpg)");
	this->setWindowTitle("Flori, fete si baieti, melodii sau cantareti");

	QVBoxLayout* mainLy = new QVBoxLayout;

	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLy);

	mainLy->addLayout(mainLayout);

	QVBoxLayout* layoutStanga = new QVBoxLayout;
	QVBoxLayout* layoutDreapta = new QVBoxLayout;

	this->slider->setRange(0, 10);
	this->slider->setOrientation(Qt::Horizontal);

	layoutStanga->addWidget(this->table);

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("TITLU:", this->txtTitlu);
	layoutDreapta->addLayout(formLayout);
	layoutDreapta->addWidget(this->slider);
	layoutDreapta->addWidget(this->butonModificare);
	layoutDreapta->addWidget(this->butonStergere);

	mainLayout->addLayout(layoutStanga);
	mainLayout->addLayout(layoutDreapta);

	this->tab->setFixedHeight(this->height() / 2);
	
	QHBoxLayout* layoutDesen = new QHBoxLayout;
	layoutDesen->addWidget(this->tab);
	mainLy->addLayout(layoutDesen);
}

void MelodieGUI::initConnect()
{
	QObject::connect(this->butonModificare, &QPushButton::clicked, [&]()
		{
			int rank = this->slider->value();
			string titlu = this->txtTitlu->text().toStdString();

			int selRow = this->table->selectionModel()->selectedIndexes().at(0).row();
			auto cel0Index = this->table->model()->index(selRow, 0);
			auto id = this->table->model()->data(cel0Index, Qt::DisplayRole).toInt();
			try
			{
				s.modifySong(id, titlu, rank);
				this->loadData(s.getSongs());
			}
			catch (exception&)
			{
				QMessageBox::warning(nullptr, "Date invalide", "Titlul nu poate fi vid!");
			}
		});

	QObject::connect(this->butonStergere, &QPushButton::clicked, [&]()
		{
			int selRow = this->table->selectionModel()->selectedIndexes().at(0).row();
			auto cel0Index = this->table->model()->index(selRow, 0);
			auto id = this->table->model()->data(cel0Index, Qt::DisplayRole).toInt();

			auto cel2Index = this->table->model()->index(selRow, 2);
			auto artist = this->table->model()->data(cel2Index, Qt::DisplayRole).toString();

			try
			{
				this->s.deleteSong(id, artist.toStdString());
				this->loadData(s.getSongs());
			}
			catch (RepoException& e)
			{
				QMessageBox::information(nullptr, "NUUUUUUUUUUUUUUUUU", QString::fromStdString(e.getMessage()));
			}
		});

	QObject::connect(this->table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]()
		{
			if (this->table->selectionModel()->selectedIndexes().isEmpty())
			{
				this->txtTitlu->setText("");
				return;
			}
			int selRow = this->table->selectionModel()->selectedIndexes().at(0).row();
			auto cel1Index = this->table->model()->index(selRow, 1);
			auto cellValue = this->table->model()->data(cel1Index, Qt::DisplayRole).toString();
			this->txtTitlu->setText(cellValue);
		});
}

void MelodieGUI::loadData(const vector<Melodie>& songs)
{
	this->model->setSongs(this->s.getSongs());
	this->model->refresh();
	this->tab->repaint();
}

void MyWidget::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };

	for (int i = 0; i <= 10; i++)
	{
		int w = this->width();
		int h = this->height();
		int nr = this->s.getNumberOfSongsByRank(i);
		p.fillRect(i * 20, h - (nr * 20), 10, nr * 20, QColor(240, 26, 26));
	}
}
