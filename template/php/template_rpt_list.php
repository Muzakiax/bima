<?
include "db_inc.inc";
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN">
<html>
<head>
  <title> @VarFormTitle@ </title>
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
  <meta name="GENERATOR" content="Bima">
</head>
<body bgcolor="#E6E6E6">
<?php
	$db_conn = pg_connect(" @VarDatabaseConnection@ ");
	if ( !$db_conn ) {
		echo "Error ...";
		exit;
	}

@VarArrayFields@
	
	$sql_str = "  @VarSQLString@  ";
	if ($keyword != "") {
		$sql_str .= "WHERE $field_name[$search_by] LIKE '%$keyword%'";
	}	
	
	$num_fields = @VarNumFields@ ;


  	$qry_result = pg_query($db_conn, $sql_str  );
	if (!$qry_result) {
		echo pg_last_error() . " ... <br>";
		exit;
	}
?>
<form method="POST" action="<?echo $_SERVER["PHP_SELF"]?>">
<table border=1 align=center width=90%>
  <thead>
    <tr align=left>
    	<td colspan=2> Search By </td>
		<td colspan=<? echo $num_fields - 2?> >
			<SELECT name="search_by" >
@VarSearchFields@
			</SELECT>
		</td>
    </tr>
    <tr align=left>
    	<td colspan=2> Key  </td>
		<td colspan=<? echo $num_fields -2?> >
		<input type=text name="keyword" value="<? echo $keyword?>"> &nbsp;&nbsp;&nbsp;
		<input type=submit name="submit" value="Filter">
		</td>
    </tr>
    <tr>
    	<td colspan=<? echo $num_fields - 1 ?> > <?php echo "Found " . pg_num_rows($qry_result) . " records"; ?>  </td>
		<td align=right> << page 1 of 1 >> </td>
    </tr>

    <tr align=center>
		@VarHeaderList@

    </tr>
  </thead>
  <tbody>
  	<?php
	while ($data = pg_fetch_row($qry_result , $row )) {
	?>
	<tr>
	<?
		@VarContentList@
	?>
    </tr>
	<?
	}
	?>
  </tbody>
</table>
</form>
</body>
</html>
