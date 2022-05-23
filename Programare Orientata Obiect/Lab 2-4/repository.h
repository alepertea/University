#pragma once

int cauta(char* nume, char* prenume);

int adaugaParticipant(char* nume, char* prenume, int scor);

int afiseazaParticipanti();

int actualizeazaParticipant(char* nume, char* prenume, int scor);

int stergeParticipant(char* nume, char* prenume);

int filtreazaValoare(int valoare);

int filtreazaLitera(char* litera);

int sorteazaCrescatorNume();

int sorteazaDescrescatorNume();

int sorteazaCrescatorScor();

int sorteazaDescrescatorScor();