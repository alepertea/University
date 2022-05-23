#include <QWidget>
#include <QLabel>
#include <string>
#include "Observer.h"
#include <vector>
#include "Produs.h"
#include "Service.h"
#include <QHBoxLayout>
#include <qicon.h>
#include <qpixmap.h>

class TipGUI : public QWidget, public Observer
{
private:
	string tipProdus;
	QLabel* nr;
	QHBoxLayout* layout;
	Service& s;
	int numar;

	void initGUI();

public:
	TipGUI(Service& s, const string& tipProdus, const int& numar) : s{ s }, tipProdus{ tipProdus }, numar{ numar }
	{
		this->initGUI();
	}

	virtual void update() override
	{
		nr->setText("Numar elemente:" + QString::number(this->s.getNumberOfProducts(this->tipProdus)));
	}

};