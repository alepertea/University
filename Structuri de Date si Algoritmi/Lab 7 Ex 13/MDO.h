#pragma once
#include <vector>
#include <utility>

#define NULL_POINTER -1
#define NULL_TCHEIE -999999
#define NULL_TVALOARE -999999

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;

struct Nod
{
	TCheie cheie;
	TValoare* valori;
	int capacitateVector;
	int stanga;
	int dreapta;
};

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO
{
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */

	Nod* nod;
	int capacitate;
	int radacina;
	int dimensiune;
	Relatie rel;
	int primLiber;

	int adauga_rec(int rad, TCheie c, TValoare v);
	int sterge_rec(int rad, TCheie c, TValoare v, bool& gasit);
	void redimensionare();
	int minim(int nod);

public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// gaseste si returneaza cheia maxima a multidictionarului
	// daca multidictionarul este vid, se returneaza NULL_TCHEIE
	TCheie cheieMaxima() const;

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};