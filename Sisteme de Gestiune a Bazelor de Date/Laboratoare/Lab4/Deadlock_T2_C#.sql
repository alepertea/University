USE PetStore;

go
CREATE PROCEDURE Deadlock_T2_C# AS
BEGIN
	SET DEADLOCK_PRIORITY HIGH
	-- SET DEADLOCK_PRIORITY LOW
	BEGIN TRAN
	UPDATE Manager SET nume = 'DEADLOCK' WHERE nume = 'Deadlock'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Manager', CURRENT_TIMESTAMP)
	WAITFOR DELAY '00:00:05'
	UPDATE Magazin SET numarOrase = 100 where denumire = 'Deadlock Store'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Magazin', CURRENT_TIMESTAMP)
	COMMIT TRAN
END

SELECT * FROM Manager
insert into Magazin(denumire, numarOrase) values ('Deadlock Store', 1)
insert into Manager(idManager, nume, prenume, dataOcuparePost) values (459855, 'Deadlock', 'Manager', '2021-05-18')