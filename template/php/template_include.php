<?php
	$db_conn = pg_connect("@VarDatabaseConnection@");
	if ( !$db_conn ) {
			echo "Error... <br>";
			echo pg_last_error($db_conn);
		exit;
	}
?>
