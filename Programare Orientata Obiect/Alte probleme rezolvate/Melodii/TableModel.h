#pragma once
#pragma once
#include "Melodie.h"
#include <QAbstractTableModel>
#include <vector>

using namespace std;

class TableModel : public QAbstractTableModel
{
private:
	vector<Melodie> songs;

public:
	TableModel(const vector<Melodie>& songs) : songs{ songs } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return this->songs.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role) const override
	{
		if (role == Qt::DisplayRole)
		{
			Melodie m = this->songs[index.row()];
			if (index.column() == 0)
				return QString::number(m.getID());
			if (index.column() == 1)
				return QString::fromStdString(m.getTitlu());
			if (index.column() == 2)
				return QString::fromStdString(m.getArtist());
			if (index.column() == 3)
				return QString::number(m.getRank());
			if (index.column() == 4)
			{
				int rank = m.getRank();
				int count = 0;
				for (const auto& mel : this->songs)
				{
					if (mel.getRank() == rank)
						count++;
				}
				return QString::number(count - 1);
			}
		}
		return QVariant{};
	}

	void setSongs(const vector<Melodie>& songs)
	{
		this->songs = songs;
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
				return "ID MELODIE";
			if (section == 1)
				return "TITLU MELODIE";
			if (section == 2)
				return "ARTIST MELODIE";
			if (section == 3)
				return "RANK MELODIE";
			if (section == 4)
				return "NR. MELODIILOR";
		}
		return QVariant();
	}
};