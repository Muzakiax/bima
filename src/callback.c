/***************************************************************************
 *            callback.c
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

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "callback.h"
#include "dia-er-parse.h"
#include "bma-file-parse.h"
#include "bima-app-gui.h"
#include "property.h"
#include "bima-utils.h"
#include "file-utils.h"
#include "gen-db-script.h"
#include "gen-source.h"

void
on_step1_file_entry_changed 	(GtkEntry *entry,
								BimaAppGui *bgui)
{
	// as long as step1_file_entry is permanent property,
	// we can link pointer for source_file
	//bgui->app_data->source_file = gtk_entry_get_text(entry);

}

void
on_step1_file_brow_btn_clicked (GtkButton       *button,
                               BimaAppGui         *bgui)
{
	GtkWidget *file_dlg;
	gchar *file_name ;
	
	file_dlg = gtk_file_chooser_dialog_new("Choose a File", GTK_WINDOW (bgui),
						GTK_FILE_CHOOSER_ACTION_OPEN,
						GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
						NULL);
						
	if (gtk_dialog_run(GTK_DIALOG (file_dlg)) == GTK_RESPONSE_ACCEPT ) 
	{
		file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_dlg));
		gtk_entry_set_text(bgui->step1_file_entry,file_name);
	}
	gtk_widget_destroy(file_dlg);
}

void
on_step1_parse_btn_clicked (GtkButton       *button,
                               BimaAppGui   *bgui)
{

	const gchar *file_name = NULL;
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step1_text_parse)), "Parse \n",-1);
	//
	file_name = gtk_entry_get_text(GTK_ENTRY(bgui->step1_file_entry));
	bima_app_data_parse_file_diagram(bgui->app_data,file_name);
}

void 
load_module_property(BimaAppGui *bgui) 
{
	gchar *str_val = NULL;

	g_object_get(bgui->cur_obj, "name", &str_val, NULL);
	bima_property_add_entry( "name", "Name", NULL,str_val);
	g_object_get(bgui->cur_obj, "description", &str_val, NULL);
	bima_property_add_text( "description", "Description", NULL,str_val);
}

void 
load_table_property(BimaAppGui *bgui) 
{
//	gint int_val;
	gchar *str_val = NULL;

	g_object_get(bgui->cur_obj, "abbreviation", &str_val, NULL);
	bima_property_add_entry( "abbreviation", "Abbreviation", NULL,str_val);
	g_object_get(bgui->cur_obj, "description", &str_val, NULL);
	bima_property_add_text( "description", "Description", NULL,str_val);
}

void 
load_attribute_property(BimaAppGui *bgui) 
{
	gint int_val;
	gchar *str_val = NULL;

	g_object_get(bgui->cur_obj, "title", &str_val, NULL);
	bima_property_add_entry( "title", "Title", NULL,str_val);

	g_object_get(bgui->cur_obj, "not_null", &int_val, NULL);
	bima_property_add_bool( "not_null", "Not Null", NULL, int_val);

	g_object_get(bgui->cur_obj, "field_type", &str_val, NULL);
	bima_property_add_combo_text( "field_type", "Field Type", NULL,str_val);
				
	bima_property_combo_list_add( "field_type", "varchar");
	bima_property_combo_list_add( "field_type", "integer");
	bima_property_combo_list_add( "field_type", "date");
	bima_property_combo_list_add( "field_type", "char");

	g_object_get(bgui->cur_obj, "length", &int_val, NULL);
	bima_property_add_number( "length", "Length", NULL, int_val,0,255,1,10);

	g_object_get(bgui->cur_obj, "control_type", &str_val, NULL);
	bima_property_add_combo_text( "control_type", "Control Type", NULL,str_val);
				
	bima_property_combo_list_add( "control_type", "Text");
	bima_property_combo_list_add( "control_type", "Combo Box");
	bima_property_combo_list_add( "control_type", "Check Box");
	bima_property_combo_list_add( "control_type", "Radio Button");
										
	g_object_get(bgui->cur_obj, "parameter", &str_val, NULL);
	bima_property_add_entry( "parameter", "Parameter", NULL,str_val);
	g_object_get(bgui->cur_obj, "description", &str_val, NULL);
	bima_property_add_text( "description", "Description", NULL,str_val);
}


void 
load_view_property(BimaAppGui *bgui) 
{
	gchar *str_val = NULL;

	g_object_get(bgui->cur_obj, "title", &str_val, NULL);
	bima_property_add_entry( "title", "Title", NULL,str_val);
	
	g_object_get(bgui->cur_obj, "name", &str_val, NULL);				
	gtk_entry_set_text(bgui->step2_name_entry, str_val);
	
	g_object_get(bgui->cur_obj, "sql_text", &str_val, NULL);
	if (str_val) { 
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), str_val,-1);
		//qry_scan_string(str_val);
		//qryparse();
		//g_object_unref((GObject *) (bgui->query));
	}
	else
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), "",-1);
	
	bima_property_set_table_widget(bgui->step2_page2_table, 0);
	g_object_get(bgui->cur_obj, "description", &str_val, NULL);
	bima_property_add_text( "description", "Description", NULL,str_val);
}

void
load_table_into_combo(BimaQueryTable *qry_tbl, gchar *prop_name)
{
	BimaQuery *sub_qry;
	GList *l_tmp;
	if(qry_tbl->join_type == 0) {
		if (qry_tbl->table != NULL)
			bima_property_combo_model_list_add(prop_name, qry_tbl->table, ((BimaEntity *)(qry_tbl->entity))->id, NULL);
		else {
			if (sub_qry == NULL)
				return ;
			for (l_tmp=g_list_first(sub_qry->tables);l_tmp != NULL; l_tmp = l_tmp->next){
				if (l_tmp->data) 
					load_table_into_combo((BimaQueryTable *) (l_tmp->data), prop_name);
			}
		}
	}
	else {
		load_table_into_combo(qry_tbl->left_table, prop_name);
		load_table_into_combo(qry_tbl->right_table, prop_name);
	}
}

void 
load_form_property(BimaAppGui *bgui) 
{
	gint int_val;
	gchar *str_val = NULL;
	GList *l_tmp;
	BimaQueryTable *qry_tmp;
	BimaForm * form;
	GList *list;
	BimaProperty *prop;
	
	g_object_get(bgui->cur_obj, "name", &str_val, NULL);				
	gtk_entry_set_text(bgui->step2_name_entry, str_val);

	g_object_get(bgui->cur_obj, "title", &str_val, NULL);
	bima_property_add_entry( "title", "Title", NULL,str_val);
		
	bima_property_add_combo_model("primary_obj_id", "Primary Table", NULL);
	g_object_get(bgui->cur_obj, "sql_text", &str_val, NULL);
	if (str_val) { 
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), str_val,-1);
		bima_sql_parser(str_val);
		for (l_tmp=g_list_first(bgui->query->tables);l_tmp != NULL; l_tmp = l_tmp->next){
			if (!l_tmp->data)
				break;
			qry_tmp = (BimaQueryTable *) (l_tmp->data);
			load_table_into_combo(qry_tmp,"primary_obj_id");
		}
		if ((bgui->state == STATE_REPORT) || (bgui->state == STATE_FORM)) {
			g_object_get(bgui->cur_obj, "primary_obj_id", &str_val, NULL);
			bima_property_combo_model_set_value("primary_obj_id",str_val,NULL);
		}
	}
	else
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), "",-1);
		

	bima_property_set_table_widget(bgui->step2_page2_table, 0);

	g_object_get(bgui->cur_obj, "description", &str_val, NULL);
	bima_property_add_text( "description", "Description", NULL,str_val);

	form = (BimaForm *) bgui->cur_obj;
	if (g_list_length(form->properties) > 0 )  {
		
		bima_property_v_get((form->properties),"num_of_col", &int_val,NULL);
		//v_get(GList list, const gchar *first_prop, ...) 
		//g_printf("form %d prop int_val %d\n", g_list_length(form->properties), int_val);

		for (list=g_list_first(form->properties);list != NULL; list = list->next){
			if (list->data) {
//				prop = bima_property_copy( (BimaProperty *)(list->data) );
//				self->properties = g_list_append(self->properties, (gpointer) prop);			
				bima_property_load_widget( (BimaProperty *)(list->data));

			}
		}
	}
/*
				if ( (form != NULL ) && (tform->properties != NULL) ) {
					bima_form_copy_properties(form, tform->properties );
					g_printf("cp prop %d\n", g_list_length(form->properties));	
*/
}

void
on_step2_treeview_sel_changed(GtkTreeSelection       *selection,
                                BimaAppGui *bgui)
{
	GtkTreeIter iter, parent_iter;
	GtkTreeStore *model;

	gchar *str_val = NULL;
	gchar *image_file = NULL;
	gchar *id, *parent_id=NULL, *name=NULL;
	//gchar *markup;
	bgui->cur_obj = NULL;
	
	bima_property_empty_hash();

	if (gtk_tree_selection_get_selected(selection, &model, &iter )) {
		gtk_tree_model_get( GTK_TREE_MODEL (model), &iter,0, &name, 1, &id,2 , &str_val, -1);
		
		if (gtk_tree_model_iter_parent( GTK_TREE_MODEL (model), &parent_iter, &iter)) 
			gtk_tree_model_get( GTK_TREE_MODEL (model), &parent_iter,1, &parent_id, 2, &image_file, -1);
		else
			image_file = g_strdup(str_val);
	}
	
//	if ( name != NULL )
//		gtk_label_set_markup (GTK_LABEL(bgui->step2_main_label), g_markup_printf_escaped("<span size=\"xx-large\">%s</span>",name));
	
	switch (bgui->state) {
		case STATE_PARSE:
			break;
		case STATE_TABLE:
			gtk_label_set_markup (GTK_LABEL(bgui->step2_main_label), g_markup_printf_escaped("<span size=\"xx-large\">Table</span>"));
			bima_property_set_table_widget(bgui->step2_page2_table, 0);
			gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
			if (!g_ascii_strcasecmp("MD", str_val)) {
				bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->modules, "id", id);
				if ( ! bgui->cur_obj)
					return;
				load_module_property(bgui);			
			}
			else if (!g_ascii_strcasecmp("TB", str_val)) {
				bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->entities, "id", id);
				if ( ! bgui->cur_obj)
					return;
				load_table_property(bgui);
			} 
			else if (!g_ascii_strcasecmp("AT", str_val)) {
				bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->entities, "id", parent_id);
				if (!bgui->cur_obj)	
					bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->relations, "id", parent_id);
					
				if (bgui->cur_obj)
					bgui->cur_obj = bima_get_object_by_prop(((BimaEntity *) (bgui->cur_obj))->attributes, "id", id);
				else
					return;
					
				if (!bgui->cur_obj)
					return ;
				load_attribute_property(bgui);
			}
			if (bgui->cur_obj != NULL)
				gtk_widget_set_sensitive(bgui->step2_main_notebook,TRUE);
			break;
		case STATE_VIEW:
			gtk_label_set_markup (GTK_LABEL(bgui->step2_main_label), g_markup_printf_escaped("<span size=\"xx-large\">View</span>"));

			bima_property_set_table_widget(bgui->step2_page1_table, 1);
			bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->views, "id", id);

			if (!bgui->cur_obj)	{
				gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
				gtk_entry_set_text(bgui->step2_name_entry, "");
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), "",-1);
				return;
			}
			gtk_widget_set_sensitive(bgui->step2_main_notebook,TRUE);
			load_view_property(bgui);
			break;
		case STATE_REPORT:
			gtk_label_set_markup (GTK_LABEL(bgui->step2_main_label), g_markup_printf_escaped("<span size=\"xx-large\">Report</span>"));

			bima_property_set_table_widget(bgui->step2_page1_table, 1);
			bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->reports, "id", id);
			if (!bgui->cur_obj)	{
				gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
				gtk_entry_set_text(bgui->step2_name_entry, "");
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), "",-1);
				return;
			}
			gtk_widget_set_sensitive(bgui->step2_main_notebook,TRUE);
			gtk_image_set_from_file(bgui->main_left_image,image_file);			
			load_form_property(bgui);
			break;
		case STATE_FORM:
			gtk_label_set_markup (GTK_LABEL(bgui->step2_main_label), g_markup_printf_escaped("<span size=\"xx-large\">Form</span>"));

			bima_property_set_table_widget(bgui->step2_page1_table, 1);
			bgui->cur_obj = bima_get_object_by_prop(bgui->app_data->forms, "id", id);
			if (!bgui->cur_obj)	{
				gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
				gtk_entry_set_text(bgui->step2_name_entry, "");
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(bgui->step2_sql_textview)), "",-1);
				return;
			}
			gtk_widget_set_sensitive(bgui->step2_main_notebook,TRUE);
			gtk_image_set_from_file(bgui->main_left_image,image_file);			
			
			load_form_property(bgui);
			break;
		case STATE_OPTION:
			break;
		case STATE_GENERATE:
			break;

	}
	if (str_val)
		g_free(str_val);
	if (image_file)
		g_free(image_file);
}

gboolean
on_step2_main_treeview_event (GtkWidget  *widget,
                            GdkEvent        *event,
                            BimaAppGui *bgui)
{
	GdkEventButton *eb ;
	
	g_return_val_if_fail(GTK_IS_TREE_VIEW (widget),FALSE);
	
	if(!event)
		return FALSE;	
	
	if (event->type == GDK_BUTTON_PRESS){
		if (((GdkEventButton *) event)->button != 3) 
			return FALSE;
		
		eb = (GdkEventButton *) event;
		//eb->button = 1;

		switch (bgui->state) {
			case STATE_PARSE:
				break;
			case STATE_TABLE:
				break;
			case STATE_VIEW:
				gtk_menu_popup(GTK_MENU(bgui->popup_menu),
					NULL,NULL,NULL,NULL,eb->button ,eb->time);
				break;
			case STATE_REPORT:
				gtk_menu_popup(GTK_MENU(bgui->popup_menu),
					NULL,NULL,NULL,NULL,eb->button ,eb->time);		
				break;
			case STATE_FORM:
				gtk_menu_popup(GTK_MENU(bgui->popup_menu),
					NULL,NULL,NULL,NULL,eb->button ,eb->time);
				break;
			case STATE_OPTION:
				break;
			case STATE_GENERATE:
				break;
		}

		return TRUE;
	}
	return FALSE;
}

void
on_step2_name_entry_changed 	(GtkEntry *entry,
								BimaAppGui *bgui)
{
	if (!bgui->cur_obj)
		return ;

	g_object_set( bgui->cur_obj, "name", gtk_entry_get_text(entry), NULL);
		
}

gboolean
on_step2_sql_textview_focus_out(GtkWidget  *textview,
                            GdkEventFocus        *event,
                            BimaAppGui *bgui)
{
	GtkTextBuffer *txt_buff;
	GtkTextIter start, end;
	GList *l_tmp;
	BimaQueryTable *qry_tmp;
	gchar *str_val;

	if (!bgui->cur_obj)
		return ;
	str_val = NULL;
	txt_buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
	gtk_text_buffer_get_start_iter(txt_buff, &start);
	gtk_text_buffer_get_end_iter(txt_buff, &end);
	g_object_set( bgui->cur_obj, "sql_text", gtk_text_buffer_get_text(txt_buff,&start,&end,FALSE), NULL);

	//if (bgui->query != NULL) 
	//	g_object_unref((GObject *) (bgui->query));
 	//bgui->query = NULL;

 	//qry_scan_string(gtk_text_buffer_get_text(txt_buff,&start,&end,FALSE));
 	//qryparse();
 	bima_sql_parser(gtk_text_buffer_get_text(txt_buff,&start,&end,FALSE));
	if ((bgui->state == STATE_REPORT) || (bgui->state == STATE_FORM)) {
		for (l_tmp=g_list_first(bgui->query->tables);l_tmp != NULL; l_tmp = l_tmp->next){
			if (!l_tmp->data)
				break;
			qry_tmp = (BimaQueryTable *) (l_tmp->data);
			load_table_into_combo(qry_tmp,"primary_obj_id");
		}

		g_object_get(bgui->cur_obj, "primary_obj_id", &str_val, NULL);
		bima_property_combo_model_set_value("primary_obj_id",str_val,NULL);
	}
	g_free(str_val);
	return FALSE;
}                            


void 
load_option_property(BimaAppGui *bgui) //step 5
{
	gint int_val;
	gchar *str_val = NULL;

	bima_property_set_table_widget(bgui->step5_left_table, 0);

	g_object_get(bgui->cur_obj, "project_name", &str_val, NULL);
	bima_property_add_entry( "project_name", "Project Name", NULL,str_val);

	g_object_get(bgui->cur_obj, "author", &str_val, NULL);
	bima_property_add_entry( "author", "Author", NULL,str_val);

	g_object_get(bgui->cur_obj, "version", &str_val, NULL);
	bima_property_add_entry( "version", "Version", NULL,str_val);

	bima_property_set_table_widget(bgui->step5_right_table, 0);

	g_object_get(bgui->cur_obj, "db_type", &int_val, NULL);
	bima_property_add_combo_model( "db_type", "DB Type", NULL);
	bima_property_combo_model_list_add("db_type", "Postgresql",NULL,DB_POSTGRESQL);
	bima_property_combo_model_list_add("db_type", "MySql",NULL,DB_MYSQL);
	bima_property_combo_model_list_add("db_type", "Oracle",NULL,DB_ORACLE);
	bima_property_combo_model_set_value("db_type", NULL, int_val);
	
	g_object_get(bgui->cur_obj, "db_name", &str_val, NULL);
	bima_property_add_entry( "db_name", "DB Name", NULL,str_val);

	g_object_get(bgui->cur_obj, "db_user_name", &str_val, NULL);
	bima_property_add_entry( "db_user_name", "DB User Name", NULL,str_val);

	g_object_get(bgui->cur_obj, "db_user_pass", &str_val, NULL);
	bima_property_add_entry( "db_user_pass", "DB Password", NULL,str_val);

}

void
on_step5_output_dir_entry_changed (GtkEntry       *entry,
                                   BimaAppGui      *bgui)
{
	/*
	if (bgui->app_data->output_dir != NULL)
		g_free(bgui->app_data->output_dir); 
	bgui->app_data->output_dir = g_strdup(gtk_entry_get_text(entry));
	*/
	// as long as step5_output_dir_entry is permanent property,
	// we can link pointer 
	bgui->app_data->output_dir = gtk_entry_get_text(entry);
}

void
on_step5_browse_button_clicked    (GtkButton       *button,
                                   BimaAppGui         *bgui)
{
	GtkWidget *dir_dlg;
	gchar *dir_name ;
	
	dir_dlg = gtk_file_chooser_dialog_new("Choose Direktory", GTK_WINDOW (bgui),
						GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
						GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
						NULL);
						
	if (gtk_dialog_run(GTK_DIALOG (dir_dlg)) == GTK_RESPONSE_ACCEPT ) 
	{
		dir_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dir_dlg));
		gtk_entry_set_text(bgui->step5_output_dir_entry,dir_name);
	}
	gtk_widget_destroy(dir_dlg);
}

void
on_back_button_clicked ( GtkButton *button, BimaAppGui *bgui )
{
	BimaState new_state;
	
	new_state = bgui->state - 1;	

	bgui->state = new_state;
	bima_app_gui_show_current_state(bgui);
	if (!bgui->cur_obj)
		gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
		
	gtk_widget_set_sensitive(bgui->back_button,(new_state > 0));
	gtk_widget_set_sensitive(bgui->forward_button,(new_state < STATE_GENERATE));
//	gtk_notebook_set_current_page(bgui->main_notebook,new_state);
//	bgui->state = new_state ;

}

void
on_forward_button_clicked (GtkButton *button, BimaAppGui *bgui )
{
	GtkTreeStore *model;
	GtkTreeIter iter;
	gchar *text_str;
	BimaState new_state;
	
	new_state = bgui->state + 1 ;
	bima_property_empty_hash();
	bgui->state = new_state;
	bima_app_gui_show_current_state(bgui);
	if (!bgui->cur_obj)
		gtk_widget_set_sensitive(bgui->step2_main_notebook,FALSE);
	switch (new_state) {
		case STATE_TABLE:
			if (gtk_combo_box_get_active_iter(bgui->step1_app_combo, &iter)) {
				model = GTK_TREE_STORE (gtk_combo_box_get_model(bgui->step1_app_combo));
				gtk_tree_model_get( GTK_TREE_MODEL (model), &iter,1, &text_str, -1);

				if (bgui->app_data->template == NULL) {
					bgui->app_data->template = bima_template_new() ;
					bima_template_load_from_file(bgui->app_data->template,text_str);
					//g_printf("%s\n",get_dir_name(text_str));
				}
				// else if ( g_ascii_strcasecmp(bgui->app_data->template->file_name, text_str ) )
				//}
			}
			break;
		case STATE_OPTION:
			load_option_property(bgui);
			break;
	}

	gtk_widget_set_sensitive(bgui->back_button,(new_state > STATE_PARSE));
	gtk_widget_set_sensitive(bgui->forward_button,(new_state < STATE_GENERATE));	

}

void
on_step6_generate_button_clicked (GtkButton       *button,
                                 BimaAppGui *bgui)
{
	BimaEntity *entity = NULL;
	//BimaForeignKey *fk,*fk2;
	//BimaAttribute *attr;
	//BimaRelation *relation;
	BimaForm *form = NULL;
	BimaTemplateForm *tform = NULL;
	//FILE *tfile, *ofile;
	GList *flist, *tlist ;

	GtkTreeIter iter;
	GtkTreeStore *model;
	GdkColor  blue_color, red_color;
	gint i, err_status =0 ;
	gchar *str_tmp=NULL;
	gchar *prefix=NULL, *suffix=NULL;
		
	gdk_color_parse("Blue", &blue_color);
	gdk_color_parse("Red", &red_color);

	model = GTK_TREE_STORE (gtk_tree_view_get_model(bgui->step6_generate_treeview));
	gtk_tree_store_clear(GTK_TREE_STORE(model));
	
	gtk_tree_store_append ( model,&iter,NULL);
	gtk_tree_store_set (model, &iter, 0 , "Generating",-1);

	// write Bma file
	gtk_tree_store_append ( model,&iter,NULL);
	gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Bima File : %s.bma ",bgui->app_data->project_name), -1);

	err_status = bima_app_data_write_to_xml(bgui->app_data, g_strdup_printf("%s/%s.bma",bgui->app_data->output_dir, bgui->app_data->project_name));
	if (err_status == 0) 
		gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Bima File : %s.bma .... Done",bgui->app_data->project_name), 1, &blue_color, -1);
	else
		gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Bima File : %s.bma .... Fail",bgui->app_data->project_name), 1, &red_color, -1);


	// write DB sql script
	gtk_tree_store_append ( model,&iter,NULL);
	gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Sql File : %s.sql ",bgui->app_data->project_name), -1);

	err_status = gen_db_script(g_strdup_printf("%s/%s.sql",bgui->app_data->output_dir, bgui->app_data->project_name), bgui->app_data);
	if (err_status == 0) 
		gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Sql File : %s.sql .... Done",bgui->app_data->project_name), 1, &blue_color, -1);
	else
		gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Sql File : %s.sql .... Fail",bgui->app_data->project_name), 1, &red_color, -1);

	// write Code of each entity 

	if (bgui->app_data->template->tentities) {
		tform = (BimaTemplateForm *) bgui->app_data->template->tentities->data;
	//	if (tform == NULL ) break;

		for (flist=g_list_first(bgui->app_data->entities);flist != NULL; flist = flist->next) {
			entity = (BimaEntity *) flist->data;
			
			bgui->cur_obj = (GObject *) entity;
			
			//if (bgui->query != NULL) 
			//	g_object_unref((GObject *) (bgui->query));
		 	//bgui->query = NULL;

		 	//qry_scan_string(g_strdup_printf("select * from %s ", g_ascii_strdown(entity->name,-1)));
 			//qryparse();	
			bima_sql_parser(g_strdup_printf("select * from %s ", g_ascii_strdown(entity->name,-1)));
			
			gtk_tree_store_append ( model,&iter,NULL);
			gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Entity File : %s ",entity->name), -1); 

			for (tlist = g_list_first(tform->template_file);tlist != NULL; tlist = tlist->next) {			
				if (strlen(get_file_name_ext(tlist->data)) > 0 ) {
					err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *) tlist->data),
						g_strdup_printf("%s/%s.%s", bgui->app_data->output_dir,g_ascii_strdown(entity->name,-1),get_file_name_ext(tlist->data)),bgui);
				}
				else {
					err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *) tlist->data),
						g_strdup_printf("%s/%s", bgui->app_data->output_dir,g_ascii_strdown(entity->name,-1)),bgui);
				}
				if (err_status != 0 ) break;
			}
			if (err_status == 0) 
				gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Entity File : %s .... Done",g_ascii_strdown(entity->name,-1)), 1, &blue_color, -1);
			else 
				gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Entity File : %s .... Fail",g_ascii_strdown(entity->name,-1)), 1, &red_color, -1);

		}
		entity = NULL;
	}
	
	//
	for(i = 1; i <=2 ; i++ ) { 
		if (i == 1) { 
			flist = g_list_first(bgui->app_data->forms);
			str_tmp = g_strdup("form");
		} else {
			flist = g_list_first(bgui->app_data->reports);
			str_tmp = g_strdup("report");
		}
		
		for (;flist != NULL; flist = flist->next) {
			form = (BimaForm *) flist->data;
			bgui->cur_obj = (GObject *) form;
			tform = NULL;

			//if (bgui->query != NULL) 
			//	g_object_unref((GObject *) (bgui->query));
		 	//bgui->query = NULL;

		 	//qry_scan_string(form->sql_text);
 			//qryparse();	
			bima_sql_parser(form->sql_text);
			gtk_tree_store_append ( model,&iter,NULL);
			gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave %s File : %s ",str_tmp,form->name), -1); 
			
			if (i==1) 				
				tform = (BimaTemplateForm *) bima_get_object_by_prop(bgui->app_data->template->tforms,"id",form->template_id);
			else 
				tform = (BimaTemplateForm *) bima_get_object_by_prop(bgui->app_data->template->treports,"id",form->template_id);

			if (tform == NULL ) break;

			for (tlist = g_list_first(tform->template_file);tlist != NULL; tlist = tlist->next) {
				
				if (strlen(get_file_name_ext(tlist->data)) > 0 ) {
					err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *)tlist->data),
						g_strdup_printf("%s/%s.%s", bgui->app_data->output_dir,form->name,get_file_name_ext(tlist->data)),bgui);
				}
				else {
					err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *)tlist->data),
						g_strdup_printf("%s/%s", bgui->app_data->output_dir,form->name),bgui);
				}
				if (err_status != 0 ) break;
			}
			if (err_status == 0) 
				gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave %s File : %s .... Done",str_tmp,form->name), 1, &blue_color, -1);
			else 
				gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave %s File : %s .... Fail",str_tmp,form->name), 1, &red_color, -1);
		}
		g_free(str_tmp);
	}


	for (tlist=g_list_first(bgui->app_data->template->tadditions);tlist != NULL; tlist = tlist->next) {

		tform = (BimaTemplateForm *) tlist->data;
//		if (tform == NULL ) break;

		gtk_tree_store_append ( model,&iter,NULL);
		gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Addition File : %s ",tform->name), -1); 

		for (flist = g_list_first(tform->template_file);flist != NULL; flist = flist->next) {			
			if (strlen(get_file_name_ext(flist->data)) > 0 ) {
				err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *)flist->data),
					g_strdup_printf("%s/%s.%s", bgui->app_data->output_dir,tform->name,get_file_name_ext(flist->data)),bgui);
			}
			else {
				err_status = gen_source(g_strdup_printf("%s/%s", bgui->app_data->template->directory,(gchar *)flist->data),
					g_strdup_printf("%s/%s", bgui->app_data->output_dir,tform->name),bgui);
			}
			if (err_status != 0 ) break;
		}
		if (err_status == 0) 
			gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Addition File : %s .... Done",tform->name), 1, &blue_color, -1);
		else 
			gtk_tree_store_set (model, &iter, 0 , g_strdup_printf("\tSave Addition File : %s .... Fail",tform->name), 1, &red_color, -1);
	}

}

void
on_popup_mnu_add_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui)
{
	BimaView *view;
	BimaForm *form;
	GtkTreeIter iter, parent_iter;
	GtkTreeStore *model;
//	GtkWidget *tree;
	GtkTreeSelection *selection;
	GList *list;
	
	gchar *id;

	selection = gtk_tree_view_get_selection(bgui->step2_main_treeview);
	if (gtk_tree_selection_get_selected(selection, &model, &iter )) {
		if  (gtk_tree_model_iter_parent( GTK_TREE_MODEL (model), &parent_iter, &iter))  {
			gtk_tree_model_get( GTK_TREE_MODEL (model), &parent_iter, 1, &id, -1);
		} 	
		else {
			gtk_tree_model_get( GTK_TREE_MODEL (model), &iter, 1, &id, -1);
			parent_iter = iter;
		}
						
		switch (bgui->state) {
			case STATE_VIEW:
				view = bima_app_data_create_new_view( bgui->app_data, id);
				if (view == NULL) 
								form = bima_app_data_create_new_report( bgui->app_data,NULL, id);
				if (view == NULL) 
					return ;
					
				gtk_tree_store_append ( model,&iter ,&parent_iter );
				gtk_tree_store_set (model, &iter, 0, form->name,1, form->id, 2, "report", -1);	return ;
					
				gtk_tree_store_append ( model,&iter ,&parent_iter );
				gtk_tree_store_set (model, &iter, 0, view->name,1, view->id, 2, "view", -1);
				//g_printf("new entity %s = %s \n", view->primary_obj_id,id);
				break;
			case STATE_REPORT:
				form = bima_app_data_create_new_report( bgui->app_data,NULL, id);
				if (view == NULL) 
					return ;
					
				gtk_tree_store_append ( model,&iter ,&parent_iter );
				gtk_tree_store_set (model, &iter, 0, form->name,1, form->id, 2, "form", -1);
				break;
			case STATE_FORM:
				form = bima_app_data_create_new_form( bgui->app_data,NULL, id);
				if (view == NULL) 
					return ;
					
				gtk_tree_store_append ( model,&iter ,&parent_iter );
				gtk_tree_store_set (model, &iter, 0, form->name,1, form->id, 2, "form", -1);

				break;
		}
		g_free(id);
	}
	view = NULL;
}

void
on_popup_mnu_remove_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui)
{
	GtkTreeIter iter, parent_iter;
	GtkTreeStore *model;
//	GtkWidget *tree;
	GtkTreeSelection *selection;
	GList *list;
	
//	gchar *parent_id;
	gchar *id;

	selection = gtk_tree_view_get_selection(bgui->step2_main_treeview);
	if (gtk_tree_selection_get_selected(selection, &model, &iter )) {
		if  (gtk_tree_model_iter_parent( GTK_TREE_MODEL (model), &parent_iter, &iter))  {
			gtk_tree_model_get( GTK_TREE_MODEL (model), &iter, 1, &id, -1);
		}
		else  
			return;

		switch (bgui->state) {
			case STATE_VIEW:
				bima_app_data_delete_view(bgui->app_data, id);
				break;
			case STATE_REPORT:
				bima_app_data_delete_report(bgui->app_data, id);
				break;
			case STATE_FORM:
				bima_app_data_delete_form(bgui->app_data, id);
				break;
		}
		g_free(id);
		bgui->cur_obj = NULL;
		gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
	}
}

void
on_popup_mnu_refresh_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui)
{
	bima_app_gui_show_current_state(bgui);

}
