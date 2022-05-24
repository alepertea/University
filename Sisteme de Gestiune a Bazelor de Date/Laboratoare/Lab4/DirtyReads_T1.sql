USE PetStore;

-- Dirty Reads Transaction 1: update + delay + rollback
go
CREATE PROCEDURE Dirty_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		UPDATE Magazin SET numarOrase = 100 WHERE denumire = 'Animal Care'
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('UPDATE', 'Magazin', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked - good!' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked - bad!' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T1;