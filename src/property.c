/***************************************************************************
 *            property.c
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

#include <gtk/gtk.h>
#include "bima-app-gui.h"

extern GHashTable *widget_hash_tbl;
extern GHashTable *label_hash_tbl;
extern BimaAppGui *app_gui;

static int tbl_prop_rows;
static GtkWidget *tbl_prop;
gchar *key_found;

void
bima_property_set_table_widget(GtkWidget *tbl, int rows)
{
	tbl_prop = tbl;
	tbl_prop_rows = rows;
}

GtkWidget*
bima_property_get_table_widget(int *rows)
{
	*rows = tbl_prop_rows;
	return tbl_prop;
}

gboolean
find_hash_value(const gchar *key, GtkWidget * data, GtkWidget * property)
{
	//printf("key %s... %d %d\n", key, data, property);
	if (data == property)
	{
		g_free(key_found);
		key_found = g_strdup(key);
		//printf("key found %s...\n", key);	
		return TRUE;
	}
	return FALSE;
}

gboolean
bima_property_destroy_widget(const gchar *key, GtkWidget *value, gpointer user_data)
{
//	if (key)
//		g_free(key);
	gtk_widget_destroy(value);
	return TRUE;
}

void
bima_property_empty_hash()
{
	g_hash_table_foreach_remove(widget_hash_tbl,bima_property_destroy_widget,NULL);
	g_hash_table_foreach_remove(label_hash_tbl,bima_property_destroy_widget,NULL);

}

void
bima_property_add(char *prop_name, char *label_string, GtkWidget *pwidget , GtkWidget *pbtn, char *tooltip)
{
  //GtkWidget *eventbox;
  GtkWidget *label;
  char *prop_name_dup;
   
  //eventbox = gtk_event_box_new ();
  //gtk_widget_show (eventbox);
  //gtk_table_attach (GTK_TABLE (tbl_prop), eventbox, 0, 1, tbl_prop_rows, tbl_prop_rows + 1,
  //                  (GtkAttachOptions) (GTK_FILL),
  //                  (GtkAttachOptions) (GTK_FILL), 0, 0);

  label = gtk_label_new (label_string);
  gtk_widget_show (label);
  //gtk_container_add (GTK_CONTAINER (eventbox), label);
  gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
  gtk_table_attach (GTK_TABLE (tbl_prop), label, 0, 1, tbl_prop_rows, tbl_prop_rows + 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  gtk_widget_show (pwidget);	
  if ( pbtn ) {
	  GtkWidget *hbox = gtk_hbox_new (FALSE, 0);
	  gtk_table_attach (GTK_TABLE (tbl_prop), hbox, 1, 2, tbl_prop_rows, tbl_prop_rows+1,
	                    (GtkAttachOptions) (GTK_FILL),
	                    (GtkAttachOptions) (GTK_FILL), 0, 0);

	  gtk_box_pack_start (GTK_BOX (hbox), pwidget, TRUE, TRUE, 0);

	  gtk_widget_show (pbtn);
	  gtk_box_pack_end (GTK_BOX (hbox), pbtn, FALSE, FALSE, 0);
		gtk_widget_show (hbox);  
  } else {
	  gtk_table_attach (GTK_TABLE (tbl_prop), pwidget, 1, 2, tbl_prop_rows, tbl_prop_rows+1,
	                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
	                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  } 
  tbl_prop_rows ++;
  prop_name_dup = g_strdup(prop_name);
  g_hash_table_insert(widget_hash_tbl, prop_name_dup, pwidget);
  g_hash_table_insert(label_hash_tbl, prop_name_dup, label);
}

void 
bima_property_set_string(char *prop_name, char *value)
{
	GtkWidget *widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);
	gtk_entry_set_text( GTK_ENTRY(widget), value);
}

void
on_property_changed(GtkWidget *widget, gpointer *property)
{
	gchar *value;
	if ((app_gui->cur_obj) && (g_hash_table_find(widget_hash_tbl,find_hash_value,property) != NULL) ) {
		value = gtk_entry_get_text(widget);
		g_object_set( app_gui->cur_obj, key_found, value, NULL);
		if (BIMA_IS_FORM(app_gui->cur_obj)) {
			bima_property_v_set( ((BimaForm *)(app_gui->cur_obj))->properties, key_found, value, NULL );
		} 
	}
		//g_object_set( app_gui->cur_obj, key_found, g_strdup(gtk_entry_get_text(property)), NULL);	
}

void
bima_property_add_entry( char *prop_name, char *label, char *tooltip, gchar *val)
{
  GtkWidget *prop = gtk_entry_new ();
  gtk_widget_set_usize(prop,80,-1);
  if (val)
	gtk_entry_set_text( GTK_ENTRY(prop), val);
  bima_property_add (prop_name, label, prop, NULL, NULL);
  g_signal_connect (G_OBJECT (prop), "changed",
					G_CALLBACK (on_property_changed),
					prop);
}

void
on_bool_property_toggled(GtkWidget *prop, gpointer *property)
{
	gboolean is_active;

	if ((app_gui->cur_obj) && (g_hash_table_find(widget_hash_tbl,find_hash_value,property) != NULL) ) {
		is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (prop));
		g_object_set( app_gui->cur_obj, key_found, is_active, NULL);
		if (is_active)
			gtk_button_set_label(GTK_BUTTON(prop),"Yes");
		else
			gtk_button_set_label(GTK_BUTTON(prop),"No");

	}
}

void
bima_property_add_bool( char *prop_name, char *label, char *tooltip, gboolean val)
{
	GtkWidget *prop;
	if (val)
		prop = gtk_toggle_button_new_with_label("Yes");
	else
		prop = gtk_toggle_button_new_with_label("No");

	gtk_toggle_button_set_active(prop, val);
	
	bima_property_add (prop_name, label, prop, NULL, NULL);
	g_signal_connect (G_OBJECT (prop), "toggled",
					G_CALLBACK (on_bool_property_toggled),
					prop);
}

void 
on_number_property_value_changed(GtkWidget *prop, gpointer *property)
{
	gint value;

	if ((app_gui->cur_obj) && (g_hash_table_find(widget_hash_tbl,find_hash_value,property) != NULL) ) {
		value = (gint) gtk_spin_button_get_value((GtkSpinButton *) prop );
		g_object_set( app_gui->cur_obj, key_found, value, NULL);
		if (BIMA_IS_FORM(app_gui->cur_obj)) {
			bima_property_v_set( ((BimaForm *)(app_gui->cur_obj))->properties, key_found, value, NULL );
		} 
	}

}

void
bima_property_add_number( char *prop_name, char *label, char *tooltip, gint val
						, gint min, gint max, gint step_inc, gint page_inc)
{
	GtkWidget *adj = gtk_adjustment_new (min, min, max, step_inc, page_inc, page_inc);
	GtkWidget *prop = gtk_spin_button_new (GTK_ADJUSTMENT (adj), 1, 0);
	if (val) 
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(prop) , val);

	bima_property_add (prop_name, label, prop, NULL, NULL);

	g_signal_connect (G_OBJECT (prop), "value-changed",
					G_CALLBACK (on_number_property_value_changed),
					prop);

}

void 
bima_property_set_text(char *prop_name, char *value)
{

	GtkWidget *text;
	GtkWidget *widget;
	widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);
	text = GTK_BIN(widget)->child;
	if (value) 
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)), value,-1);
	else
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)), "",-1);
}
/*
gboolean 
on_property_focus_out (GtkWidget       *widget,
                       GdkEventFocus   *event,
                       gpointer         property)
{
	GtkWidget *tmp_widget;
	GtkTextBuffer *txt_buff;
	GtkTextIter start, end;
	gchar *str_buff;
	if ((app_gui->cur_obj) && (g_hash_table_find(widget_hash_tbl,find_hash_value,property) != NULL))
	{
		txt_buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (widget));
		gtk_text_buffer_get_start_iter(txt_buff, &start);
		gtk_text_buffer_get_end_iter(txt_buff, &end);
		str_buff = gtk_text_buffer_get_text(txt_buff,&start,&end,FALSE);
		g_object_set( app_gui->cur_obj, key_found, str_buff, NULL);
	}	
	return FALSE;
}                       
*/
void 
on_property_text_changed (GtkTextBuffer       *widget,
                       gpointer         property)
{
	GtkTextIter start, end;
	gchar *str_buff;
	if ( (app_gui->cur_obj) && (g_hash_table_find(widget_hash_tbl,find_hash_value,property) != NULL) ) {
		gtk_text_buffer_get_start_iter(widget, &start);
		gtk_text_buffer_get_end_iter(widget, &end);
		str_buff = gtk_text_buffer_get_text(widget,&start,&end,FALSE);
		g_object_set( app_gui->cur_obj, key_found, str_buff, NULL);
	}
}

void
bima_property_add_text( gchar *prop_name, gchar *label, gchar *tooltip, gchar *val)
{
  GtkWidget *prop;
  GtkTextView *text;
  GtkTextBuffer *text_buff;
  
  prop = gtk_scrolled_window_new (NULL, NULL);
  text = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (text), TRUE);
  gtk_widget_show (text);

  gtk_container_add (GTK_CONTAINER (prop), text);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (prop), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_usize(prop,80,200);
  bima_property_add (prop_name, label, prop, NULL, NULL);

  text_buff = gtk_text_view_get_buffer(text);
  if (val) 
	gtk_text_buffer_set_text(text_buff, val,-1);
  else
	gtk_text_buffer_set_text(text_buff, "",-1);

  g_signal_connect (text_buff, "changed",
					G_CALLBACK (on_property_text_changed),
					prop);	
}

void 
bima_property_combo_list_add(char *prop_name, char *value)
{
	GtkWidget *widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);
	gtk_combo_box_append_text(GTK_COMBO_BOX(widget), value);
}

void
bima_property_add_combo_text( char *prop_name, char *label, char *tooltip, gchar *val)
{
    GtkWidget *prop;

	prop = gtk_combo_box_entry_new_text ();
    if (val)
		gtk_entry_set_text( GTK_ENTRY(GTK_BIN(prop)->child), val);

    g_signal_connect (GTK_ENTRY(GTK_BIN(prop)->child), "changed",
					G_CALLBACK (on_property_changed),
					prop);
    bima_property_add (prop_name, label, prop, NULL, NULL);

}

void 
bima_property_combo_model_clear(char *prop_name)
{
	GtkTreeStore *model;
	GtkTreeIter iter;

	GtkWidget *widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);

	model = GTK_TREE_STORE (gtk_combo_box_get_model(widget));
	gtk_tree_store_clear(GTK_TREE_STORE(model));

}

void 
bima_property_combo_model_set_value(char *prop_name, gchar *str_value, gint int_value)
{
	GtkTreeStore *model;
	GtkTreeIter iter;
	gboolean valid ; 
	gchar *str_val=NULL;
	gint int_val;
	gint col_number=0;
	
	GtkWidget *widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);

	gtk_combo_box_set_active(widget,-1);
	model = GTK_TREE_STORE (gtk_combo_box_get_model(widget));

	valid = gtk_tree_model_get_iter_first(model, &iter);
	while(valid) 
	{
		if (str_val)
			g_free(str_val);
			
		gtk_tree_model_get( GTK_TREE_MODEL (model), &iter,1, &str_val, 2, &int_val, -1);
		if (str_value!=NULL) {
			if (!g_ascii_strcasecmp(str_value,str_val)){
				gtk_combo_box_set_active(widget,col_number);
				break; 
			}
		}
		else {
			if (int_value == int_val ) {
				gtk_combo_box_set_active(widget,col_number);
				break;
			}
		}
		
		col_number++;
		valid = gtk_tree_model_iter_next(model, &iter);
	}
}

void 
bima_property_combo_model_list_add(char *prop_name, gchar *title, gchar *str_val, gint *int_val)
{
	GtkTreeStore *model;
	GtkTreeIter iter;

	GtkWidget *widget = (GtkWidget *) g_hash_table_lookup(widget_hash_tbl, prop_name);
	g_return_if_fail(widget != NULL);

	model = GTK_TREE_STORE (gtk_combo_box_get_model(widget));
	//gtk_tree_store_clear(GTK_TREE_STORE(model));

	gtk_tree_store_append (model,&iter,NULL);
	gtk_tree_store_set (model, &iter, 0 ,  title,1, str_val, 2, int_val, -1);

}

void
bima_property_add_combo_model( char *prop_name, char *label, char *tooltip)
{
	GtkWidget *prop;
	GtkTreeStore *model;
	GtkCellRenderer *renderer;

	model = gtk_tree_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	
	prop = gtk_combo_box_new_with_model(model);
	renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(prop), 
								renderer, TRUE );
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(prop), 
								renderer, "text",0, NULL );

    bima_property_add (prop_name, label, prop, NULL, NULL);

}
