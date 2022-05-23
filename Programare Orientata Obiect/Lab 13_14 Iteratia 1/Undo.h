#pragma once
#include "Medicament.h"
#include "Repository.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
private:
	Medicament med;
	VirtualRepo& repo;
public:
	UndoAdauga(VirtualRepo& repo, const Medicament& med) :repo{ repo }, med{ med } {}

	void doUndo() override
	{
		repo.del(med);
	}
};

class UndoSterge : public ActiuneUndo
{
private:
	Medicament med;
	VirtualRepo& repo;
public:
	UndoSterge(VirtualRepo& repo, const Medicament& med) :repo{ repo }, med{ med } {}

	void doUndo() override
	{
		repo.add(med);
	}
};

class UndoModifica : public ActiuneUndo
{
private:
	Medicament medInitial, medModificat;
	VirtualRepo& repo;
public:
	UndoModifica(VirtualRepo& repo, const Medicament& medInitial, const Medicament& medModificat) : repo{ repo }, medInitial{ medInitial }, medModificat{ medModificat } {}

	void doUndo() override
	{
		repo.del(medModificat);
		repo.add(medInitial);
	}
};

class UndoAddReteta : public ActiuneUndo
{
private:
	Reteta& ret;
	Medicament med;
public:
	UndoAddReteta(Reteta& ret, const Medicament& med) : ret{ ret }, med{ med }{}

	void doUndo() override
	{
		ret.stergeInReteta(med);
	}
};
