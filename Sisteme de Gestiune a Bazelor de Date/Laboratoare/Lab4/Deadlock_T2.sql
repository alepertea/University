USE PetStore;

-- Deadlock Transaction 2 : update on MANAGER + delay + update on MAGAZIN
go
CREATE PROCEDURE Deadlock_T2 AS
BEGIN
	SET DEADLOCK_PRIORITY HIGH
	-- SET DEADLOCK_PRIORITY LOW
	BEGIN TRAN
	BEGIN TRY
		UPDATE Manager SET nume = 'DEADLOCK' WHERE nume = 'Deadlock'
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Manager', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		UPDATE Magazin SET numarOrase = 100 where denumire = 'Deadlock Store'
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Magazin', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Deadlock_T2;