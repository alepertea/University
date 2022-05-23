#include "OpenGUI.h"

void OpenGUI::initGUI()
{
	this->setStyleSheet("background-image:url(fundal.jpg)");
	this->setWindowTitle("OpenGUI");
	QPixmap pixmap("flower.png");
	QIcon icon(pixmap);
	this->setWindowIcon(icon);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QVBoxLayout* layoutButoane = new QVBoxLayout;
	layoutButoane->addWidget(this->butonOpen);
	layoutButoane->addWidget(this->butonClosed);
	layoutButoane->addWidget(this->butonInProgress);

	mainLayout->addWidget(this->lst);
	mainLayout->addLayout(layoutButoane);
}

void OpenGUI::loadData(const vector<Task>& tasks)
{
	this->lst->clear();
	for (const auto& t : tasks)
	{
		for (const auto& p : t.getProgramatori())
		{
			QString it = QString::number(t.getID()) + " - " + QString::fromStdString(t.getDescriere()) + " - " + QString::fromStdString(p + "\n");
			this->lst->addItem(it);
		}
	}
}

void OpenGUI::initConnect()
{
	QObject::connect(this->butonOpen, &QPushButton::clicked, [&]()
		{
			auto sel = this->lst->selectedItems();

			if (!sel.isEmpty())
			{
				auto selItem = sel.at(0)->text().toStdString();
				string aux = "";
				int i = 0;
				while (selItem[i] != ' ')
				{
					aux += selItem[i];
					i++;
				}

				int id = stoi(aux);
				this->s.modifyState(id, "open");
				this->gui.reloadDataAfterModification();
			}
		});

	QObject::connect(this->butonClosed, &QPushButton::clicked, [&]()
		{
			auto sel = this->lst->selectedItems();

			if (!sel.isEmpty())
			{
				auto selItem = sel.at(0)->text().toStdString();
				string aux = "";
				int i = 0;
				while (selItem[i] != ' ')
				{
					aux += selItem[i];
					i++;
				}

				int id = stoi(aux);
				this->s.modifyState(id, "closed");
				this->gui.reloadDataAfterModification();
			}
		});

	QObject::connect(this->butonInProgress, &QPushButton::clicked, [&]()
		{
			auto sel = this->lst->selectedItems();

			if (!sel.isEmpty())
			{
				auto selItem = sel.at(0)->text().toStdString();
				string aux = "";
				int i = 0;
				while (selItem[i] != ' ')
				{
					aux += selItem[i];
					i++;
				}

				int id = stoi(aux);
				this->s.modifyState(id, "inprogress");
				this->gui.reloadDataAfterModification();
			}
		});
}
