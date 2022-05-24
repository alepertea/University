USE PetStore;

-- Non-Repeatable Reads Transaction 2: select + delay + select
-- Order of the operations: select - update - select
go
CREATE PROCEDURE Non_Repeatable_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED	-- !!!!!!!!!
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

EXECUTE Non_Repeatable_Reads_T2;

-- Solution
go
CREATE PROCEDURE Non_Repeatable_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
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

EXECUTE Non_Repeatable_Reads_T2_Solution;