#pragma once
#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime 
{
	friend class IteratorMultime;

private:

	/* aici e reprezentarea */

	int cp;			// capacitatea de memorare a celor doi vectori
	int prim, primLiber;
	TElem* e;		// vectorul de elemente
	int* urm;		// vectorul de legaturi
	int* prec;		// vectorul de legaturi

	// furnizeaza un spatiu liber de indice i
	// se sterge primul nod din lista spatiului liber
	int aloca();

	// trece pozitia i in lista spatiului liber
	// se adauga i la inceputul listei spatiului liber
	void dealoca(int i);

	// creeaza un nod in lista
	int creeazaNod(TElem elem);

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	// pastreaza doar elementele care se afla si in multimea b
	void intersectie(const Multime& b);

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};