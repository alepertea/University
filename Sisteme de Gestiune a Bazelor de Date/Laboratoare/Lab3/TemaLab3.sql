CREATE TABLE LogTable
(
	id INT IDENTITY,
	operationType VARCHAR(20),
	tableName VARCHAR(20),
	executionTime DATETIME,
	CONSTRAINT pk_LogTable PRIMARY KEY(id)
)

go
CREATE FUNCTION validateParameters_Magazin(@denumire VARCHAR(50), @numarOrase INT)
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
go

CREATE FUNCTION validateParameters_Animal(@idGrupa INT, @denumire VARCHAR(100), @pret INT)
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
go

CREATE FUNCTION validateParameters_PetStore(@idMagazin INT, @idAnimal INT)
RETURNS VARCHAR(200)
AS
BEGIN
	DECLARE @errorMessage VARCHAR(200)
	SET @errorMessage = ''

	IF (EXISTS(SELECT idMagazin, idAnimal FROM PetStore WHERE idMagazin = @idMagazin AND idAnimal = @idAnimal))
		SET @errorMessage = @errorMessage + 'Valorile deja exista in tabel.'

	RETURN @errorMessage
END
go

CREATE PROCEDURE Insert_Into_Tables(@denumireMagazin VARCHAR(50), @numarOrase INT, @idGrupa INT, @denumireAnimal VARCHAR(100), @pret INT, @descriere VARCHAR(100))
AS
BEGIN
	
	BEGIN TRAN
	BEGIN TRY
		DECLARE @errorMessage VARCHAR(200)
		SET @errorMessage = dbo.validateParameters_Magazin(@denumireMagazin, @numarOrase)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumireMagazin, @numarOrase)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'Magazin', CURRENT_TIMESTAMP)

		SET @errorMessage = dbo.validateParameters_Animal(@idGrupa, @denumireAnimal, @pret)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Animal(idGrupa, denumire, pret, descriere) VALUES (@idGrupa, @denumireAnimal, @pret, @descriere)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'Animal', CURRENT_TIMESTAMP)

		DECLARE @idMagazin INT, @idAnimal INT
		SET @idMagazin = (SELECT MAX(idMagazin) FROM Magazin)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		SET @idAnimal = (SELECT MAX(idAnimal) FROM Animal)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Animal', CURRENT_TIMESTAMP)

		SET @errorMessage = dbo.validateParameters_PetStore(@idMagazin, @idAnimal)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO PetStore(idMagazin, idAnimal) VALUES (@idMagazin, @idAnimal)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'PetStore', CURRENT_TIMESTAMP)

		COMMIT TRAN

		SELECT 'Transaction committed'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked'
	END CATCH

END
go

-- with success (commit)
EXECUTE dbo.Insert_Into_Tables 'Store 2', 2, 12, 'Porumbel', 50, ''
SELECT * FROM Magazin
SELECT * FROM Animal
SELECT * FROM PetStore
SELECT * FROM LogTable

-- without success (rollback)
EXECUTE dbo.Insert_Into_Tables 'Lalala', 2, 192, 'asas', 2, ''
SELECT * FROM Magazin
SELECT * FROM Animal
SELECT * FROM PetStore
SELECT * FROM LogTable

go
CREATE PROCEDURE Insert_Into_Tables_v2(@denumireMagazin VARCHAR(50), @numarOrase INT, @idGrupa INT, @denumireAnimal VARCHAR(100), @pret INT, @descriere VARCHAR(100))
AS
BEGIN

	DECLARE @error INT
	SET @error = 0
	
	BEGIN TRAN
	BEGIN TRY
		DECLARE @errorMessage VARCHAR(200)
		SET @errorMessage = dbo.validateParameters_Magazin(@denumireMagazin, @numarOrase)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Magazin(denumire, numarOrase) VALUES (@denumireMagazin, @numarOrase)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'Magazin', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction committed for table Magazin'
	
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked for table Magazin'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('ROLLBACK', 'Magazin', CURRENT_TIMESTAMP)
		SET @error = 1
	END CATCH

	BEGIN TRAN
	BEGIN TRY
		SET @errorMessage = dbo.validateParameters_Animal(@idGrupa, @denumireAnimal, @pret)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO Animal(idGrupa, denumire, pret, descriere) VALUES (@idGrupa, @denumireAnimal, @pret, @descriere)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'Animal', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction committed for table Animal'

	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked for table Animal'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('ROLLBACK', 'Animal', CURRENT_TIMESTAMP)
	END CATCH

	IF (@error != 0)
		RETURN

	BEGIN TRAN
	BEGIN TRY
		DECLARE @idMagazin INT, @idAnimal INT
		SET @idMagazin = (SELECT MAX(idMagazin) FROM Magazin)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		SET @idAnimal = (SELECT MAX(idAnimal) FROM Animal)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Animal', CURRENT_TIMESTAMP)

		SET @errorMessage = dbo.validateParameters_PetStore(@idMagazin, @idAnimal)
		IF (@errorMessage != '')
		BEGIN
			RAISERROR(@errorMessage, 14, 1)
		END

		INSERT INTO PetStore(idMagazin, idAnimal) VALUES (@idMagazin, @idAnimal)
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'PetStore', CURRENT_TIMESTAMP)

		COMMIT TRAN
		SELECT 'Transaction committed for table PetStore'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked for table PetStore'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('ROLLBACK', 'PetStore', CURRENT_TIMESTAMP)
		SET @error = 1
	END CATCH

END
go

DROP PROCEDURE Insert_Into_Tables_v2

-- with success (commit)
EXECUTE dbo.Insert_Into_Tables_v2 'Yay animals 1', 2, 12, 'Porumbel', 50, ''
SELECT * FROM Magazin
SELECT * FROM Animal
SELECT * FROM PetStore
SELECT * FROM LogTable

-- without success (rollback)
EXECUTE dbo.Insert_Into_Tables_v2 'Lalala', 2, 192, 'asas', 2, ''
SELECT * FROM Magazin
SELECT * FROM Animal
SELECT * FROM PetStore
SELECT * FROM LogTable
