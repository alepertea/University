#pragma once
#include "Joc.h"
#include <QAbstractTableModel>
#include <vector>

using namespace std;

class TableModel : public QAbstractTableModel
{
private:
	vector<Joc> jocuri;

public:
	TableModel(const vector<Joc>& j) : jocuri{ j } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return this->jocuri.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role) const override
	{
		if (role == Qt::DisplayRole)
		{
			Joc j = this->jocuri[index.row()];
			if (index.column() == 0)
				return QString::number(j.getID());
			if (index.column() == 1)
				return QString::number(j.getDim());
			if (index.column() == 2)
				return QString::fromStdString(j.getTabla());
			if (index.column() == 3)
			{
				if (j.getJucator() == 'X')
					return QString::fromStdString("X");
				return QString::fromStdString("O");
			}
			if (index.column() == 4)
			{
				if(j.getStare() == "InDerulare")
					return QString::fromStdString("In derulare");
				return QString::fromStdString(j.getStare());
			}
		}
		return QVariant{};
	}

	void setJocuri(const vector<Joc>& jocuri)
	{
		this->jocuri = jocuri;
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
				return "ID JOC";
			if (section == 1)
				return "DIMENSIUNE";
			if (section == 2)
				return "TABLA JOC";
			if (section == 3)
				return "JUCATOR";
			if (section == 4)
				return "STARE JOC";
		}
		return QVariant();
	}
};