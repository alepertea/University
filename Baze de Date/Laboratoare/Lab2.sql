USE PetStore;

-- CONTINENT:
INSERT INTO Continent(denumire) VALUES
('Asia'), ('Africa'), ('America de Nord'), ('America de Sud'), ('Antarctica'), ('Australia'), ('Europa')

-- GRUPA:
INSERT INTO Grupa(descriere, modDeplasare) VALUES
('Insecte', 'zbor'), ('Pesti', 'inot'), ('Amfibieni', 'sarit'), ('Reptile', 'tarat'), ('Pasari', 'zbor'), ('Mamifere', 'mers')

-- MAGAZIN:
INSERT INTO Magazin(denumire, numarOrase) VALUES
('Biopet', 1), ('Minerva PET', 5), ('Royal Pet Shop', 10), ('ZooMania', 5), ('Zoo Center', 8), ('Pet Life', 2)

-- ADRESA:
INSERT INTO Adresa(idAdresa, judet, localitate, strada, numar) VALUES
(459740, 'Bucuresti', 'Bucuresti', 'Bd Theodor Pallady', 319), (459745, 'Bucuresti', 'Bucuresti', 'Sperantei', 5), 
(459750, 'Cluj', 'Cluj-Napoca', 'Bd 21 Decembrie 1989', 131), (459755, 'Cluj', 'Cluj-Napoca', 'Alexandru Vaida Voievod', 53), 
(459760, 'Bistrita-Nasaud', 'Bistrita', 'Calea Moldovei', 13), (459765, 'Cluj', 'Cluj-Napoca', 'Calea Dorobantilor', 99)

-- MANAGER:
INSERT INTO Manager(idManager, nume, prenume, dataOcuparePost) VALUES
(459740, 'Pop', 'Amelia', '10-02-2018'), (459745, 'Dumitru', 'Eliza', '02-15-2019'), (459750, 'Vultur', 'Denis', '01-10-2020'), 
(459755, 'Jucan', 'Sanziana', '09-29-2005'), (459760, 'Varduca', 'Tania', '07-02-2019'), (459765, 'Maris', 'Paula', '04-25-2020')

-- EVIDENTA CONTABILA:
INSERT INTO EvidentaContabila(idMagazin, dataEvidenta) VALUES
(459740, '01-01-2020'), (459740, '05-02-2020'), (459740, '12-02-2019'),
(459745, '06-29-2020'), (459745, '05-02-2020'), (459745, '07-24-2019'),
(459750, '02-02-2018'), (459750, '12-12-2019'), (459750, '12-02-2019'),
(459755, '07-20-2019'), (459755, '01-01-2020'), (459755, '04-10-2020'),
(459760, '03-01-2020'), (459760, '08-29-2019'), (459760, '10-20-2018'),
(459765, '08-29-2019'), (459765, '09-15-2018'), (459765, '03-27-2018')

-- ANGAJAT:
INSERT INTO Angajat(idMagazin, nume, prenume, dataNasterii, observatii) VALUES
(459740, 'Geta', 'Iulia', '01-27-1998', ''), (459740, 'Mihut', 'Madalina', '05-12-2000', 'A lucrat ore suplimentare'), (459740, 'Dulca', 'Francesca', '02-12-1999', ''),
(459745, 'Nemes', 'Andrei', '10-09-2000', ''), (459745, 'Pop', 'Ionel', '02-07-1989', 'A lucrat ore suplimentare'), (459745, 'Font', 'Dragos', '11-03-1990', 'A lucrat ore suplimentare'),
(459745, 'Stan', 'Alexandra', '10-05-1994', ''), (459750, 'Utiu', 'Claudiu', '01-18-1996', 'A absentat des'), (459750, 'Pop', 'Alexandra', '05-05-1999', ''),
(459755, 'Jucan', 'Sanziana', '02-28-2000', ''), (459755, 'Timis', 'Ioana', '01-01-1999', ''), (459760, 'Popescu', 'Marcel', '10-29-1998', ''),
(459765, 'Moisescu', 'Andrei', '07-20-1996', 'A lucrat ore suplimentare'), (459765, 'Pop', 'Ana', '01-05-2000', ''), (459765, 'Bele', 'Dan', '06-06-1999', '')


-- ANIMAL:
INSERT INTO Animal(idGrupa, denumire, pret, descriere) VALUES
(13, 'Suri alpaca', 1500, 'Rasa rara de alpaca'), (13, 'Huacaya alpaca', 1000, ''), (13, 'Poodle', 350, 'Traieste intre 12-15 ani'), 
(12, 'Motata olandeza', 100, ''), (12, 'Rata polara', 2599, 'Protejata de lege'), (13, 'Newfoundland', 500, ''), (13, 'Beagle', 250, ''),
(10, 'Triton', 250, ''), (11, 'Testoasa terestra', 100, ''), (11, 'Testoasa marina', 200, ''), (10, 'Olm', 500, ''),
(12, 'Cacadu', 450, ''), (9, 'Caras auriu', 50, ''), (9, 'Peste siamez', 100, ''), (8, 'Blue mormon', 300, ''), (8, 'Coada randunicii', 250, '')

-- SPECIE:
INSERT INTO Specie(idGrupa, denumire, idContinent, hrana) VALUES
(8, 'Fluture', 7, 'ierbivor'), (9, 'Caras', 1, 'omnivor'), (9, 'Betta', 1, 'carnivor'), (13, 'Alpaca', 4, 'ierbivor'),
(13, 'Lup', 7, 'carnivor'), (12, 'Gaina', 1, 'ierbivor'), (12, 'Rata', 6, 'omnivor'), (10, 'Salamandra', 2, 'carnivor'),
(11, 'Testoasa', 1, 'ierbivor'), (12, 'Papagal', 6, 'omnivor')

-- PET STORE:
INSERT INTO PetStore(idMagazin, idAnimal) VALUES
(459740, 1), (459740, 2), (459740, 3), (459740, 4), (459740, 5), (459740, 6), (459740, 7), (459740, 8), (459740, 9), (459740, 10), (459740, 11), (459740, 12), (459740, 13), (459740, 14), (459740, 15), (459740, 16),
(459745, 1), (459745, 2), (459745, 3), (459745, 5), (459745, 6), (459745, 7), (459745, 8), (459745, 9), (459745, 10), (459745, 11), (459745, 12), (459745, 13), (459745, 15), (459745, 16),
(459750, 1), (459750, 2), (459750, 3), (459750, 4), (459750, 5), (459750, 6), (459750, 7), (459750, 8), (459750, 9), (459750, 10), (459750, 11), (459750, 12), (459750, 13), (459750, 14), (459750, 15), (459750, 16),
(459755, 2), (459755, 3), (459755, 4), (459755, 5), (459755, 7), (459755, 8), (459755, 9), (459755, 10), (459755, 11), (459755, 12), (459755, 13), (459755, 14), (459755, 15), (459755, 16),
(459760, 1), (459760, 2), (459760, 3), (459760, 4), (459760, 5), (459760, 6), (459760, 7), (459760, 14), (459760, 15), (459760, 16),
(459765, 1), (459765, 2), (459765, 3), (459765, 4), (459765, 5), (459765, 6), (459765, 7), (459765, 8), (459765, 9), (459765, 10), (459765, 11), (459765, 12), (459765, 13), (459765, 14), (459765, 15),(459765, 16)


-- INTEROGARI:

--1. Afiseaza angajatii care au numele incepand cu litera P, magazinele si adresele unde lucreaza
SELECT A.nume AS Nume, A.prenume AS Prenume, A.dataNasterii AS [Data nasterii], Mag.denumire AS Magazin, Adr.localitate AS [Localitate]
FROM Angajat A, Magazin Mag, Adresa Adr
WHERE Mag.idMagazin = A.idMagazin AND Mag.idMagazin = Adr.idAdresa AND A.nume LIKE 'P%'

--2. Afiseaza animalele si pretul lor, impreuna cu grupa si specia din care fac parte
SELECT A.denumire AS Animal, A.pret AS Pret, S.denumire AS Specie, G.descriere AS Grupa
FROM Animal A, Grupa G, Specie S
WHERE A.idGrupa = G.idGrupa AND G.idGrupa = S.idGrupa;

--3. Afiseaza numarul de angajati de la fiecare magazin
SELECT M.denumire AS Magazin, COUNT(A.idAngajat) AS [Numar angajati]
FROM Magazin M, Angajat A
WHERE A.idMagazin = M.idMagazin
GROUP BY M.denumire

--4. Afiseaza magazinele care au suma totala a preturilor mai mare decat 7000
SELECT M.denumire AS Magazin, SUM(A.pret) AS [Pret total] FROM Magazin M 
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal
GROUP BY M.denumire
HAVING SUM(A.pret) > 7000

--5. Afiseaza magazinele si cate pasari au, daca suma preturilor lor e mai mare decat 2500
SELECT M.denumire AS Magazin, COUNT(A.denumire) AS [Numar pasari], SUM(A.pret) AS [Pret total] FROM Magazin M 
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal
INNER JOIN Grupa G ON A.idGrupa = G.idGrupa
WHERE G.descriere = 'Pasari'
GROUP BY M.denumire
HAVING SUM(A.pret) > 2500

--6. Afiseaza judetele, o singura data, care au magazine cu exact 5 mamifere
SELECT DISTINCT A.judet AS Judet FROM Adresa A
WHERE A.idAdresa IN 
(
SELECT M.idMagazin FROM Magazin M
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal
INNER JOIN Grupa G ON A.idGrupa = G.idGrupa
WHERE G.descriere = 'Mamifere'
GROUP BY M.idMagazin
HAVING COUNT(A.idGrupa) = 5
)

--7. Afiseaza magazinele si managerii, care au cel putin o evidenta contabila mai veche de un an
SELECT DISTINCT Mag.denumire AS Magazin, Man.nume AS [Nume manager], Man.prenume AS [Prenume manager]
FROM Magazin Mag, Manager Man, EvidentaContabila E
WHERE Mag.idMagazin = Man.idManager AND Mag.idMagazin = E.idMagazin AND DATEDIFF(year, E.dataEvidenta, CURRENT_TIMESTAMP) > 1

--8. Afiseaza animalele ierbivore, grupele din care fac parte si continentele de unde provin
SELECT S.denumire AS Animal, G.descriere AS Grupa, C.denumire AS Continent
FROM Specie S, Grupa G, Continent C
WHERE S.idContinent = C.idContinent AND S.idGrupa = G.idGrupa AND S.hrana = 'ierbivor'

--9. Afiseaza managerii care sunt pe post de mai putin de 2 ani, impreuna cu magazin si cu numarul de angajati
SELECT Man.nume AS Nume, Man.prenume AS Prenume, Mag.denumire AS Magazin, COUNT(A.idAngajat) AS [Numar angajati]
FROM Magazin Mag, Manager Man, Angajat A
WHERE Mag.idMagazin = Man.idManager AND A.idMagazin = Mag.idMagazin AND DATEDIFF(year, Man.dataOcuparePost, CURRENT_TIMESTAMP) < 2
GROUP BY Man.nume, Man.prenume, Mag.denumire

--10. Afiseaza magazinele si toate animalele
SELECT M.denumire AS Magazin, A.denumire AS Animal FROM Magazin M 
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal

SELECT * FROM Versiune
EXECUTE Main '1'