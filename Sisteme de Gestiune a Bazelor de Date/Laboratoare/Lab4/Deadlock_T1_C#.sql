USE PetStore;

go
CREATE PROCEDURE Deadlock_T1_C# AS
BEGIN
	BEGIN TRAN
	UPDATE Magazin SET numarOrase = 100 where denumire = 'Deadlock Store'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Magazin', CURRENT_TIMESTAMP)
	WAITFOR DELAY '00:00:05'
	UPDATE Manager SET nume = 'DEADLOCK' WHERE nume = 'Deadlock'
		INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Manager', CURRENT_TIMESTAMP)
	COMMIT TRAN
END