#include "Teste.h"

void Test::testEntity()
{
	Melodie m{ 1, "Stigmata", "Grandson", 10 };
	assert(m.getID() == 1);
	assert(m.getTitlu() == "Stigmata");
	assert(m.getArtist() == "Grandson");
	assert(m.getRank() == 10);

	m.setRank(5);
	assert(m.getRank() == 5);
	m.setTitle("KissBang");
	assert(m.getTitlu() == "KissBang");
}

void Test::testModificare()
{
	Repo r{ "test.txt" };
	Service s{ r };

	Melodie m{ 1, "Stigmata", "Grandson", 4 };
	r.add(m);

	try
	{
		s.modifySong(1, "", 5);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}

	try
	{
		s.modifySong(1, "Lol", 7);
		Melodie mel = r.getAll()[0];
		assert(mel.getTitlu() == "Lol");
		assert(mel.getRank() == 7);
	}
	catch (exception&)
	{
		assert(false);
	}

	ofstream f("test.txt");
	f.clear();
	f.close();
}

void Test::runTests()
{
	this->testEntity();
	this->testModificare();
}
