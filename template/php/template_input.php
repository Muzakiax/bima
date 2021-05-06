<?
include "db_inc.inc";
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN">
<html>
<head>
  <title> @VarForm(TITLE)@ </title>
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
  <meta name="GENERATOR" content="Bima">
</head>
<?php

	if ($submit == 'Save') {
		if ($cat == "update") {
			$sql_str = "@VarUpdateSQLStr@ = '" . $uniqid . "'";
		} else {
			$sql_str = "@VarInsertSQLStr@";
		}
		$qry_result = pg_query($db_conn, $sql_str);
		if (!$qry_result) {
			echo "Error, could not save ... <br>";
			echo pg_last_error($db_conn);
		}		
	}
	if ($cat == "update") {
		$sql_str = "  @VarSelUpdtSQL@ = '" . $uniqid . "'";

		$qry_result = pg_query($db_conn, $sql_str  );
		if (!$qry_result) {
			echo pg_last_error() . " ... <br>";
		} else {
			if ($data = pg_fetch_row($qry_result , $row )) {
@VarUpdtInputList@
			}
		}
	}
?>
<body>
<table border=1>
  <thead>
    <tr>
      <th scope=col colspan=2> @VarFormTitle@ </th>
    </tr>
  </thead>
  <tbody>
  <form method="POST"  action="<?echo $_SERVER["PHP_SELF"]?>">
@VarFormInputList@  
    <tr>
    	<td colspan=2><input type=submit name=submit value="Save"></td>
    </tr>
	<input type=hidden name=cat value="<?echo $cat?>">
	<input type=hidden name=uniqid value="<?echo $uniqid?>">
  </form>

  </tbody>
</table>
</body>
</html>
