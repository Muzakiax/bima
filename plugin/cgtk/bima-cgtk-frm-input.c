
#include <string.h> /* memset() */
#include "bima-cgtk.h"
#include "bima-cgtk-utils.h"
#include "bima-cgtk-frm-input.h"

extern GList *local_list;
extern gint varc;


void
cgtk_gen_set_widget_default_value_an_attribute(FILE *ofile, BimaAttribute *attribute)
{
	gchar *name, *param;
	char *str_tok, *str_tok2;
	gint i ;
	BimaEntity *entity = NULL;

	i = 0;

	if (attribute != NULL) {
		// to avoid duplicate variable name
		name = g_strdup(attribute->name);
		if (is_exists_in_local_list(name)) {
			g_free(name);
			
			if (attribute->parent) 
				entity = (BimaEntity *)(attribute->parent);
			if (entity) {
				name = g_strdup_printf("%s_%s",entity->name,attribute->name);
			} else {
				name = g_strdup_printf("%s%d",attribute->name, varc);
			}
			entity = NULL;
		} else {
			append_to_local_list(name);
			varc++;
		}
		
		//fprintf(ofile, "  GtkWidget *lbl_%s;\n", name);
		if (!g_ascii_strcasecmp("Check", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Text", attribute->control_type)) {
			fprintf(ofile, "  gtk_entry_set_text(self->txt_%s,\"\");;\n", name);
		}
		else if (!g_ascii_strcasecmp("Label", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Radio Button", attribute->control_type)) {
			if (strlen(attribute->parameter) == 0) {
				fprintf(ofile, "  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbtn_%s),TRUE);\n",name);
			}
			else {
				fprintf(ofile, "  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbtn_%s1),TRUE);\n",name);
			}
		}
		else if (!g_ascii_strcasecmp("Combo", attribute->control_type)) {
			fprintf(ofile, " gtk_combo_box_set_active(self->cmb_%s,-1);\n", name);
		}
		else {
		}
	}
}


void
cgtk_gen_set_widget_default_value_an_fk(FILE *ofile, BimaForeignKey *fk)
{
	GList *list;
	gchar *name;

	if (fk != NULL) {
		// to avoid duplicate variable name
		name = g_strdup_printf("fk_%s",fk->name);
		if (is_exists_in_local_list(name)) {
			g_free(name);		
			name = g_strdup_printf("fk_%s%d",fk->name, varc);
		} else {
			append_to_local_list(name);
			varc++;
		}
		
		fprintf(ofile, "  //foreign key %s \n", fk->name);
		
		//fprintf(ofile, "  GtkWidget *lbl_%s;\n", name);
		//fprintf(ofile, "  GtkWidget *cmb_%s_model;\n", name);
		//fprintf(ofile, "  GtkWidget *cmb_%s_renderer;\n", name);
		fprintf(ofile, " gtk_combo_box_set_active(self->cmb_%s,-1);\n", name);
			//gtk_combo_box_set_active(self->cmb_fk_manages,-1);
	
		if ((fk->relation) && (fk->relation->attributes != NULL )) {
			fprintf(ofile, "  //foreign attribute\n");
			for (list = g_list_first(fk->relation->attributes);list != NULL; list = list->next){
				cgtk_gen_set_widget_default_value_an_attribute(ofile, (BimaAttribute *) list->data);
				//cgtk_gen_decl_widget_an_attribute(ofile, (BimaAttribute *) list->data);
			}
		}
	}
}

/**
 * gtk_gen_set_widget_default_value
 * @ofile 		: output file stream
 * @app_gui		: master gui
 * 	gtk_entry_set_text(self->txt_Number,"");
 *
**/
void
cgtk_gen_set_widget_default_value(FILE *ofile, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	

	gint n, n_field, fld, n_table,tbl;
	gchar *name;
	n_table = 0;
	varc = 0 ;
	// get number of 'query table'
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	// get number of query field  
	n_field = bima_query_get_number_of_fields(app_gui->query);

	n = 0;
	//loop for each 'query table'
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);

		//if ( (table_name == NULL) || ((table_name) && (!g_ascii_strcasecmp(table_name, qtbl->table))) && (n==0) ) {
		//qtbl->table

			// loop for each query field
			for (fld=0; fld < n_field ; fld++) {
				qtable = NULL;
				qfield = NULL;
		
				attribute = bima_query_get_nth_attribute(app_gui->query,fld, &qtable, &qfield);

				if ( (attribute) && ( 
				     ((qtable->alias) && (qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias)) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) || 
				     ((qtable->alias) && (qtbl->alias) && (!qtable->table) && (!qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias))) || 
					 ((!qtable->alias) && (!qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) 
					 ) 
				   ) {

						if (BIMA_IS_ATTRIBUTE(attribute))
							cgtk_gen_set_widget_default_value_an_attribute(ofile, (BimaAttribute *) attribute);
						//cgtk_gen_def_widget_an_attribute(ofile, &n, "widgetTable", (BimaAttribute *) attribute);
		
						if ( BIMA_IS_FOREIGN_KEY(attribute)) {
							cgtk_gen_set_widget_default_value_an_fk(ofile, (BimaForeignKey *) attribute);
					//	cgtk_gen_def_widget_an_fk(ofile, &n, "widgetTable",(BimaForeignKey *) attribute);
					}
					n++;
				}
			}
		//}
	}
}

/**
 * @CgtkFormInputShowData
 * gtk_gen_form_input_show_data
 * @ofile 		: output file stream
 * @app_gui		: master gui
 * 	gtk_entry_set_text(self->txt_Number,"");
 *
**/
void
cgtk_gen_form_input_show_data(FILE *ofile, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	

	gint n_field, fld, n_table,tbl;
	gchar *name;
	// get number of 'query table'
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	// get number of query field  
	n_field = bima_query_get_number_of_fields(app_gui->query);

	//loop for each 'query table'
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);
			
			// loop for each query field
			for (fld=0; fld < n_field ; fld++) {
				qtable = NULL;
				qfield = NULL;
		
				attribute = bima_query_get_nth_attribute(app_gui->query,fld, &qtable, &qfield);

				if ( (attribute) && ( 
				     ((qtable->alias) && (qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias)) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) || 
				     ((qtable->alias) && (qtbl->alias) && (!qtable->table) && (!qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias))) || 
					 ((!qtable->alias) && (!qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) 
					 ) 
				   ) {

						if (BIMA_IS_ATTRIBUTE(attribute))
							cgtk_gen_set_widget_default_value_an_attribute(ofile, (BimaAttribute *) attribute);
		
						if ( BIMA_IS_FOREIGN_KEY(attribute)) {
							cgtk_gen_set_widget_default_value_an_fk(ofile, (BimaForeignKey *) attribute);

					}
				}
			}
	}
}

