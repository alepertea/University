-- Validarea datelor PetStore
CREATE FUNCTION validatePetStore(@idMagazin INT, @idAnimal INT)
RETURNS VARCHAR(200)
AS
BEGIN
	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = ''
	
	IF (NOT(EXISTS(SELECT idMagazin FROM PetStore WHERE idMagazin = @idMagazin)))
		SET @errorMessage = @errorMessage + 'Magazinul cu ID ' + CONVERT(VARCHAR, @idMagazin) + ' nu exista. '

	IF (NOT(EXISTS(SELECT idAnimal FROM PetStore WHERE idAnimal = @idAnimal)))
		SET @errorMessage = @errorMessage + 'Animalul cu ID ' + CONVERT(VARCHAR, @idAnimal) + ' nu exista. '

	IF (EXISTS(SELECT idMagazin, idAnimal FROM PetStore WHERE idMagazin = @idMagazin AND idAnimal = @idAnimal))
		SET @errorMessage = @errorMessage + 'Valorile deja exista in tabel.'

	RETURN @errorMessage
END
GO

-- CRUD procedure for PetStore
GO
CREATE PROCEDURE CRUD_PetStore
(@idMagazin INT, @idAnimal INT)
AS
BEGIN

	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = dbo.validatePetStore(@idMagazin, @idAnimal)

	IF (@errorMessage != '')
	BEGIN
		PRINT 'ERROR: ' + @errorMessage
		RETURN
	END

	PRINT 'CRUD operations for table PetStore'

	-- CREATE
	INSERT INTO PetStore(idMagazin, idAnimal) VALUES (@idMagazin, @idAnimal)
	PRINT 'Inserted values (' + CONVERT(VARCHAR, @idMagazin) + ', ' + CONVERT(VARCHAR, @idAnimal) + ')'

	-- READ
	SELECT * FROM PetStore

	-- UPDATE
	PRINT 'Cannot update this table'

	-- DELETE
	DELETE FROM PetStore WHERE idMagazin = @idMagazin AND idAnimal = @idAnimal
	PRINT 'Deleted values (' + CONVERT(VARCHAR, @idMagazin) + ', ' + CONVERT(VARCHAR, @idAnimal) + ')'
	SELECT * FROM PetStore

END
GO

EXECUTE CRUD_PetStore 459740, 1
EXECUTE CRUD_PetStore 459740, 2

-- Validarea datelor Magazin
GO
CREATE FUNCTION validateMagazin(@denumire VARCHAR(50), @numarOrase INT)
RETURNS VARCHAR(200)
AS
BEGIN

	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = ''

	IF (@numarOrase <= 0)
		SET @errorMessage = @errorMessage + 'Numar invalid de orase. '

	IF (@denumire = '' OR LEFT(@denumire, 1) != UPPER(LEFT(@denumire, 1)) COLLATE Latin1_General_BIN)
		SET @errorMessage = @errorMessage + 'Denumire invalida.'

	IF (EXISTS(SELECT denumire FROM Magazin WHERE denumire = @denumire))
		SET @errorMessage = @errorMessage + 'Magazinul cu numele ' + @denumire + ' deja exista.'

	RETURN @errorMessage

END
GO

-- CRUD procedure for Magazin
CREATE PROCEDURE CRUD_Magazin
(@denumire VARCHAR(50), @numarOrase INT)
AS
BEGIN
	
	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = dbo.validateMagazin(@denumire, @numarOrase)

	IF (@errorMessage != '')
	BEGIN
		PRINT 'ERROR: ' + @errorMessage
		RETURN
	END

	PRINT 'CRUD operations for Magazin'

	-- CREATE
	INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumire, @numarOrase)
	PRINT 'Inserted values (' + @denumire + ', ' + CONVERT(VARCHAR, @numarOrase) + ')'

	-- READ
	SELECT * FROM Magazin

	-- UPDATE
	UPDATE Magazin SET numarOrase = @numarOrase + 10 WHERE denumire = @denumire
	PRINT '(' + @denumire + ', ' + CONVERT(VARCHAR, @numarOrase) + ') --> (' + @denumire + ', ' + CONVERT(VARCHAR, @numarOrase + 10) + ')'
	SELECT * FROM Magazin

	-- DELETE
	DELETE FROM Magazin WHERE denumire = @denumire
	PRINT 'Deleted store ' + @denumire
	SELECT * FROM Magazin

END

EXECUTE CRUD_Magazin Pets4Life, 4
EXECUTE CRUD_Magazin Biopet, -2

-- Validarea datelor Animal
GO
CREATE FUNCTION validateAnimal(@idGrupa INT, @denumire VARCHAR(100), @pret INT, @descriere VARCHAR(100))
RETURNS VARCHAR(200)
AS
BEGIN

	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = ''

	IF (NOT(EXISTS(SELECT idGrupa FROM Grupa WHERE idGrupa = @idGrupa)))
		SET @errorMessage = @errorMessage + 'Nu exista grupa cu ID-ul ' + CONVERT(VARCHAR, @idGrupa) + '. '

	IF (PATINDEX('%[0-9]%', @denumire) > 0 OR LEFT(@denumire, 1) != UPPER(LEFT(@denumire, 1)) COLLATE Latin1_General_BIN)
		SET @errorMessage = @errorMessage + 'Denumire animal invalida. '

	IF (@pret <= 0)
		SET @errorMessage = @errorMessage + 'Pret invalid. '

	RETURN @errorMessage

END
GO

-- CRUD procedure for Animal
GO
CREATE PROCEDURE CRUD_Animal
(@idGrupa INT, @denumire VARCHAR(100), @pret INT, @descriere VARCHAR(100))
AS
BEGIN
	
	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = dbo.validateAnimal(@idGrupa, @denumire, @pret, @descriere)

	IF (@errorMessage != '')
	BEGIN
		PRINT 'ERROR: ' + @errorMessage
		RETURN
	END

	PRINT 'CRUD operations for Animal'

	-- CREATE
	INSERT INTO Animal(idGrupa, denumire, pret, descriere) VALUES (@idGrupa, @denumire, @pret, @descriere)
	PRINT 'Inserted values (' + CONVERT(VARCHAR, @idGrupa) + ', ' + @denumire + ', ' + CONVERT(VARCHAR, @pret) + ', ' + @descriere + ')'

	-- READ
	SELECT * FROM Animal

	-- UPDATE
	UPDATE Animal SET pret = @pret + 100 WHERE denumire = @denumire
	PRINT '(' + CONVERT(VARCHAR, @idGrupa) + ', ' + @denumire + ', ' + CONVERT(VARCHAR, @pret) + ', ' + @descriere + ') --> (' + CONVERT(VARCHAR, @idGrupa) + ', ' + @denumire + ', ' + CONVERT(VARCHAR, @pret + 100) + ', ' + @descriere + ')'
	SELECT * FROM Animal

	-- DELETE
	DELETE FROM Animal WHERE denumire = @denumire
	PRINT 'Deleted ' + @denumire
	SELECT * FROM Animal

END
GO

EXECUTE CRUD_Animal 13, Pug, 100, 'Small doggo'
EXECUTE CRUD_Animal 323, lalala, -12, ''

-- View 1
GO
CREATE VIEW View_MagazineMamifere AS
SELECT DISTINCT M.denumire AS Magazin, M.numarOrase AS [Numar orase] FROM Magazin M 
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal
WHERE A.idGrupa = 13
GO

SELECT * FROM View_MagazineMamifere

-- View 2
GO
CREATE VIEW View_AnimaleMagazine AS
SELECT M.denumire AS Magazin, A.denumire AS Animal, A.pret AS Pret FROM Magazin M 
INNER JOIN PetStore P ON M.idMagazin = P.idMagazin
INNER JOIN Animal A ON A.idAnimal = P.idAnimal
WHERE A.pret <= 200
GO

SELECT * FROM View_AnimaleMagazine ORDER BY Pret

DROP VIEW View_AnimaleMagazine

-- Indecsi
--CREATE NONCLUSTERED INDEX Index_DenumireMagazin ON Magazin(denumire)
--CREATE NONCLUSTERED INDEX Index_DenumireAnimal ON Animal(denumire)
--CREATE NONCLUSTERED INDEX Index_NumarOrase ON Magazin(numarOrase)
CREATE NONCLUSTERED INDEX Index_PretAnimal ON Animal(pret)

DROP INDEX Index_DenumireMagazin ON Magazin
DROP INDEX Index_DenumireAnimal ON Animal
DROP INDEX Index_NumarOrase ON Magazin
DROP INDEX Index_IDGrupa ON Animal
DROP INDEX Index_idMagazin ON Magazin
DROP INDEX Index_idAnimal ON Animal

CREATE NONCLUSTERED INDEX Index_IDGrupa ON Animal(idGrupa)
CREATE NONCLUSTERED INDEX Index_idMagazin ON PetStore(idMagazin)
CREATE NONCLUSTERED INDEX Index_idAnimal ON PetStore(idAnimal)

SELECT * FROM Animal