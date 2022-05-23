INSERT INTO Tables(Name) VALUES
('Magazin'), ('Angajat'), ('PetStore')

go
CREATE VIEW View_1 AS
SELECT denumire FROM Magazin

go
CREATE VIEW View_2 AS
SELECT DISTINCT Mag.denumire AS Magazin, E.dataEvidenta AS [Data evidenta]
FROM Magazin Mag, EvidentaContabila E
WHERE Mag.idMagazin = E.idMagazin AND DATEDIFF(year, E.dataEvidenta, CURRENT_TIMESTAMP) < 1

go
CREATE VIEW View_3 AS
SELECT M.denumire AS Magazin, COUNT(A.idAngajat) AS [Numar angajati]
FROM Magazin M, Angajat A
WHERE A.idMagazin = M.idMagazin
GROUP BY M.denumire
go

INSERT INTO Views(Name) VALUES
('View_1'), ('View_2'), ('View_3')

INSERT INTO Tests(Name) VALUES
('Deletion'), ('Insertion'), ('Evaluation')

INSERT INTO TestViews(TestID, ViewID) VALUES
(3, 4), (3, 5), (3, 6)

INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
(1, 6, 100, 1), (1, 5, 100, 2), (1, 4, 100, 3)

INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
(2, 4, 100, 1), (2, 5, 100, 2), (2, 6, 100, 3)

--- Procedura stocata Insertion
go
CREATE PROCEDURE Insertion
(@noOfRows INT, @position INT)
AS
BEGIN
	DECLARE @currentIndex INT
	SET @currentIndex = 1

	DECLARE @storeNumber INT, @idMagazin INT, @idAnimal INT
	SET @storeNumber = 1
	SET @idAnimal = (SELECT MIN(idAnimal) FROM Animal)

	DECLARE @denumire VARCHAR(50), @numarOrase INT, @nume VARCHAR(50), @prenume VARCHAR(100)

	WHILE @currentIndex <= @noOfRows
	BEGIN

		IF @position = 1
		BEGIN

			SET @denumire = CONCAT('Magazin ', @storeNumber)
			SET @numarOrase = RAND() * (20 - 2) + 2

			INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumire, @numarOrase)

			SET @idMagazin = (SELECT MAX(idMagazin) FROM Magazin)
			INSERT INTO EvidentaContabila(idMagazin, dataEvidenta) VALUES (@idMagazin, GETDATE())

			SET @storeNumber = @storeNumber + 1

		END

		IF @position = 2
		BEGIN
			
			SET @denumire = CONCAT('Magazin ', @storeNumber)
			SET @numarOrase = RAND() * (20 - 2) + 2

			INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumire, @numarOrase)

			SET @idMagazin = (SELECT MAX(idMagazin) FROM Magazin)

			INSERT INTO EvidentaContabila(idMagazin, dataEvidenta) VALUES (@idMagazin, GETDATE())

			SET @nume = CONCAT('Nume ', @storeNumber)
			SET @prenume = CONCAT('Prenume ', @storeNumber)

			INSERT INTO Angajat(idMagazin, nume, prenume, dataNasterii) VALUES (@idMagazin, @nume, @prenume, GETDATE())

		END

		IF @position = 3
		BEGIN

			DECLARE @denumireMagazin VARCHAR(50), @nrOrase INT
			SET @denumireMagazin = CONCAT('Magazin ', @storeNumber)
			SET @nrOrase = RAND() * (20 - 2) + 2

			INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumireMagazin, @nrOrase)

			SET @storeNumber = @storeNumber + 1

			SET @idMagazin = (SELECT MAX(idMagazin) FROM Magazin)

			INSERT INTO EvidentaContabila(idMagazin, dataEvidenta) VALUES (@idMagazin, GETDATE())

			INSERT INTO PetStore(idMagazin, idAnimal) VALUES (@idMagazin, @idAnimal)

		END

		SET @currentIndex = @currentIndex + 1

	END
END

EXECUTE Insertion 2, 1

SELECT * FROM Magazin

go
CREATE PROCEDURE Deletion
(@noOfRows INT, @position INT)
AS
BEGIN
	DECLARE @currentIndex INT
	SET @currentIndex = 1

	DECLARE @idMagazin INT, @idAngajat INT, @idPetStore INT

	SET @idMagazin = (SELECT MIN(idMagazin) FROM Magazin)
	SET @idAngajat = (SELECT MIN(idAngajat) FROM Angajat)

	WHILE @currentIndex <= @noOfRows
	BEGIN

		IF @position = 1
		BEGIN
			DELETE FROM PetStore WHERE idMagazin = @idMagazin
			SET @idMagazin = (SELECT MIN(idMagazin) FROM PetStore)
		END

		IF @position = 2
		BEGIN
			DELETE FROM Angajat WHERE idAngajat = @idAngajat
			SET @idAngajat = (SELECT MIN(idAngajat) FROM Angajat)
		END

		IF @position = 3
		BEGIN
			DELETE FROM Angajat WHERE idMagazin = @idMagazin
			DELETE FROM PetStore WHERE idMagazin = @idMagazin
			DELETE FROM EvidentaContabila WHERE idMagazin = @idMagazin
			DELETE FROM Magazin WHERE idMagazin = @idMagazin
			SET @idMagazin = (SELECT MIN(idMagazin) FROM Magazin)
		END

		SET @currentIndex = @currentIndex + 1

	END
END

go
CREATE PROCEDURE Evaluation
(@noOfView VARCHAR(10))
AS
BEGIN

	IF @noOfView NOT IN ('4', '5', '6')
	BEGIN
		PRINT 'Incorrect number of view!'
		RETURN
	END

	IF @noOfView = 4
		SELECT * FROM View_1
	
	IF @noOfView = 5 
		SELECT * FROM View_2
		
	IF @noOfView = 6
		SELECT * FROM View_3

END

DROP PROCEDURE Evaluation

go
CREATE PROCEDURE MainProcedure
(@tableID VARCHAR(10))
AS
BEGIN
		
	IF @tableID NOT IN ('4', '5', '6')
	BEGIN
		PRINT 'Invalid table ID!'
		RETURN
	END

	SET @tableID = CONVERT(INT, @tableID)

	DECLARE @startTime DATETIME, @intermediateTime DATETIME, @endTime DATETIME
	DECLARE @table VARCHAR(50), @test VARCHAR(50)

	DECLARE @noOfRows INT, @position INT, @testID INT

	SET @table = (SELECT Name FROM Tables WHERE TableID = @tableID)

	--- Start of tests:
	SET @startTime = GETDATE()

	--- Deletion:
	SET @test = (SELECT Name FROM Tests 
				INNER JOIN TestTables ON Tests.TestID = TestTables.TestID 
				WHERE TestTables.TableID = @tableID AND TestTables.TestID = 1)
	SET @noOfRows = (SELECT NoOfRows FROM TestTables 
					WHERE TestTables.TestID = 1 AND TestTables.TableID = @tableID)
	SET @position = (SELECT Position FROM TestTables 
					WHERE TestTables.TestID = 1 AND TestTables.TableID = @tableID)

	EXECUTE @test @noOfRows, @position

	--- Insertion:
	SET @test = (SELECT Name FROM Tests 
				INNER JOIN TestTables ON Tests.TestID = TestTables.TestID 
				WHERE TestTables.TableID = @tableID AND TestTables.TestID = 2)
	SET @noOfRows = (SELECT NoOfRows FROM TestTables
					WHERE TestTables.TestID = 2 AND TestTables.TableID = @tableID)
	SET @position = (SELECT Position FROM TestTables 
					WHERE TestTables.TestID = 2 AND TestTables.TableID = @tableID)

	EXECUTE @test @noOfRows, @position

	SET @intermediateTime = GETDATE()

	--- Evaluation:
	SET @test = (SELECT Name FROM Tests 
				INNER JOIN TestViews ON Tests.TestID = TestViews.TestID 
				WHERE TestViews.ViewID = @tableID AND TestViews.TestID = 3)

	EXECUTE @test @tableID

	--- Finish:
	SET @endTime = GETDATE()

	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (CONVERT(VARCHAR, @noOfRows) + ' modified rows on table ' + @table, @startTime, @endTime)
	SET @testID = (SELECT MAX(TestRunID) FROM TestRuns)

	INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@testID, @tableID, @startTime, @intermediateTime)
	INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@testID, @tableID, @intermediateTime, @endTime)

END

DROP PROCEDURE Evaluation

SELECT * FROM Tables
SELECT * FROM Tests
SELECT * FROM TestTables
SELECT * FROM TestViews
SELECT * FROM Views
SELECT * FROM EvidentaContabila
SELECT * FROM Magazin
SELECT * FROM Angajat
SELECT * FROM PetStore
SELECT * FROM TestRunTables
SELECT * FROM TestRuns
SELECT * FROM TestRunViews

INSERT INTO Views(Name) VALUES ('View_1'), ('View_2'), ('View_3')
INSERT INTO TestViews(TestID, ViewID) VALUES
(3, 4), (3, 5), (3, 6)
DELETE FROM TestViews WHERE ViewID <= 3
DELETE FROM Views WHERE ViewID <= 3

DELETE FROM Adresa
DELETE FROM Manager
DELETE FROM EvidentaContabila
DELETE FROM Magazin WHERE idMagazin >= 1030

EXECUTE MainProcedure 4