#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "participant.h"
#include "vectordinamic.h"
#include "service.h"

void testeValidari()
{
	// participant valid
	Participant p1 = creareParticipant("Pertea", "Ale", 23);
	int ok = valideazaParticipant(p1);
	assert(ok == 0);
	distrugeParticipant(&p1);

	// nume invalid
	Participant p2 = creareParticipant("Pertea54", "Ale", 23);
	ok = valideazaParticipant(p2);
	assert(ok == 1);
	distrugeParticipant(&p2);

	Participant p5 = creareParticipant("", "Ale", 23);
	ok = valideazaParticipant(p5);
	assert(ok == 1);
	distrugeParticipant(&p5);

	// prenume invalid
	Participant p3 = creareParticipant("Pertea", "Ale54", 23);
	ok = valideazaParticipant(p3);
	assert(ok == 2);
	distrugeParticipant(&p3);

	Participant p6 = creareParticipant("Pertea", "", 23);
	ok = valideazaParticipant(p6);
	assert(ok == 2);
	distrugeParticipant(&p6);

	// scor invalid
	Participant p4 = creareParticipant("Pertea", "Ale", 243);
	ok = valideazaParticipant(p4);
	assert(ok == 3);
	distrugeParticipant(&p4);
}

void testeDomain()
{
	Participant p = creareParticipant("Gigi", "Becali", 100);
	assert(strcmp(getNume(&p), "Gigi") == 0);
	assert(strcmp(getPrenume(&p), "Becali") == 0);
	assert(getScor(&p) == 100);
	distrugeParticipant(&p);
}

void testCreareVector()
{
	Vector* v = creareVector();
	assert(v->lungime == 0);
	assert(v->capacitate == 10);
	distrugeVector(v);
	free(v);
}

void testAdaugareParticipant(Srv* s)
{
	assert(adaugareParticipant(s, "Pertea", "Ale", 65) == 0);
	// adaugare participant existent
	assert(adaugareParticipant(s, "Pertea", "Ale", 54) == 4);
	// adaugare participant invalid
	assert(adaugareParticipant(s, "Per54", "Ale", 43) == 1);
}

void testActualizareParticipant(Srv* s)
{
	// actualizare participant existent
	assert(actualizareParticipant(s, "Pertea", "Ale", 100) == 0);
	// actualizare participant invalid
	assert(actualizareParticipant(s, " ", "Ioana", 43) == 1);
	// actualizare participant inexistent
	assert(actualizareParticipant(s, "Gica", "Hagi", 54) == 4);
}

void testStergereParticipant(Srv* s)
{
	// stergere participant existent
	assert(stergereParticipant(s, "Pertea", "Ale") == 4);
	// stergere participant invalid
	assert(stergereParticipant(s, "Mor", " ") == 2);
	// stergere participant inexistent
	assert(stergereParticipant(s, "Gica", "Hagi") == 4);
}

void testSortari(Srv* s)
{
	int a = adaugareParticipant(s, "Mihut", "Andreea", 34);
	a = adaugareParticipant(s, "Pop", "Madalina", 69);
	// Sirul va fi de forma [("Mihut", "Andreea", 34), ("Pop", "Madalina", 69)]

	assert(sortareCrescatorNume(s) == 0);
	// Sirul ramane neschimbat
	assert(sortareCrescatorScor(s) == 0);
	// Sirul ramane neschimbat
	assert(sortareDescrescatorNume(s) == 0);
	// Sirul va fi de forma [("Pop", "Madalina", 69), ("Mihut", "Andreea", 34)]
	assert(sortareDescrescatorScor(s) == 0);
	// Sirul va fi de forma [("Pop", "Madalina", 69), ("Mihut", "Andreea", 34)]

	a = adaugareParticipant(s, "Bira", "Elena", 90);
	// Sirul va fi de forma [("Mihut", "Andreea", 34), ("Pop", "Madalina", 69), ("Bira", "Elena", 90)]
	assert(sortareCrescatorNume(s) == 0);
	// Sirul va fi de forma [("Bira", "Elena", 90), ("Mihut", "Andreea", 34), ("Pop", "Madalina", 69)]
	assert(sortareCrescatorScor(s) == 0);
	// Sirul va reveni la forma [("Mihut", "Andreea", 34), ("Pop", "Madalina", 69), ("Bira", "Elena", 90)]
	assert(sortareDescrescatorNume(s) == 0);
	// Sirul va fi de forma [("Pop", "Madalina", 69), ("Mihut", "Andreea", 34), ("Bira", "Elena", 90)]
	assert(sortareDescrescatorScor(s) == 0);
	// Sirul va fi de forma [("Bira", "Elena", 90),("Pop", "Madalina", 69), ("Mihut", "Andreea", 34)]

}

void testFiltrareDupaValoare(Srv* s)
{
	assert(filtrareValoare(s, 50) == 0);
	assert(filtrareValoare(s, 10) == 1);
}

void testFiltrareDupaLitera(Srv* s)
{
	assert(filtrareLitera(s, "B") == 0);
	assert(filtrareLitera(s, "S") == 1);
}

void testAfisare(Srv* s)
{
	assert(afisareParticipanti(s) == 0);
}

void runTeste(Srv* s)
{
	testeDomain();
	testeValidari();
	testCreareVector();
	testAdaugareParticipant(s);
	testActualizareParticipant(s);
	testStergereParticipant(s);
	testSortari(s);
	testFiltrareDupaValoare(s);
	testFiltrareDupaLitera(s);
	testAfisare(s);
}
