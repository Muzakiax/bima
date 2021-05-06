/***************************************************************************
 *            bima-cgtk.c
 *
 *  Copyright  2006  Anas Muzakir
 *  anas.muzakir@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string.h> /* memset() */
#include "bima-cgtk.h"
#include "bima-cgtk-utils.h"
#include "bima-cgtk-frm-input.h"


/* here are local prototypes */
static void bima_cgtk_plugin_init (BimaCgtkPlugin * o) ;
static void bima_cgtk_plugin_class_init (BimaCgtkPluginClass * c) ;

/* pointer to the class of our parent */
static BimaPluginClass *parent_class = NULL;

 GList *local_list;
 gint varc;

BIMA_PLUGIN_REGISTER_TYPE(BimaCgtkPlugin, bima_cgtk_plugin)

void
cgtk_gen_decl_main_btn(FILE *ofile, GList *flist)
{
	GList *tlist;
	BimaForm *form;

	for (tlist=g_list_first(flist);tlist != NULL; tlist = tlist->next){
  		form = (BimaForm *) tlist->data;
  		fprintf(ofile, "  GtkWidget *btn%s ;\n", form->name );
  	}
}

void
cgtk_gen_signal_main_btn(FILE *ofile, GList *flist)
{
	GList *tlist;
	BimaForm *form;

	for (tlist=g_list_first(flist);tlist != NULL; tlist = tlist->next){
  		form = (BimaForm *) tlist->data;

		fprintf(ofile, "\nvoid\n");
		fprintf(ofile, "on_btn%s_clicked (GtkButton *button, gpointer user_data)\n", form->name);
		fprintf(ofile, "{\n\n");
		fprintf(ofile, "\tGtkWidget *widget;\n");
		fprintf(ofile, "\twidget = create_%s();\n", form->name);
		fprintf(ofile, "\tg_signal_connect_swapped(widget, \"response\",\n");
		fprintf(ofile, "\t\tG_CALLBACK(gtk_widget_destroy),widget);\n");
		fprintf(ofile, "\tgtk_widget_show(widget);\n");
		fprintf(ofile, "}\n");  		
  	}
}

void
cgtk_gen_defn_main_btn(FILE *ofile, GList *flist)
{
	GList *tlist;
	BimaForm *form;

	for (tlist=g_list_first(flist);tlist != NULL; tlist = tlist->next){
  		form = (BimaForm *) tlist->data;

		fprintf(ofile, "\n  btn%s = gtk_button_new_with_mnemonic ((\"%s\"));\n", form->name, form->title);
		fprintf(ofile, "  gtk_widget_show (btn%s);\n", form->name);
		fprintf(ofile, "  gtk_box_pack_start (GTK_BOX (main_menu_vbox), btn%s, FALSE, FALSE, 0);\n", form->name);
		fprintf(ofile, "  g_signal_connect ( G_OBJECT (btn%s), \"clicked\",\n", form->name);
		fprintf(ofile, "  					G_CALLBACK (on_btn%s_clicked),\n", form->name);
		fprintf(ofile, "  					NULL);\n");
  	}
}

void
cgtk_gen_decl_widget_an_attribute(FILE *ofile, BimaAttribute *attribute)
{
	gchar *name, *param;
	char *str_tok, *str_tok2;
	gint i ;
	BimaEntity *entity = NULL;

	i = 0;

	if (attribute == NULL) {
//		fprintf(ofile, "  GtkWidget *lbl_%s;\n", "widget");
//		fprintf(ofile, "  GtkWidget *widget_%s;\n", "widget");
	} else {
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

		
		fprintf(ofile, "  GtkWidget *lbl_%s;\n", name);
		if (!g_ascii_strcasecmp("Check", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Text", attribute->control_type)) {
			fprintf(ofile, "  GtkWidget *txt_%s;\n", name);
		}
		else if (!g_ascii_strcasecmp("Label", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Radio Button", attribute->control_type)) {
			if (strlen(attribute->parameter) == 0) {
				
				fprintf(ofile, "  GtkWidget *rbtn_%s;\n", name);
			}
			else {
				fprintf(ofile, "  GtkWidget *hbox_rbtn_%s;\n", name);	
				param = g_strdup(attribute->parameter);
				str_tok  = strtok(param,";");
				str_tok2  = strtok(NULL,";");
					
				while (str_tok2 != NULL) {
					i++;
					fprintf(ofile, "  GtkWidget *rbtn_%s%d;\n", name,i);						
					str_tok  = strtok(NULL,";");
					if (str_tok != NULL) 
						str_tok2  = strtok(NULL,";");
					else 
						str_tok2  = NULL;			
				}
				g_free(param);
				fprintf(ofile, "  GSList *rbtn_%s_group = NULL;\n", name);										
				//g_free(str_tok);
				//g_free(str_tok2);
			}
		}
		else if (!g_ascii_strcasecmp("Combo", attribute->control_type)) {
			fprintf(ofile, "  GtkWidget *cmb_%s;\n", name);
		}
		else {
		}
	}
}

void
cgtk_gen_decl_widget_an_fk(FILE *ofile, BimaForeignKey *fk)
{
	GList *list;
	gchar *name;

	if (fk == NULL) {
//		fprintf(ofile, "  GtkWidget *lbl_%s;\n", "widget");
//		fprintf(ofile, "  GtkWidget *widget_%s;\n", "widget");
	} else {
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
		
		fprintf(ofile, "  GtkWidget *lbl_%s;\n", name);
		fprintf(ofile, "  GtkWidget *cmb_%s_model;\n", name);
		fprintf(ofile, "  GtkWidget *cmb_%s_renderer;\n", name);
		fprintf(ofile, "  GtkWidget *cmb_%s;\n", name);
			
		if ((fk->relation) && (fk->relation->attributes != NULL )) {
			fprintf(ofile, "  //foreign attribute\n");
			for (list = g_list_first(fk->relation->attributes);list != NULL; list = list->next){
				cgtk_gen_decl_widget_an_attribute(ofile, (BimaAttribute *) list->data);
			}
		}
	}
}

void
cgtk_gen_decl_widget(FILE *ofile, gchar *table_name, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	
	gchar *name;
	gint n,n_field, fld, n_table,tbl;
	n_table = 0;
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	n_field = bima_query_get_number_of_fields(app_gui->query);
	varc = 0 ;
	n=0;
	// looping for each table, to group show field base on table name
	// or one table base on table_name parameter	
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);
		if ( (table_name == NULL) || ((table_name) && (!g_ascii_strcasecmp(table_name, qtbl->table)) && (n==0))) {

			if (qtbl->alias)
				name = g_strdup_printf("%s",qtbl->alias);
			else
				name = g_strdup_printf("%s",qtbl->table);
			
			if (is_exists_in_local_list(name)) {
				g_free(name);		
				if (qtbl->alias)
					name = g_strdup_printf("%s%d",qtbl->alias, varc);
				else
					name = g_strdup_printf("%s%d",qtbl->table, varc);
			} else {
				append_to_local_list(name);
				varc++;
			}

			fprintf(ofile, "  GtkWidget *lbl_%s;\n", name);
			// now, loop for field in table
			for (fld=0; fld < n_field ; fld++) {
				qtable = NULL;
				qfield = NULL;
			
				attribute = bima_query_get_nth_attribute(app_gui->query,fld, &qtable, &qfield);
				// tbl hsl query attr hrs sama degan tabel iterasi
				if ( (attribute) && ( 
				     ((qtable->alias) && (qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias)) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) || 
				     ((qtable->alias) && (qtbl->alias) && (!qtable->table) && (!qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias))) || 
					 ((!qtable->alias) && (!qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) 
				 	) 
			   	) {

					if (BIMA_IS_ATTRIBUTE(attribute))
						cgtk_gen_decl_widget_an_attribute(ofile, (BimaAttribute *) attribute);
	
					if ( BIMA_IS_FOREIGN_KEY(attribute))
						cgtk_gen_decl_widget_an_fk(ofile, (BimaForeignKey *) attribute);
				}
				n++;
			}
		}
	}
}

/**
 * cgtk_gen_def_widget_an_attribute
 * @ofile 			: output file stream
 * @nth 			: row number in table widget
 * @tbl_container   : only specify GTK table widget container name
 * @app_gui			: master gui
**/
void
cgtk_gen_def_widget_an_attribute(FILE *ofile, gint *nth, gchar *tbl_container, BimaAttribute *attribute)
{
	gchar *name, *param;
	char *str_tok, *str_tok2;
	gint i ;
	BimaEntity *entity = NULL;
	i = 0;
	if (attribute == NULL) {
//		fprintf(ofile, "  GtkWidget *lbl_%s;\n", "widget");
//		fprintf(ofile, "  GtkWidget *widget_%s;\n", "widget");
		
	} else {
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
		fprintf(ofile, "  lbl_%s = gtk_label_new ((\"%s : \"));\n", name, attribute->title);
		fprintf(ofile, "  gtk_widget_show (lbl_%s);\n", name);
		fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), lbl_%s, 0, 1, %d, %d,\n", tbl_container, name,*nth,(*nth)+1);
		fprintf(ofile, "                    (GtkAttachOptions) (GTK_FILL),\n");
		fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");
		fprintf(ofile, "  gtk_misc_set_alignment (GTK_MISC (lbl_%s), 0, 0.5);\n", name);

		//fprintf(ofile, "  GtkWidget *lbl_%s;\n", attribute->name);
		if (!g_ascii_strcasecmp("Check", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Text", attribute->control_type)) {
			fprintf(ofile, "  txt_%s = gtk_entry_new ();\n", name);
			fprintf(ofile, "  gtk_widget_show (txt_%s);\n", name);
			fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), txt_%s, 1, 2, %d, %d,\n", tbl_container, name,*nth,(*nth)+1);
			fprintf(ofile, "                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),\n");
			fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");
		}
		else if (!g_ascii_strcasecmp("Label", attribute->control_type)) {
		}
		else if (!g_ascii_strcasecmp("Radio Button", attribute->control_type)) {
			if (strlen(attribute->parameter) == 0) {
//				fprintf(ofile, "  GtkWidget *rbtn_%s;\n", name);
				fprintf(ofile, "  rbtn_%s = gtk_radio_button_new_with_mnemonic (NULL, _(\"radiobutton\"));\n", name);
				fprintf(ofile, "  gtk_widget_show (rbtn_%s);\n",name);
				fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), rbtn_%s, 1, 2, %d, %d,\n", tbl_container, name,*nth,(*nth)+1);
				fprintf(ofile, "                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),\n");
				fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");

//				fprintf(ofile, "  gtk_box_pack_start (GTK_BOX (hbox1), radiobutton1, FALSE, FALSE, 0);
//				fprintf(ofile, "  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), radiobutton1_group);

			}
			else {

//				fprintf(ofile, "  GtkWidget *hbox_rbtn_%s;", name);	
				fprintf(ofile, "  hbox_rbtn_%s = gtk_hbox_new (FALSE, 5);\n", name);	
				fprintf(ofile, "  gtk_widget_show (hbox_rbtn_%s);\n", name);	
				fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), hbox_rbtn_%s, 1, 2, %d, %d,\n", tbl_container, name,*nth, (*nth)+1);	
				fprintf(ofile, "                    (GtkAttachOptions) (GTK_FILL),\n");
				fprintf(ofile, "                    (GtkAttachOptions) (GTK_FILL), 0, 0);\n");
//				fprintf(ofile, "  gtk_container_set_border_width (GTK_CONTAINER (hbox1), 3);
				
				//g_printf("%s  %s\n",attribute->name,attribute->parameter);
				param = g_strdup(attribute->parameter);
				str_tok  = strtok(param,";");
				str_tok2  = strtok(NULL,";");
					
				while (str_tok2 != NULL) {
					i++;
					fprintf(ofile, "  rbtn_%s%d = gtk_radio_button_new_with_mnemonic (NULL, (\"%s\"));\n", name,i,str_tok2);
					fprintf(ofile, "  gtk_widget_show (rbtn_%s%d);\n",name,i);
					fprintf(ofile, "  gtk_box_pack_start (GTK_BOX (hbox_rbtn_%s), rbtn_%s%d, FALSE, FALSE, 0);\n",name,name,i);
					fprintf(ofile, "  gtk_radio_button_set_group (GTK_RADIO_BUTTON (rbtn_%s%d), rbtn_%s_group);\n",name,i,name);
					fprintf(ofile, "  rbtn_%s_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rbtn_%s%d));\n",name,name,i);
					

					str_tok  = strtok(NULL,";");
					if (str_tok != NULL) 
						str_tok2  = strtok(NULL,";");
					else 
						str_tok2  = NULL;			
				}
				g_free(param);
//				fprintf(ofile, "  GSList *rbtn_%s_group = NULL;", name);										
				fprintf(ofile, "\n");
				//g_free(str_tok);
				//g_free(str_tok2);
			}

		}
		else if (!g_ascii_strcasecmp("Combo", attribute->control_type)) {

		}
		else {
		
		}
		g_free(name);
			
	}
}

void
cgtk_gen_def_widget_an_fk(FILE *ofile, gint *nth, gchar *tbl_container, BimaForeignKey *fk)
{
	GList *list;
	gchar *name;

	if (fk == NULL) {
//		fprintf(ofile, "  GtkWidget *lbl_%s;\n", "widget");
//		fprintf(ofile, "  GtkWidget *widget_%s;\n", "widget");
	} else {
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
		fprintf(ofile, "  lbl_%s = gtk_label_new ((\"%s : \"));\n", name, fk->name);
		fprintf(ofile, "  gtk_widget_show (lbl_%s);\n", name);
		fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), lbl_%s, 0, 1, %d, %d,\n",tbl_container, name,*nth,(*nth)+1);
		fprintf(ofile, "                    (GtkAttachOptions) (GTK_FILL),\n");
		fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");
		fprintf(ofile, "  gtk_misc_set_alignment (GTK_MISC (lbl_%s), 0, 0.5);\n", name);


		fprintf(ofile, "  cmb_%s_model = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_STRING);\n", name);
		fprintf(ofile, "  cmb_%s = gtk_combo_box_new_with_model(cmb_%s_model);\n", name,name);
		fprintf(ofile, "  cmb_%s_renderer = gtk_cell_renderer_text_new();\n", name);
		fprintf(ofile, "  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(cmb_%s), \n", name);
		fprintf(ofile, "  		cmb_%s_renderer, TRUE );\n", name);
		fprintf(ofile, "  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(cmb_%s), \n", name);
		fprintf(ofile, "  		cmb_%s_renderer, \"text\",0, NULL );\n",name);

		fprintf(ofile, "  gtk_widget_show (cmb_%s);\n", name);
		fprintf(ofile, "  gtk_table_attach (GTK_TABLE (%s), cmb_%s, 1, 2, %d, %d,\n", tbl_container, name,*nth,(*nth)+1);
		fprintf(ofile, "                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),\n");
		fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");

		// fix for nth
		if ((fk->relation) && (fk->relation->attributes != NULL )) {
			fprintf(ofile, "  //foreign attribute\n");
			for (list = g_list_first(fk->relation->attributes);list != NULL; list = list->next){
				*nth = (*nth) + 1;
				cgtk_gen_def_widget_an_attribute(ofile, nth,tbl_container, (BimaAttribute *) list->data);
			}
		}
	}
}

/**
 * cgtk_gen_def_widget
 * @ofile 		: output file stream
 * @table_name  : to specify entity/table or NULL if all table to be generate
 * @app_gui		: master gui
**/
void
cgtk_gen_def_widget(FILE *ofile, gchar *table_name, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	

	gint n,n_field, fld, n_table,tbl;
	gchar *name;
	n_table = 0;
	varc = 0;
	// get number of query table 
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	// get number of query field in 
	n_field = bima_query_get_number_of_fields(app_gui->query);

	//g_print("%s : %d \n ", ((BimaForm *)(app_gui->cur_obj))->title, n_table);

	n = 0;
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);

		if ( (table_name == NULL) || ((table_name) && (!g_ascii_strcasecmp(table_name, qtbl->table))) && (n==0) ) {
		//qtbl->table
			if (qtbl->alias)
				name = g_strdup_printf("%s",qtbl->alias);
			else
				name = g_strdup_printf("%s",qtbl->table);
			
			if (is_exists_in_local_list(name)) {
				g_free(name);		
				if (qtbl->alias)
					name = g_strdup_printf("%s%d",qtbl->alias, varc);
				else
					name = g_strdup_printf("%s%d",qtbl->table, varc);
			} else {
				append_to_local_list(name);
			}

			// print sparator lable
			fprintf(ofile, "  lbl_%s = gtk_label_new ((\"<b>%s</b>\"));\n", name, name);
			fprintf(ofile, "  gtk_widget_show (lbl_%s);\n", name);
			fprintf(ofile, "  gtk_table_attach (GTK_TABLE (widgetTable), lbl_%s, 0, 2, %d, %d,\n", name,n,n+1);
			fprintf(ofile, "                    (GtkAttachOptions) (GTK_FILL),\n");
			fprintf(ofile, "                    (GtkAttachOptions) (0), 0, 0);\n");
			fprintf(ofile, "  gtk_label_set_use_markup (GTK_LABEL (lbl_%s), TRUE);\n", name);
			fprintf(ofile, "  gtk_misc_set_alignment (GTK_MISC (lbl_%s), 0, 0.5);\n", name);
			n++;
		
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
						cgtk_gen_def_widget_an_attribute(ofile, &n, "widgetTable", (BimaAttribute *) attribute);
		
					if ( BIMA_IS_FOREIGN_KEY(attribute))
						cgtk_gen_def_widget_an_fk(ofile, &n, "widgetTable",(BimaForeignKey *) attribute);
					n++;
				}
			}
		}
	}
}

/**
 * cgtk_gen_dec_notebook_treeview_widget
 * @ofile 		: output file stream
 * @table_name  : to specify entity/table or NULL if all table to be generate
 * @app_gui		: master gui
**/
void
cgtk_gen_dec_notebook_treeview_widget(FILE *ofile, gchar *table_name, BimaAppGui *app_gui)
{
	//BimaAttribute *attribute;
	//BimaQueryField *qfield;
	BimaQueryTable *qtbl;	
	BimaEntity *main_entity;
	
	gint n,n_field, n_table,tbl;
	gchar *name, *str_tmp;
	n_table = 0;
	// get number of query table 
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	// get number of query field in 
	n_field = bima_query_get_number_of_fields(app_gui->query);

	g_object_get(app_gui->cur_obj, "primary_obj_id", &str_tmp, NULL);
	main_entity = (BimaEntity *) bima_get_object_by_prop(app_gui->app_data->entities,"id",str_tmp);
	g_free(str_tmp);
	varc = 0;	
	n = 0;
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);

		if ( ((main_entity) && (main_entity->name) && (g_ascii_strcasecmp(main_entity->name, qtbl->table)))  ) {
		//qtbl->table
			if (qtbl->alias)
				name = g_strdup_printf("%s",qtbl->alias);
			else
				name = g_strdup_printf("%s",qtbl->table);
			
			if (is_exists_in_local_list(name)) {
				g_free(name);		
				if (qtbl->alias)
					name = g_strdup_printf("%s%d",qtbl->alias, varc);
				else
					name = g_strdup_printf("%s%d",qtbl->table, varc);
			} else {
				append_to_local_list(name);
				varc++;
			}

			n_field = qtbl->num_fields;
			
			fprintf(ofile, "  GtkWidget *lbl_nb_%s;\n", name);
			fprintf(ofile, "  GtkWidget *child_%s_scrlw;\n", name);
			fprintf(ofile, "  GtkWidget *child_%s_tvw;\n", name);


			n++;

		}
	}
}


/**
 * cgtk_gen_def_notebook_treeview_widget
 * @ofile 		: output file stream
 * @table_name  : to specify entity/table or NULL if all table to be generate
 * @app_gui		: master gui
**/
void
cgtk_gen_def_notebook_treeview_widget(FILE *ofile, gchar *table_name, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	
	BimaEntity *main_entity;
	
	gint n,n_field, fld, n_table,tbl;
	gchar *name, *str_tmp;
	varc = 0 ;
	n_table = 0;
	// get number of query table 
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	g_object_get(app_gui->cur_obj, "primary_obj_id", &str_tmp, NULL);
	main_entity = (BimaEntity *) bima_get_object_by_prop(app_gui->app_data->entities,"id",str_tmp);

	g_free(str_tmp);
	n = 0;
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);

		// table in notebook should not same as with Primary table (main entity)
		if ( ((main_entity) && (main_entity->name) && (g_ascii_strcasecmp(main_entity->name, qtbl->table)))  ) {
			if (qtbl->alias)
				name = g_strdup_printf("%s",qtbl->alias);
			else
				name = g_strdup_printf("%s",qtbl->table);
			g_printf("\t%s\n",name);
			if (is_exists_in_local_list(name)) {
				g_free(name);		
				if (qtbl->alias)
					name = g_strdup_printf("%s%d",qtbl->alias, varc);
				else
					name = g_strdup_printf("%s%d",qtbl->table, varc);
			} else {
				append_to_local_list(name);
				varc++;
			}

			n_field = qtbl->num_fields;
	

			fprintf(ofile, "  child_%s_scrlw = gtk_scrolled_window_new (NULL, NULL);\n", name);
			fprintf(ofile, "  gtk_widget_show (child_%s_scrlw);\n", name);
			fprintf(ofile, "  gtk_container_add (GTK_CONTAINER (main_notebook), child_%s_scrlw);\n",name);
			fprintf(ofile, "  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (child_%s_scrlw), GTK_SHADOW_IN);\n",name); 
			fprintf(ofile, "  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (child_%s_scrlw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);\n",name);

			fprintf(ofile, "\n  lbl_nb_%s = gtk_label_new ((\"%s\"));\n",name,name);
			fprintf(ofile, "  gtk_widget_show (lbl_nb_%s);\n");
			fprintf(ofile, "  gtk_notebook_set_tab_label (GTK_NOTEBOOK (main_notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (main_notebook), %d), lbl_nb_%s);\n",n,name);

			fprintf(ofile, "\n  model = gtk_tree_store_new (%d ",n_field);
			for (fld=0; fld < n_field ; fld++) {
			//, G_TYPE_BOOLEAN , G_TYPE_STRING);
				fprintf(ofile, ", G_TYPE_STRING");
			}
			fprintf(ofile, ");\n");

			fprintf(ofile, "\n  child_%s_tvw = gtk_tree_view_new_with_model (model);\n",name);
			fprintf(ofile, "  g_object_unref(G_OBJECT(model));\n");

//			fprintf(ofile, "  child_%s_tvw = gtk_tree_view_new ();\n,",name);
			fprintf(ofile, "  gtk_widget_show (child_%s_tvw);\n",name);
			fprintf(ofile, "  gtk_container_add (GTK_CONTAINER (child_%s_scrlw), child_%s_tvw);\n",name,name);


			n++;
			
			// get number of query field in 
			n_field = bima_query_get_number_of_fields(app_gui->query);

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

					fprintf(ofile, "\n  column = gtk_tree_view_column_new();\n");
					fprintf(ofile, "  gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);\n");
	
					if (qfield->alias) {
						fprintf(ofile, "  gtk_tree_view_column_set_title(column,\"%s\");\n",qfield->alias);
					} else	if ((attribute) && BIMA_IS_ATTRIBUTE(attribute)) {
						fprintf(ofile, "  gtk_tree_view_column_set_title(column,\"%s\");\n",attribute->title);				
					} else {
						fprintf(ofile, "  gtk_tree_view_column_set_title(column,\"Title\");\n");				
					}
				
					fprintf(ofile, "\n  renderer = gtk_cell_renderer_text_new();\n");
					fprintf(ofile, "  gtk_tree_view_column_pack_start(column,renderer,TRUE);\n");
					fprintf(ofile, "  gtk_tree_view_column_add_attribute (column, renderer, \"text\", 1);\n");
	
					fprintf(ofile, "  gtk_tree_view_append_column(GTK_TREE_VIEW (child_%s_tvw),column);\n", name);
				}
			}
		}
	}
}


void
cgtk_gen_report_print_title(FILE *ofile, gchar *table_name, BimaAppGui *app_gui)
{
	BimaAttribute *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	
	gchar *name;
	gint n,n_field, fld, n_table,tbl, y_pos;
	n_table = 0;
	varc = 0 ;
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	n_field = bima_query_get_number_of_fields(app_gui->query);

	n=0;
	y_pos = 0 ;
	// looping for each table, to group show field base on table name
	// or one table base on table_name parameter	
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);
		if ( (table_name == NULL) || ((table_name) && (!g_ascii_strcasecmp(table_name, qtbl->table)) && (n==0))) {

			if (qtbl->alias)
				name = g_strdup_printf("%s",qtbl->alias);
			else
				name = g_strdup_printf("%s",qtbl->table);
			
			if (is_exists_in_local_list(name)) {
				g_free(name);		
				if (qtbl->alias)
					name = g_strdup_printf("%s%d",qtbl->alias, varc);
				else
					name = g_strdup_printf("%s%d",qtbl->table, varc);
			} else {
				append_to_local_list(name);
				varc++;
			}
			y_pos += 50;
			
			fprintf(ofile, "gnome_print_moveto(pc, 50,%d);\n", y_pos);
			fprintf(ofile, "gnome_print_show(pc, \"%s\");\n",name);
			
			// it's time to loop for field in table
			for (fld=0; fld < n_field ; fld++) {
				qtable = NULL;
				qfield = NULL;
			
				attribute = bima_query_get_nth_attribute(app_gui->query,fld, &qtable, &qfield);
				// tbl hsl query attr hrs sama degan tabel iterasi
				if ( (attribute) && ( 
				     ((qtable->alias) && (qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias)) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) || 
				     ((qtable->alias) && (qtbl->alias) && (!qtable->table) && (!qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias))) || 
					 ((!qtable->alias) && (!qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) 
				 	) 
			   	) {

					y_pos += 50;

					if (BIMA_IS_ATTRIBUTE(attribute)) {
						//fprintf(ofile, "gnome_print_beginpage(pc, \"1\");\n");
						fprintf(ofile, "gnome_print_moveto(pc, 75,%d);\n", y_pos);
						fprintf(ofile, "gnome_print_show(pc, \"%s\");\n",((BimaAttribute *)attribute)->title);
					}
	
					if ( BIMA_IS_FOREIGN_KEY(attribute)){
						//fprintf(ofile, "gnome_print_beginpage(pc, \"1\");\n");
						fprintf(ofile, "gnome_print_moveto(pc, 75,%d);\n", y_pos);
						fprintf(ofile, "gnome_print_show(pc, \"%s\");\n",((BimaForeignKey *)attribute)->name);	
				
						//cgtk_gen_decl_widget_an_fk(ofile, (BimaForeignKey *) attribute);
					}
				}
				n++;
			}
		}
	}
}

void
cgtk_gen_makefile(FILE *ofile, BimaAppData *app_data)
{
	GList *list;
	BimaForm *form;

	fprintf(ofile, "main: main.o interface.o");
	for (list=g_list_first(app_data->forms);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.o", form->name);
	}
	for (list=g_list_first(app_data->reports);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.o", form->name);
	}
	fprintf(ofile, "\n main.o: main.c interface.h");
	fprintf(ofile, "\n interface.o: interface.c interface.h");
	for (list=g_list_first(app_data->forms);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.c", form->name);
	}
	for (list=g_list_first(app_data->reports);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.c", form->name);
	}
	fprintf(ofile, "\n");
	for (list=g_list_first(app_data->forms);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.o : %s.c\n", form->name, form->name);
	}
	for (list=g_list_first(app_data->reports);list != NULL; list = list->next){
		form = (BimaForm *) list->data;
		fprintf(ofile, " %s.o : %s.c\n", form->name, form->name);
	}
}


static void
___finalize(GObject *obj_self)
{
	BimaCgtkPlugin *self  = BIMA_CGTK_PLUGIN (obj_self);

	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);

	if(self->name) { g_free ((gpointer) self->name); self->name = NULL; }
	if(self->author) { g_free ((gpointer) self->author); self->author = NULL; }
}

static void 
bima_cgtk_plugin_init (BimaCgtkPlugin * o )
{
	o->name = g_strdup("Cgtk Plugin");;
	o->author = g_strdup("Anas Muzakir");;
}

static void  
bima_cgtk_plugin_activate (BimaPlugin * plugin, BimaAppGui * app_gui)
{
		return;
}

static void  
bima_cgtk_plugin_deactivate (BimaPlugin * plugin, BimaAppGui * app_gui)
{
		return;
}


static int  
bima_cgtk_plugin_generate (FILE * ofile, gchar * token, BimaAppGui * app_gui)
{
	BimaEntity *main_entity=NULL;
	gint tkn_code = 0;
	gchar *str_tmp;
	varc = 0;	
	if (local_list) 
		free_local_list();
		
	local_list = NULL;
	str_tmp = NULL;
	
	//g_printf("hello generate by cgtk plugin\n");
	//g_printf("token %s\n", token);
	if (!g_ascii_strcasecmp("@VarDeclareMainButton@", token)) {
		tkn_code = 1;
		if (app_gui->app_data->forms)
			cgtk_gen_decl_main_btn(ofile, app_gui->app_data->forms);
		if (app_gui->app_data->reports)
			cgtk_gen_decl_main_btn(ofile, app_gui->app_data->reports);			
	}
	else if (!strcmp("@VarSignalMainButton@", token)) {
		tkn_code = 1;
		if (app_gui->app_data->forms)
			cgtk_gen_signal_main_btn(ofile, app_gui->app_data->forms);
		if (app_gui->app_data->reports)
			cgtk_gen_signal_main_btn(ofile, app_gui->app_data->reports);			
	}
	else if (!g_ascii_strcasecmp("@VarDefMainButton@", token)) {
		tkn_code = 1;
		if (app_gui->app_data->forms)
			cgtk_gen_defn_main_btn(ofile, app_gui->app_data->forms);
		if (app_gui->app_data->reports)
			cgtk_gen_defn_main_btn(ofile, app_gui->app_data->reports);			
	}
	else if (!g_ascii_strcasecmp("@VarDeclareWidget@", token)) {
		tkn_code = 1;
		cgtk_gen_decl_widget(ofile,NULL,app_gui);
	}
	else if (!strcmp("@VarDefWidget@", token)) {
		tkn_code = 1;
		cgtk_gen_def_widget(ofile,NULL,app_gui);
		
	}
	else if (!g_ascii_strcasecmp("@VarDeclareMainWidget@", token)) {
		tkn_code = 1;

		g_object_get(app_gui->cur_obj, "primary_obj_id", &str_tmp, NULL);
		main_entity = (BimaEntity *) bima_get_object_by_prop(app_gui->app_data->entities,"id",str_tmp);
		g_free(str_tmp);

		if ( (main_entity == NULL) || ((main_entity) && (main_entity->name == NULL)) )
			cgtk_gen_decl_widget(ofile,NULL,app_gui);
		else
			cgtk_gen_decl_widget(ofile,main_entity->name,app_gui);
	}
	else if (!strcmp("@VarDefMainWidget@", token)) {
		tkn_code = 1;

		g_object_get(app_gui->cur_obj, "primary_obj_id", &str_tmp, NULL);
		main_entity = (BimaEntity *) bima_get_object_by_prop(app_gui->app_data->entities,"id",str_tmp);
		g_free(str_tmp);

		if ( (main_entity == NULL) || ((main_entity) && (main_entity->name == NULL)) )
			cgtk_gen_def_widget(ofile,NULL,app_gui);
		else {
			//g_printf("%s = ",main_entity->name);
			cgtk_gen_def_widget(ofile,main_entity->name,app_gui);
		}
		
	} 
	else if (!g_ascii_strcasecmp("@VarDecNBTree@", token)) {
		tkn_code = 1;
		cgtk_gen_dec_notebook_treeview_widget(ofile,NULL,app_gui);
	}
	else if (!strcmp("@VarDefNBTree@", token)) {
		tkn_code = 1;
		
		g_object_get(app_gui->cur_obj, "sql_text", &str_tmp, NULL);
		g_printf("%s\n", str_tmp);
		g_free(str_tmp);
		
		cgtk_gen_def_notebook_treeview_widget(ofile,NULL,app_gui);
	}
	else if (!strcmp("@VarPrintTitle@", token)) {
		tkn_code = 1;
		cgtk_gen_report_print_title(ofile, NULL, app_gui);
	}
	else if (!strcmp("@VarMakefile@", token)) {
		tkn_code = 1;
		cgtk_gen_makefile(ofile, app_gui->app_data);
	/*
		if (diagram->forms)
			bima_gen_makefile(out_file,diagram->forms);
		if (diagram->reports)
			bima_gen_makefile(out_file,diagram->reports);
	*/
	}
	else if (!strcmp("@VarModuleGType@", token)) {
		tkn_code = 1;
		//cgtk_gen_report_print_title(ofile, NULL, app_gui);
		cgtk_gen_module_gtype(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarModuleClass@", token)) {
		tkn_code = 1;
		cgtk_gen_module_class(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarModuleFunction@", token)) {
		tkn_code = 1;
		cgtk_gen_module_function(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityGType@", token)) {
		tkn_code = 1;
		//cgtk_gen_report_print_title(ofile, NULL, app_gui);
		cgtk_gen_entity_gtype(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityClass@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_class(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityFunction@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_function(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityAttribute@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_attribute(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarKeyParam@", token)) {
		tkn_code = 1;
		cgtk_gen_key_param(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarKeyParamSql@", token)) {
		tkn_code = 1;
		cgtk_gen_key_param_sql(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarKeyParamStr@", token)) {
		tkn_code = 1;
		cgtk_gen_key_param_str(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityDataAssignment@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_data_assignment(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityDataAllAssignment@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_data_all_assignment(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityAttributeInsertList@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_attribute_list(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityAttributeInsertValues@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_attribute_insert_values(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityAttributeSetUpadte@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_attribute_set_update(ofile, app_gui ) ;
	}
	else if (!strcmp("@VarEntityKeyParamStr@", token)) {
		tkn_code = 1;
		cgtk_gen_entity_key_param_str(ofile, app_gui ) ;
	}
	else if ( !strcmp("@CGtkSetWidgetDefaultValue@", token)) {
		tkn_code = 1;
		cgtk_gen_set_widget_default_value(ofile, app_gui);

	}
	if (local_list) 
		free_local_list();
		
	local_list = NULL;

	return tkn_code;

	
//	return 0;
}


static void 
bima_cgtk_plugin_class_init (BimaCgtkPluginClass * c )
{
	GObjectClass *g_object_class  = (GObjectClass*) c;
	BimaPluginClass *plugin_class = BIMA_PLUGIN_CLASS(c);
	
	parent_class = g_type_class_ref (BIMA_TYPE_PLUGIN);
	
	g_object_class->finalize = ___finalize;

	plugin_class->activate = bima_cgtk_plugin_activate;
	plugin_class->deactivate = bima_cgtk_plugin_deactivate;
	plugin_class->generate = bima_cgtk_plugin_generate;	
}
