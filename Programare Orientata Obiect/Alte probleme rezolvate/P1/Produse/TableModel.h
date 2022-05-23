#pragma once
#include "Produs.h"
#include <QAbstractTableModel>
#include <vector>

using namespace std;

class TableModel : public QAbstractTableModel
{
private:
	vector<Produs> produse;
	int valoareSlider;

public:
	TableModel(const vector<Produs>& produse) : produse{ produse }, valoareSlider{ 0 } {}

	void setValoareSlider(const double& value)
	{
		this->valoareSlider = value;
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return this->produse.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role) const override
	{
		if (role == Qt::BackgroundColorRole)
		{
			Produs p = this->produse[index.row()];
			if (p.getPret() <= this->valoareSlider)
			{
				QBrush bg(Qt::red);
				return bg;
			}
		}

		if (role == Qt::DisplayRole)
		{
			Produs p = this->produse[index.row()];
			if (index.column() == 0)
				return QString::number(p.getID());
			if (index.column() == 1)
				return QString::fromStdString(p.getNume());
			if (index.column() == 2)
				return QString::fromStdString(p.getTip());
			if (index.column() == 3)
				return QString::number(p.getPret());
			if (index.column() == 4)
				return QString::number(p.getNumarVocale());
		}
		return QVariant{};
	}

	void setProducts(const vector<Produs>& produse)
	{
		this->produse = produse;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}

	void refresh()
	{
		emit layoutChanged();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
		{
			if (section == 0)
				return "ID";
			if (section == 1)
				return "NUME";
			if (section == 2)
				return "TIP";
			if (section == 3)
				return "PRET";
			if (section == 4)
				return "NUMAR VOCALE";
		}
		return QVariant();
	}
};