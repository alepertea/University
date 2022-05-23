#include "ui.h"
#include "Medicament.h"
#include "Lista.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

void ConsoleUI::adaugaUI()
{
	string denumire, producator;
	double pret;
	int substantaActiva;

	cout << "Introduceti denumirea: ";
	cin >> denumire;

	cout << "Introduceti producatorul: ";
	cin >> producator;

	cout << "Introduceti pretul: ";
	cin >> pret;

	cout << "Introduceti cantitatea de substanta activa: ";
	cin >> substantaActiva;

	srv.addMed(denumire, producator, pret, substantaActiva);
}

void ConsoleUI::printUI(const Lista<Medicament>& meds)
{
	Lista<Medicament> medicamente = srv.getMeds();
	if (medicamente.size() == 0)
		cout << "Nu exista medicamente! \n";
	else
	{
		for (const Medicament& med : meds)
		{
			cout << "Denumire: " << med.getDenumire() << " | ";
			cout << "Producator: " << med.getProducator() << " | ";
			cout << "Pret: " << med.getPret() << " | ";
			cout << "Substanta activa: " << med.getSubstantaActiva() << '\n';
		}
	}
}

void ConsoleUI::modificaUI()
{
	string denumire, producator;
	double pret;
	int substantaActiva;
	int camp;

	cout << "Introduceti denumirea: ";
	cin >> denumire;

	cout << "Introduceti producatorul: ";
	cin >> producator;

	cout << "1 - pret \n2 - cantitate de substanta activa \n3 - ambele\n";
	cout << "Introduceti campul pe care doriti sa il modificati: ";
	cin >> camp;

	if (camp == 1)
	{
		cout << "Introduceti pretul: ";
		cin >> pret;
	}
	if (camp == 2)
	{
		cout << "Introduceti cantitatea de substanta activa: ";
		cin >> substantaActiva;
	}
	if (camp == 3)
	{
		cout << "Introduceti pretul: ";
		cin >> pret;
		cout << "Introduceti cantitatea de substanta activa: ";
		cin >> substantaActiva;
	}

	srv.modifyMed(denumire, producator, pret, substantaActiva, camp);
}

void ConsoleUI::cautaUI()
{
	string denumire, producator;

	cout << "Introduceti denumirea: ";
	cin >> denumire;

	cout << "Introduceti producatorul: ";
	cin >> producator;

	const Medicament& med = srv.findMed(denumire, producator);
	cout << "Medicamentul cautat are pretul " << med.getPret() << " si cantitatea de substanta activa " << med.getSubstantaActiva();
}

void ConsoleUI::stergeUI()
{
	string denumire, producator;

	cout << "Introduceti denumirea: ";
	cin >> denumire;

	cout << "Introduceti producatorul: ";
	cin >> producator;

	srv.deleteMed(denumire, producator);
	cout << "Stergerea s-a efectuat cu succes. Apasati tasta 2 pentru a vedea lista de medicamente! \n";
}

void ConsoleUI::filtreazaUI()
{
	int criteriu;

	cout << "Criterii de filtrare:\n";
	cout << "\t 1: dupa pret \n";
	cout << "\t 2: dupa cantitatea de substanta activa \n";
	cout << "Introduceti criteriul: ";
	cin >> criteriu;

	Lista<Medicament> rez;
	if (criteriu == 1)
	{
		int pret;
		cout << "Introduceti pretul: ";
		cin >> pret;
		rez = srv.filterMeds(pret, 10, criteriu);
	}
	if (criteriu == 2)
	{
		int substantaActiva;
		cout << "Introduceti cantitatea de substanta activa: ";
		cin >> substantaActiva;
		rez = srv.filterMeds(10, substantaActiva, criteriu);
	}

	if (rez.size() == 0)
		if (criteriu == 1 || criteriu == 2)
			cout << "Nu s-au gasit medicamente care sa satisfaca conditia data! \n";
		else
			cout << "Criteriu invalid! \n";
	else
		for (const Medicament& med : rez)
		{
			cout << "Denumire: " << med.getDenumire() << " | ";
			cout << "Producator: " << med.getProducator() << " | ";
			cout << "Pret: " << med.getPret() << " | ";
			cout << "Substanta activa: " << med.getSubstantaActiva() << '\n';
		}
}

int ConsoleUI::start()
{
	cout << "Introduceti una dintre comenzi: \n";
	cout << "1: Adaugare medicament \n2: Afisare medicamente \n3: Modificare medicament \n4: Cautare medicament \n5: Stergere medicament \n6: Filtrare medicamente \n0: Exit \n";
	int cmd = 0;
	while (true)
	{
		cout << "\nIntroduceti comanda: ";
		cin >> cmd;
		try
		{
			switch (cmd)
			{
			case 1:
			{
				adaugaUI();
				cout << "Adaugarea s-a efectuat cu succes! \n";
				break;
			}
			case 2:
			{
				printUI(srv.getMeds());
				break;
			}
			case 3:
			{
				modificaUI();
				cout << "Modificarea s-a efectuat cu succes! \n";
				break;
			}
			case 4:
			{
				cautaUI();
				break;
			}
			case 5:
			{
				stergeUI();
				break;
			}
			case 6:
			{
				filtreazaUI();
				break;
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				cout << "Comanda invalida! \n";
				break;
			}
			}
		}
		catch (const ValidateException & erori)
		{
			cout << erori << '\n';
		}
		catch (const RepositoryException & eroare)
		{
			cout << eroare << '\n';
		}
	}
}