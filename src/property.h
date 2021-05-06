/***************************************************************************
 *            property.h
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
#ifndef __BIMA_PROP_H__
#define __BIMA_PROP_H__

void
bima_property_set_table_widget(GtkWidget *tbl, int rows);

GtkWidget*
bima_property_get_table_widget(int *rows);

void
bima_property_add_entry( char *prop_name, char *label, char *tooltip, gchar *val);

void
bima_property_add_text( char *prop_name, char *label, char *tooltip, gchar *val);

void
bima_property_add_combo_text( char *prop_name, char *label, char *tooltip, gchar *val);

void 
bima_property_combo_list_add(char *prop_name, char *value);

void
bima_property_add_number( char *prop_name, char *label, char *tooltip, gint val
						, gint min, gint max, gint step_inc, gint page_inc);

void
bima_property_add_bool( char *prop_name, char *label, char *tooltip, gboolean val);

void
bima_property_add_combo_model( char *prop_name, char *label, char *tooltip);

void 
bima_property_combo_model_list_add(char *prop_name, gchar *title, gchar *str_val, gint *int_val);

void 
bima_property_combo_model_clear(char *prop_name);

void
bima_property_empty_hash();

#endif
