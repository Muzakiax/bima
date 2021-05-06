%{
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <glib-object.h>

#include "bima-app-gui.h"
#include "bima-query.h"
#include "bima-query-field.h"
#include "bima-query-table.h"
#include "bima-utils.h"

extern char *qrytext;
%}

%union {
	BimaQuery *tquery;
	BimaQueryTable *ttable;
	BimaQueryField *tfield;
	GList *tlist;
	char *tkeyword;
	int	tint;
}

%type <tquery> select
%type <tfield> field  sort_field field_expr field_as where_sytx having_sytx
%type <tint> sort_op function join_type opr_type
%type <tlist> select_list sort_list group_list from_list
%type <ttable> table join_table
%type <tkeyword> alias_lbl
%token <tkeyword> SELECT WORDS FROM INNER JOIN OUTER RIGHT LEFT WHERE AS ON AND OR GROUP BY HAVING 
				ORDER DESC ASC SUM COUNT AVG T_MAX T_MIN STDDEV VARIANCE

%{
extern BimaAppGui *app_gui;
int nField = 0 ;
%}

%%

query:
	select 	{	app_gui->query = $1;	}
	| select ORDER BY sort_list
	{
		$1->orders = $4 ;
		app_gui->query = $1;
	}
	;

select : SELECT select_list FROM from_list where_sytx
	{
		BimaQuery *q = bima_query_new();
		q->fields = $2 ;
		q->tables = $4 ;
		q->groups = NULL;
		q->havings = NULL;
		q->wheres = $5;
		q->orders = NULL;
		
		bima_query_validate_fields(q);
		// just calc BimaQuery->
		//nField = bima_query_count_number_of_fields(q);
//		bima_query_count_num_of_tables(q);
		$$ = q;
	}
	| SELECT select_list FROM from_list where_sytx GROUP BY group_list having_sytx
	{
		BimaQuery *q = bima_query_new();
		q->fields = $2 ;
		q->tables = $4 ;
		q->groups = $8 ; 
		q->havings = $9 ;
		q->wheres = $5 ;
		q->orders = NULL;
		bima_query_validate_fields(q);
		//nField = bima_query_count_number_of_fields(q);
//		bima_query_count_num_of_tables(q);
		$$ = q;	
	}
	;

where_sytx : WHERE field_expr 		{	$$ = $2; }
	| /*EMPTY*/						{	$$ = NULL; }
	;

having_sytx : HAVING field_expr 		{	$$ = $2; }
	| /*EMPTY*/							{	$$ = NULL; }
	;
	
sort_list : sort_field
	{
		$$ = NULL;
		$$ = g_list_append($$, (gpointer)$1);
	}
	| sort_list ',' sort_field
	{
		$$ = g_list_append($1, (gpointer)$3);
	}
	;

sort_field : field sort_op
	{
		$1->sort_type = $2;
		$$ = $1;
	}
	;

sort_op : ASC					{	$$ = 1;	}
	| DESC						{	$$ = 2;	}
	| /*EMPTY*/					{	$$ = 0;	}
	;
	
select_list: field_as
	{
		//nField++;
		$$ = NULL;
		$$ = g_list_append($$, (gpointer)$1);
	}
	| select_list ',' field_as
	{
		$$ = g_list_append($1, (gpointer)$3);
	}
	;

field_as : field_expr AS WORDS
	{
		$1->alias = $3;
		$$ = $1;
	}
	| '(' field_expr ')' AS WORDS
	{
		$2->alias = $5;
		$$ = $2;
	}
	| field_expr 	{	$$ = $1;	}
	| '(' field_expr ')'	{	$$ = $2;	}
	;

group_list: field
	{
		$$ = NULL;
		$$ = g_list_append($$, (gpointer)$1);
	}
	| group_list ',' field
	{
		$$ = g_list_append($1, (gpointer)$3);
	}
	;

field_expr : field	{	$$ = $1;	}
	| field_expr opr_type field_expr
	{
		
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->opr_type = $2;
		tmp_qry->left_field = $1;
		tmp_qry->right_field = $3;
		
		$$ = tmp_qry;
	}		
	| function '(' field_expr ')'
	{
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->opr_type = $1;
		tmp_qry->left_field = $3;		
		$$ = tmp_qry;
	}	
	;

opr_type : '='	{	$$ = 1; }
	| '+'	{	$$ = 2; }
	| '-'	{	$$ = 3; }
	| '*'	{	$$ = 4; }	
	| '/'	{	$$ = 5; }
	| AND	{	$$ = 6; }
	| OR	{	$$ = 7; }
	;
	
field:	WORDS
	{
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->field = $1;
		$$ = tmp_qry;
	}
	| '*'
	{
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->field = g_strdup("*");
//		printf("star\n");		
		$$ = tmp_qry;
	}
	| WORDS '.' WORDS
	{
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->field = $3;
		tmp_qry->table = $1;
//		printf("%s %s\n",$1,$3);
		$$ = tmp_qry;
	}
	| WORDS '.' '*'
	{
		BimaQueryField *tmp_qry = bima_query_field_new();
		tmp_qry->field = g_strdup("*");
		tmp_qry->table = $1;
		$$ = tmp_qry;
	}
	;
	
function : SUM 		{ $$ = 100;}
	| COUNT 		{ $$ = 101;}
	| AVG 			{ $$ = 102;}
	| T_MAX 		{ $$ = 103;} 
	| T_MIN  		{ $$ = 104;}
	| STDDEV  		{ $$ = 105;}
	| VARIANCE 		{ $$ = 106;}
	;
	
from_list : table
	{
		$$ = NULL;
		$$ = g_list_append($$, (gpointer)$1);
	}
	| from_list ',' table
	{
		$$ = g_list_append($1, (gpointer)$3);
	}	
	;

table: WORDS alias_lbl
	{
		BimaQueryTable *tmp_tbl = bima_query_table_new();
		tmp_tbl->alias = $2;
		tmp_tbl->table = $1;
		tmp_tbl->entity = bima_get_object_by_prop(app_gui->app_data->entities , "name", $1);
		if (!tmp_tbl->entity)
			tmp_tbl->entity = bima_get_object_by_prop(app_gui->app_data->relations , "name", $1);
		$$ = tmp_tbl;
	}
	| '(' select ')'  alias_lbl
	{
		BimaQueryTable *tmp_tbl = bima_query_table_new();
		tmp_tbl->alias = $4;
		tmp_tbl->sub_query = $2;
		$$ = tmp_tbl;
	}
	| join_table 	{	$$ = $1;	}
	;

alias_lbl : WORDS 	{	$$ = $1;	}
	| /*EMPTY*/ 	{ 	$$ = NULL;	}
	;

join_table: table join_type table ON  field_expr 
	{
		BimaQueryTable *tmp_tbl = bima_query_table_new();
		tmp_tbl->left_table = $1;
		tmp_tbl->join_type = $2;
		tmp_tbl->right_table = $3;
		tmp_tbl->join_rule = $5;
		$$ = tmp_tbl;	
	}
	;

join_type : INNER JOIN				{	$$ = 1; }
	|	RIGHT OUTER JOIN			{	$$ = 2; }
	|	LEFT OUTER JOIN				{	$$ = 3; }
	;

%%

void qryerror(const char *str)
{
//	printf("query error : %s ,before %s \n", str, qrytext);
	g_object_unref((GObject *) (app_gui->query));
	app_gui->query=NULL;
}

int qrywrap()
{
	return 1;
}
