#include "RaportGUI.h"

void RaportGUI::initGUI()
{
	this->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
	this->setWindowTitle("DTO");
	this->setStyleSheet("background-image: url(nuj.png)");

	this->s.addObserver(this);

	QHBoxLayout* mainLy = new QHBoxLayout;
	this->setLayout(mainLy);

	mainLy->addWidget(lst);
}

void RaportGUI::loadData(const vector<DTO> dto)
{
	this->lst->clear();

	for (const auto& subst : dto)
	{
		int substActiva = subst.getSubstantaActiva();
		int nrMeds = subst.getNrMedicamente();

		string text = "Cantitatea de subst activa: " + to_string(substActiva) + '\t' + "Numar medicamente: " + to_string(nrMeds);

		QListWidgetItem* obiect = new QListWidgetItem(QString::fromStdString(text));
		obiect->setIcon(QApplication::style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
		obiect->setTextColor(Qt::white);
		this->lst->addItem(obiect);
	}
}

void RaportGUI::update()
{
	this->loadData(this->s.makeDTOVector());
}
