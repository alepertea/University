#include "ui.h"
#include "Medicament.h"
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

void ConsoleUI::printUI(const vector<Medicament>& meds)
{
	if (meds.size() == 0)
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
	string denumire;

	cout << "Introduceti denumirea: ";
	cin >> denumire;

	const Medicament& med = srv.findMed(denumire);
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

	vector<Medicament> rez;
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

void ConsoleUI::sorteazaUI()
{
	int criteriu;

	cout << "Criterii de sortare:\n";
	cout << "\t 1: dupa denumire \n";
	cout << "\t 2: dupa producator \n";
	cout << "\t 3: dupa substanta + pret \n";
	cout << "Introduceti criteriul: ";
	cin >> criteriu;

	vector<Medicament> meds;

	if (criteriu == 1)
		meds = srv.sortByDenumire();
	if (criteriu == 2)
		meds = srv.sortByProducator();
	if (criteriu == 3)
		meds = srv.sortBySubstantaSiPret();

	if (meds.size() == 0)
		if (criteriu == 1 || criteriu == 2 || criteriu == 3)
			cout << "Nu exista medicamente! \n";
		else
			cout << "Criteriu invalid! \n";
	else
		for (const Medicament& med : meds)
		{
			cout << "Denumire: " << med.getDenumire() << " | ";
			cout << "Producator: " << med.getProducator() << " | ";
			cout << "Pret: " << med.getPret() << " | ";
			cout << "Substanta activa: " << med.getSubstantaActiva() << '\n';
		}
}

void ConsoleUI::randomUI()
{
	int nrMeds;
	cout << "Introduceti numarul de medicamente pe care vreti sa le adaugati: ";
	cin >> nrMeds;

	srv.random(nrMeds);

	cout << "Adaugarea s-a efectuat cu succes! \n";
}

void ConsoleUI::uiExportCSV()
{
	string filename;
	cout << "Introduceti numele fisierului CVS: ";
	cin >> filename;

	srv.exportCSV(filename);
}

void ConsoleUI::uiExportHTML()
{
	string filename;
	cout << "Introduceti numele fisierului HTML: ";
	cin >> filename;

	srv.exportHTML(filename);
}

void ConsoleUI::UndoUI()
{
	srv.undo();
}

void ConsoleUI::retetaUI()
{
	int optiune;
	cout << "\t 1: Adauga medicament in reteta \n";
	cout << "\t 2: Goleste reteta \n";
	cout << "\t 3: Adauga aleator in reteta \n";
	cout << "\t 4: Afiseaza reteta \n";
	cout << "\t 5: Export reteta in fisier CSV \n";
	cout << "\t 6: Export reteta in fisier HTML \n";
	cout << "\t 7: Undo la operatia de adaugare \n";
	cout << "\t 0: Exit \n";
	cout << "Introduceti comanda: ";
	cin >> optiune;

	while (optiune != 0)
	{
		switch (optiune)
		{
		case 0:
		{
			srv.clearAll();
			cout << "Reteta a fost golita! \n";
			break;
		}
		case 1:
		{
			string denumire, producator;
			float pret;
			int substantaActiva;

			cout << "Introduceti denumirea: ";
			cin >> denumire;
			cout << "Introduceti producatorul: ";
			cin >> producator;
			cout << "Introduceti pretul: ";
			cin >> pret;
			cout << "Introduceti cantitatea de substanta activa: ";
			cin >> substantaActiva;

			srv.addReteta(denumire, producator, pret, substantaActiva);

			break;
		}
		case 2:
		{
			srv.clearAll();
			break;
		}
		case 3:
		{
			randomUI();
			break;
		}
		case 4:
		{
			vector<Medicament> rez = srv.getReteta();
			for (const auto& med : rez)
			{
				cout << "Denumire: " << med.getDenumire() << " | ";
				cout << "Producator: " << med.getProducator() << " | ";
				cout << "Pret: " << med.getPret() << " | ";
				cout << "Substanta activa: " << med.getSubstantaActiva() << '\n';
			}

			break;
		}
		case 5:
		{
			uiExportCSV();
			break;
		}
		case 6:
		{
			uiExportHTML();
			break;
		}
		case 7:
		{
			UndoUI();
			break;
		}
		default:
		{
			cout << "Optiune invalida! \n";
			break;
		}
		}

		cout << "Numarul medicamentelor din reteta: " << srv.sizeReteta() << '\n';

		cout << "\t 1: Adauga medicament in reteta \n";
		cout << "\t 2: Goleste reteta \n";
		cout << "\t 3: Adauga aleator in reteta \n";
		cout << "\t 4: Afiseaza reteta \n";
		cout << "\t 5: Export reteta in fisier CVS \n";
		cout << "\t 6: Export reteta in fisier HTML \n";
		cout << "\t 0: Exit \n";
		cout << "Introduceti comanda: ";
		cin >> optiune;
	}
}

void ConsoleUI::statisticaUI()
{
	if (srv.getMeds().size() == 0)
		cout << "Nu exista medicamente pentru statistica! \n";
	else
		cout << "Suma preturilor tuturor medicamentelor este: " << srv.stats() << "\n";
}

int ConsoleUI::start()
{
	cout << "Introduceti una dintre comenzi: \n";
	cout << "1: Adaugare medicament \n2: Afisare medicamente \n3: Modificare medicament \n4: Cautare medicament \n5: Stergere medicament \n6: Filtreaza medicamentele \n7: Sorteaza medicamentele \n8: Reteta \n9: Undo ultima operatie \n10: Statistica \n0: Exit \n";
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
			case 7:
			{
				sorteazaUI();
				break;
			}
			case 8:
			{
				retetaUI();
				break;
			}
			case 9:
			{
				UndoUI();
				break;
			}
			case 10:
			{
				statisticaUI();
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