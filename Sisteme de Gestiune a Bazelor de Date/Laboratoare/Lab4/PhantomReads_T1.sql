USE PetStore;

-- Phantom Reads Transaction 1: delay + insert + commit
go
CREATE PROCEDURE Phantom_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		WAITFOR DELAY '00:00:05'
		INSERT INTO Magazin(denumire, numarOrase) VALUES ('NEW STORE', 5)
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('INSERT', 'Magazin', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Phantom_Reads_T1;