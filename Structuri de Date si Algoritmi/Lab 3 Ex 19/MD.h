#pragma once
#include<vector>
#include<utility>

#define NULL_TCHEIE 0

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	struct TLista
	{
		TValoare val;
		TLista* urm;
	};

	struct TNod
	{
		pair<TCheie, TLista*> info;
		TNod* urm;
	};

	TNod* prim;

	// returneaza true daca lista de valori asociata unei chei este vida
	bool listaVida(TCheie c) const;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// gaseste si returneaza cheia maxima a multidictionarului
	// Daca multidictionarul este vid, se returneaza NULL_TCHEIE
	TCheie cheieMaxima() const;

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();
};
