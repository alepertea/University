USE PetStore;

-- Deadlock Transaction 1: update on MAGAZIN + delay + update on MANAGER
go
CREATE PROCEDURE Deadlock_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		UPDATE Magazin SET numarOrase = 100 where denumire = 'Deadlock Store'
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Magazin', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		UPDATE Manager SET nume = 'DEADLOCK' WHERE nume = 'Deadlock'
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Manager', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Deadlock_T1;