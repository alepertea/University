CREATE PROCEDURE Direct_1
AS
BEGIN
	ALTER TABLE Adresa
	ALTER COLUMN numar VARCHAR(100)

	UPDATE Versiune
	SET numarVersiune = 2
END

CREATE PROCEDURE Undo_1
AS
BEGIN
	ALTER TABLE Adresa
	ALTER COLUMN numar int

	UPDATE Versiune
	SET numarVersiune = 1
END

CREATE PROCEDURE Direct_2
AS
BEGIN
	ALTER TABLE Manager
	ADD CONSTRAINT DF_Data DEFAULT GETDATE() FOR dataOcuparePost

	UPDATE Versiune
	SET numarVersiune = 3
END

CREATE PROCEDURE Undo_2
AS
BEGIN
	ALTER TABLE Manager
	DROP CONSTRAINT DF_Data

	UPDATE Versiune
	SET numarVersiune = 2
END

CREATE PROCEDURE Direct_3
AS
BEGIN
	CREATE TABLE Tara
	(
		idTara INT PRIMARY KEY,
		idContinent INT,
		denumire VARCHAR(100)
	)

	UPDATE Versiune
	SET numarVersiune = 4
END

CREATE PROCEDURE Undo_3
AS
BEGIN
	DROP TABLE Tara
	UPDATE Versiune
	SET numarVersiune = 3
END

CREATE PROCEDURE Direct_4
AS
BEGIN
	ALTER TABLE Tara
	ADD numarOrase INT

	UPDATE Versiune
	SET numarVersiune = 5
END

CREATE PROCEDURE Undo_4
AS
BEGIN
	ALTER TABLE Tara
	DROP COLUMN numarOrase

	UPDATE Versiune
	SET numarVersiune = 4
END

CREATE PROCEDURE Direct_5
AS
BEGIN
	ALTER TABLE Tara
	ADD CONSTRAINT FK_Continent FOREIGN KEY(idContinent) REFERENCES Continent(idContinent)

	UPDATE Versiune
	SET numarVersiune = 6
END

CREATE PROCEDURE Undo_5
AS
BEGIN
	ALTER TABLE Tara
	DROP CONSTRAINT FK_Continent

	UPDATE Versiune
	SET numarVersiune = 5
END

CREATE PROCEDURE Main
@input VARCHAR(10)
AS
BEGIN
	DECLARE @versiuneCurenta INT
	SET @versiuneCurenta = (SELECT numarVersiune FROM Versiune)

	IF @input NOT IN ('1','2','3','4','5','6')
	BEGIN
		PRINT 'Versiune invalida!'
		RETURN
	END

	DECLARE @versiune INT
	SET @versiune = CONVERT(INT, @input)

	DECLARE @Rezultat VARCHAR(10)
	WHILE @versiune > @versiuneCurenta
	BEGIN
		SET @Rezultat = CONCAT('Direct_', @versiuneCurenta)
		EXECUTE @Rezultat
		PRINT 'Executing ' + @Rezultat
		SET @versiuneCurenta = (SELECT numarVersiune FROM Versiune)
	END

	WHILE @versiune < @versiuneCurenta
	BEGIN
		SET @versiuneCurenta = @versiuneCurenta - 1
		SET @Rezultat = CONCAT('Undo_', @versiuneCurenta)
		EXECUTE @Rezultat
		PRINT 'Executing ' + @Rezultat
		SET @versiuneCurenta = (SELECT numarVersiune FROM Versiune)
	END
END