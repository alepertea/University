USE PetStore;

-- Dirty reads:
SELECT * FROM Magazin

-- Non-repeatable reads:
SELECT * FROM Magazin
UPDATE Magazin SET numarOrase = 2 WHERE denumire = 'Animal Care'

-- Phantom reads:
SELECT * FROM Magazin
DELETE FROM Magazin WHERE denumire = 'NEW STORE'

-- Deadlock:
INSERT INTO Magazin(denumire, numarOrase) VALUES ('Deadlock Store', 1)
INSERT INTO Manager(idManager, nume, prenume, dataOcuparePost) VALUES (459850, 'Deadlock', 'Manager', '2021-05-17')
SELECT * FROM Magazin
SELECT * FROM Manager

-- Log table:
SELECT * FROM LogTable
DELETE FROM LogTable