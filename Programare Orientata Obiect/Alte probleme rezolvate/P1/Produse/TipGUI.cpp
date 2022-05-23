#include "TipGUI.h"

void TipGUI::initGUI()
{
	this->setStyleSheet("background-image: url(fundal.jpg)");
	QPixmap pixmap("flower.png");
	QIcon icon(pixmap);
	this->setWindowIcon(icon);

	this->setWindowTitle(QString::fromStdString(this->tipProdus));
	this->layout = new QHBoxLayout;
	this->setLayout(layout);
	this->nr = new QLabel{};
	this->layout->addWidget(nr);
	this->layout->addSpacing(100);
	this->update();
}