#include "CosReadOnlyGUI.h"
#include <random>
#include <qcolor.h>
#include <qbrush.h>

void CosReadOnlyGUI::update()
{
	repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };

	for (auto u : ret.getReteta())
	{
		int x = rand() % 2000;
		int y = rand() % 1000;
		p.fillRect(x, y, 50, 50, QColor(rand() % 256, rand() % 256, rand() % 256));
	}
}
