CREATE DATABASE PetStore;
use PetStore;

CREATE TABLE Magazin
(
	idMagazin INT PRIMARY KEY IDENTITY(1000, 5),
	denumire VARCHAR(50) NOT NULL,
	numarOrase INT NOT NULL
)

CREATE TABLE EvidentaContabila
(
	idEvidenta INT IDENTITY(5000, 10),
	idMagazin INT,
	dataEvidenta DATE NOT NULL,
	CONSTRAINT FK_EvidentaContabilaMagazin FOREIGN KEY(idMagazin) REFERENCES Magazin(idMagazin)
	ON DELETE CASCADE
	ON UPDATE CASCADE,
	CONSTRAINT PK_EvidentaContabila PRIMARY KEY(idEvidenta)
)

CREATE TABLE Adresa
(
	idAdresa INT,
	CONSTRAINT FK_Adresa FOREIGN KEY(idAdresa) REFERENCES Magazin(idMagazin),
	judet VARCHAR(50) NOT NULL,
	localitate VARCHAR(50) NOT NULL,
	strada VARCHAR(100) NOT NULL,
	numar INT NOT NULL,
	CONSTRAINT PK_Adresa PRIMARY KEY(idAdresa)
)

CREATE TABLE Angajat
(
	idAngajat INT IDENTITY,
	idMagazin INT,
	nume VARCHAR(50) NOT NULL,
	prenume VARCHAR(100) NOT NULL,
	dataNasterii DATE NOT NULL,
	observatii VARCHAR(100),
	CONSTRAINT PK_Angajat PRIMARY KEY(idAngajat),
	CONSTRAINT FK_Magazin FOREIGN KEY(idMagazin) REFERENCES Magazin(idMagazin)
	ON DELETE CASCADE
	ON UPDATE CASCADE
)

CREATE TABLE Manager
(
	idManager INT,
	nume VARCHAR(50) NOT NULL,
	prenume VARCHAR(100) NOT NULL,
	dataOcuparePost DATE NOT NULL,
	CONSTRAINT FK_Manager FOREIGN KEY(idManager) REFERENCES Magazin(idMagazin)
	ON DELETE CASCADE
	ON UPDATE CASCADE,
	CONSTRAINT PK_Manager PRIMARY KEY(idManager)
)

CREATE TABLE Continent
(
	idContinent INT IDENTITY,
	denumire VARCHAR(50),
	CONSTRAINT CK_NumeContinent CHECK(denumire IN ('Asia', 'Africa', 'America de Nord', 'America de Sud', 'Antarctica', 'Australia', 'Europa')),
	CONSTRAINT PK_Continent PRIMARY KEY(idContinent)
)

CREATE TABLE Grupa
(
	idGrupa INT IDENTITY,
	descriere VARCHAR(100) NOT NULL,
	modDeplasare VARCHAR(100),
	CONSTRAINT CK_Grupa CHECK(descriere IN ('Insecte', 'Pesti', 'Amfibieni', 'Reptile', 'Pasari', 'Mamifere')),
	CONSTRAINT PK_Grupa PRIMARY KEY(idGrupa)
)

CREATE TABLE Specie
(
	idSpecie INT IDENTITY,
	idGrupa INT,
	denumire VARCHAR(100) NOT NULL,
	idContinent INT,
	hrana VARCHAR(50),
	CONSTRAINT CK_Hrana CHECK(hrana IN ('carnivor', 'ierbivor', 'omnivor')),
	CONSTRAINT FK_SpecieGrupa FOREIGN KEY(idGrupa) REFERENCES Grupa(idGrupa)
	ON DELETE CASCADE
	ON UPDATE CASCADE,
	CONSTRAINT FK_SpecieContinent FOREIGN KEY(idContinent) REFERENCES Continent(idContinent)
	ON DELETE CASCADE
	ON UPDATE CASCADE,
	CONSTRAINT PK_Specie PRIMARY KEY(idSpecie)
)

CREATE TABLE Animal
(
	idAnimal INT IDENTITY,
	idGrupa INT,
	denumire VARCHAR(100) NOT NULL,
	pret INT NOT NULL,
	descriere VARCHAR(100),
	CONSTRAINT CK_Pret CHECK(pret > 0),
	CONSTRAINT PK_Animal PRIMARY KEY(idAnimal),
	CONSTRAINT FK_AnimalGrupa FOREIGN KEY(idGrupa) REFERENCES Grupa(idGrupa)
	ON DELETE CASCADE
	ON UPDATE CASCADE
)

CREATE TABLE PetStore
(
	idMagazin INT,
	idAnimal INT,
	CONSTRAINT FK_MagazinPetStore FOREIGN KEY(idMagazin) REFERENCES Magazin(idMagazin),
	CONSTRAINT FK_AnimalPetStore FOREIGN KEY(idAnimal) REFERENCES Animal(idAnimal),
	CONSTRAINT PK_PetStore PRIMARY KEY(idMagazin, idAnimal)
)