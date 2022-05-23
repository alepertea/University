#pragma once
#include "Repository.h"
#include <fstream>

class FileRepo : public Repo
{
private:
	string filename;
	void loadFromFile();
	void storeToFile();
public:
	FileRepo(string filename, double error) : filename{ filename }, Repo(error) { loadFromFile(); }
	~FileRepo() = default;

	void add(const Medicament& m) override;

	void del(const Medicament& m) override;

	void modify(const Medicament& m, int camp) override;

	void meds();
};