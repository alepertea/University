#include <stdio.h>
#include "repository.h"
#include "domain.h"
#include "validari.h"
#include <assert.h>

void testeSortari()
{
	adaugaParticipant("Mihut", "Andreea", 34);
	adaugaParticipant("Pop", "Madalina", 69);
	// Sirul va fi de forma [("Mihut", "Andreea", 34), ("Pop", "Madalina", 69)]

	assert(sorteazaCrescatorNume() == 1);
	assert(sorteazaCrescatorScor() == 1);
	// Sirul ramane de forma [("Mihut", "Andreea", 34), ("Pop", "Madalina", 69)]
	assert(sorteazaDescrescatorNume() == 0);
	// Sirul va fi de forma [("Pop", "Madalina", 69), ("Mihut", "Andreea", 34)]
	assert(sorteazaDescrescatorScor() == 1);
	// Sirul ramane de forma [("Pop", "Madalina", 69), ("Mihut", "Andreea", 34)]

	stergeParticipant("Pop", "Madalina");
	adaugaParticipant("Bira", "Elena", 90);
	// Sirul va fi de forma [("Mihut", "Andreea", 34), ("Bira", "Elena", 90)]

	assert(sorteazaCrescatorNume() == 0);
	// Sirul va fi de forma [("Bira", "Elena", 90), ("Mihut", "Andreea", 34)]
	assert(sorteazaCrescatorScor() == 0);
	// Sirul va reveni la forma [("Mihut", "Andreea", 34), ("Bira", "Elena", 90)]
	assert(sorteazaDescrescatorNume() == 1);
	// Sirul ramane de forma [("Mihut", "Andreea", 34), ("Bira", "Elena", 90)]
	assert(sorteazaDescrescatorScor() == 0);
	// Sirul va reveni la forma [("Bira", "Elena", 90), ("Mihut", "Andreea", 34)]
	
	stergeParticipant("Bira", "Elena");
	stergeParticipant("Mihut", "Andreea");
}

void testAfisareParticipanti()
{
	adaugaParticipant("Mihut", "Andreea", 34);
	assert(afiseazaParticipanti() == 0);

	stergeParticipant("Mihut", "Andreea");
	assert(afiseazaParticipanti() == 1);
}

void testFiltrareLitera()
{
	adaugaParticipant("Mihut", "Andreea", 34);
	assert(filtreazaLitera("M") == 0);
	assert(filtreazaLitera("A") == 1);

	stergeParticipant("Mihut", "Andreea");
}

void testFiltrareValoare()
{
	adaugaParticipant("Pop", "Ilinca", 43);
	assert(filtreazaValoare(50) == 0);
	assert(filtreazaValoare(40) == 1);

	stergeParticipant("Pop", "Ilinca");
}

void testStergereParticipant()
{
	// Sirul este vid, deci nu o sa gaseasca participant
	assert(stergeParticipant("Gigel", "Gigela") == 1);

	// Adaugam participantul pentru a-l putea sterge
	adaugaParticipant("Gigel", "Gigela", 40);
	adaugaParticipant("Mor", "Costela", 20);
	assert(stergeParticipant("Gigel", "Gigela") == 0);
	assert(stergeParticipant("Mor", "Costela") == 0);
}

void testActualizareParticipant()
{
	adaugaParticipant("Ionescu", "Razvan", 90);
	assert(actualizeazaParticipant("Ionescu", "Razvan", 78) == 0);
	assert(actualizeazaParticipant("Pop", "Angela", 14) == 1);

	stergeParticipant("Ionescu", "Razvan");
}

void testCautare()
{
	adaugaParticipant("Ana", "Maria", 12);
	// Participantul se afla pe prima pozitie
	assert(cauta("Ana", "Maria") == 1);

	// Participantul nu se afla in sir
	assert(cauta("Ana", "Ioana") == 0);

	stergeParticipant("Ana", "Maria");
}

void testValidareParticipant()
{
	// Date valide:
	assert(validareParticipant("Pertea", "Alexandra", 67) == 0);

	// Nume invalid:
	assert(validareParticipant("", "Elena", 30) == 1);
	assert(validareParticipant(" ", "George", 56) == 1);
	assert(validareParticipant("Popescu34", "Alin", 10) == 1);

	// Prenume invalid:
	assert(validareParticipant("Stoican", "", 23) == 2);
	assert(validareParticipant("Chis", " ", 38) == 2);
	assert(validareParticipant("Tarta", "Geor54ge", 38) == 2);

	// Scor invalid:
	assert(validareParticipant("Pop", "Gigel", 1) == 3);
	assert(validareParticipant("Stan", "Iulia", 120) == 3);
}

void testAdaugaParticipant()
{
	assert(len == 0);

	assert(adaugaParticipant("Ana", "Maria", 12) == 0);

	// Readaugam participantul
	assert(adaugaParticipant("Ana", "Maria", 12) == 1);

	stergeParticipant("Ana", "Maria");
}

void runAllTests()
{
	testAdaugaParticipant();
	testValidareParticipant();
	testAfisareParticipanti();
	testCautare();
	testActualizareParticipant();
	testStergereParticipant();
	testFiltrareValoare();
	testFiltrareLitera();
	testeSortari();
}