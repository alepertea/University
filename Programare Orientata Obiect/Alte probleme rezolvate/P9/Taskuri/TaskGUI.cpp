#include "TaskGUI.h"

void TaskGUI::initGUI()
{
	this->setStyleSheet("background-image:url(fundal.jpg)");
	this->setWindowTitle("Task");
	QPixmap pixmap("flower.png");
	QIcon icon(pixmap);
	this->setWindowIcon(icon);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("ID TASK:", this->txtID);
	formLayout->addRow("DESCRIERE:", this->txtDescriere);
	formLayout->addRow("PROGRAMATOR:", this->txtProgramator);
	formLayout->addRow("STARE TASK:", this->txtStare);
	formLayout->addRow("CAUTA:", this->txtCautare);

	QHBoxLayout* layoutButoane = new QHBoxLayout;
	layoutButoane->addWidget(this->butonAdaugare);
	layoutButoane->addWidget(this->butonExit);

	QVBoxLayout* layoutStanga = new QVBoxLayout;
	QVBoxLayout* layoutDreapta = new QVBoxLayout;

	layoutStanga->addWidget(this->table);
	layoutDreapta->addLayout(formLayout);
	layoutDreapta->addLayout(layoutButoane);

	mainLayout->addLayout(layoutStanga);
	mainLayout->addLayout(layoutDreapta);
}

void TaskGUI::initConnect()
{
	QObject::connect(this->butonExit, &QPushButton::clicked, [&]() { this->close(); });

	QObject::connect(this->butonAdaugare, &QPushButton::clicked, [&]()
		{
			auto id = this->txtID->text().toInt();
			auto descriere = this->txtDescriere->text().toStdString();
			auto programator = this->txtProgramator->text().toStdString();
			auto stare = this->txtStare->text().toStdString();

			try
			{
				vector<string> p;
				p.clear();
				p.push_back(programator);
				this->s.addTask(id, descriere, p, stare);
				this->loadData(this->s.sortByState());
			}
			catch (RepoException& e)
			{
				QMessageBox::warning(nullptr, "ID duplicat", QString::fromStdString(e.getMessage()));
			}
			catch (ValidException& e)
			{
				QMessageBox::warning(nullptr, "Date invalide", QString::fromStdString(e.getMessage()));
			}
		});

	QObject::connect(this->txtCautare, &QLineEdit::textChanged, [&]()
		{
			string nume = this->txtCautare->text().toStdString();
			vector<Task> rez = this->s.getTasksByProg(nume);
			this->loadData(rez);
		});
}

void TaskGUI::loadData(vector<Task> tasks)
{
	this->model->setTasks(tasks);
	this->model->refresh();
}
