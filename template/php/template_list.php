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

	if ($submit == "Delete") {
		for ($i = 0 ; $i < count($chkDelete) ; $i++) {
			echo  "Delete Data with Id = " . $chkDelete[$i] . " <br> " ;
			$del_str="DELETE FROM @VarMainTable(NAME)@ WHERE (@VarMainTable(KEYSTR)@) ='" . $chkDelete[$i] . "'";
  			$qry_result = pg_query($db_conn,$del_str);
			if (!$qry_result) {
				echo pg_last_error() . " ... <br>";
			}			
		}
	}
	
@VarArrayFields@
	$num_fields = @VarNumFields@ ;
	
	$sql_str = " @VarSQLStr(SELECT)@ , (@VarMainTable(ALIASKEYSTR)@) AS uniquekey ";
	$sql_str .= " @VarSQLStr(FROM)@ ";
 	$sql_where = "@VarSQLStr(WHERE)@";
	if ($keyword != "") {
		if ($sql_where != "")
			$sql_where .= " AND $field_name[$search_by] LIKE '%$keyword%'";
		else
			$sql_where .= " WHERE $field_name[$search_by] LIKE '%$keyword%' ";
	}	
	
	$sql_str .= $sql_where ;
	$sql_str .= " @VarSQLStr(GROUPBY)@ ";
	$sql_str .= " @VarSQLStr(HAVING)@ ";
	$sql_str .= " ORDER BY ( @VarMainTable(ALIASKEYSTR)@ ) " ;

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
		<td colspan=<? echo $num_fields ?> >
			<SELECT name="search_by" >
@VarSearchFields@
			</SELECT>
		</td>
    </tr>
    <tr align=left>
    	<td colspan=2> Key  </td>
		<td colspan=<? echo $num_fields ?> >
		<input type=text name="keyword" value="<? echo $keyword?>"> &nbsp;&nbsp;&nbsp;
		<input type=submit name="submit" value="Filter">
		</td>
    </tr>
    <tr>
    	<td colspan=<? echo $num_fields + 1 ?> > <?php echo "Found " . pg_num_rows($qry_result) . " records"; ?>  </td>
		<td align=right> << page 1 of 1 >> </td>
    </tr>
    <tr>
    	<td colspan=<? echo $num_fields + 2 ?> > 
			<input type=submit name=Add value="Add New" onClick="document.forms[0].action='./frm_@VarHrefUpdt@_input.php';return true;"> 
		</td>
    </tr>
    <tr align=center>
@VarHeaderList@
		<td>Update</td>
		<td><input type=submit name="submit" value="Delete"></td>
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
		<td align=center><A HREF="frm_@VarHrefUpdt@_input.php?cat=update&uniqid=<? echo $data[$num_fields] ?>"> Update </A> </td>
		<td align=center><input type=checkbox name="chkDelete[]" value="<? echo $data[$num_fields] ?>"></td>
    </tr>
	<?
	}
	?>
  </tbody>
</table>
</form>
</body>
</html>
