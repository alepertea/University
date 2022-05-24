USE PetStore;

-- Dirty Reads Transaction 2: select + delay + select
-- Order of the operations: update - select - rollback - select
go
CREATE PROCEDURE Dirty_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED	-- !!!!!!!!!!!
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Magazin
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Magazin
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T2;

-- Solution:
go
CREATE PROCEDURE Dirty_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Magazin
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Magazin
			INSERT INTO LogTable(operationType, tableName, executionTime) VALUES ('SELECT', 'Magazin', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T2_Solution;