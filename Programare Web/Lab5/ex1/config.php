<?php
	$serverName = "DESKTOP-IKRGGHC\\SQLEXPRESS";
	$connectionInfo = array("Database" => "WebHW");
	$conn = sqlsrv_connect($serverName, $connectionInfo);
	if (!$conn) {
		echo "Connection could not be established. <br>";
		die(print_r(sqlsrv_errors(), true));
	}
?>