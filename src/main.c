/***************************************************************************
 *            main.c
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "bima-entity.h"
#include "bima-app-data.h"
#include "bima-app-gui.h"
#include "bima-utils.h"

BimaAppGui *app_gui;

GHashTable *widget_hash_tbl=NULL;
GHashTable *label_hash_tbl=NULL;

void
bima_insert_parse_log(gchar *log)
{
#ifdef NO_GUI
	g_printf("%s\n",log);
#else
	gtk_text_buffer_insert_at_cursor(gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_gui->step1_text_parse))
		, log,-1);
#endif 
}

void
on_main_window_destroy (GtkObject *object, BimaAppGui *app_gui)
{
	g_object_unref(G_OBJECT(app_gui->app_data));
	gtk_main_quit();
}

int
main(int argc, char *argv[])
{
	//BimaAppData *app_data;
	/*
	BimaQuery *qry;
	BimaQueryTable *qtbl;
	gint i;
	*/
	
	gchar *s1 = g_strdup("mm");
	gchar *s2 = g_strdup("mm_ZZ");
	gchar *s3;
	
	s3 = g_strdup(s2+ g_utf8_strlen(s1,-1) );
	g_free(s1);
	s1 = g_strdup(s3);
	
	if ((!g_ascii_strcasecmp(s3, s1))) 
		g_printf("%s %s\n", s3, s1);
	
	gtk_init(&argc, &argv);
	
	widget_hash_tbl = g_hash_table_new(g_str_hash, g_str_equal);
	label_hash_tbl = g_hash_table_new(g_str_hash, g_str_equal);
	
	app_gui = (BimaAppGui *) bima_app_gui_new();
  	g_signal_connect (G_OBJECT (app_gui), "destroy",
                      G_CALLBACK (on_main_window_destroy),
                      app_gui);	
	
	if (argc == 2) {
		gtk_entry_set_text(app_gui->step1_file_entry,(const gchar*)argv[1]);
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_gui->step1_text_parse)), "Parse \n",-1);
		bima_app_data_parse_file_diagram(app_gui->app_data,(const gchar*)argv[1]);
	}
	
//	app_gui->app_data->author = g_strdup(g_get_real_name());
//	g_printf("auth %s\n", app_gui->app_data->author);	

	//app_data = bima_app_data_new();

/* 	
 	bima_sql_parser("select *  from ( select * , b.ssn from DEPARTMENT a inner join EMPLOYEE b on a.manages_Ssn = b.Ssn ) a ");
 	//bima_query_sql_parser(app_gui->query, "select *  from ( select * , b.ssn from DEPARTMENT a inner join EMPLOYEE b on a.manages_Ssn = b.Ssn ) a ");
 	g_print("num tbl : %d, sub :%d , numfield %d \n ", app_gui->query->num_tables, app_gui->query->num_sub_qry, bima_query_get_number_of_fields(app_gui->query));
 	
 	if (app_gui->query->num_sub_qry > 0) {
 		qry = ((BimaQueryTable *) (app_gui->query->tables->data))->sub_query;
 		if (!qry) 
 			exit;
 		g_print("sub num tbl : %d, sub qry :%d \n ", qry->num_tables, qry->num_sub_qry);
 		for (i = 0 ; i < qry->num_tables + qry->num_sub_qry ; i++ )  { 		
	 		qtbl = bima_query_get_nth_table(qry,i);
 			if (qtbl)
 				g_print("  tbl : %d, sub :%s as %s num_fields %d \n ", i, qtbl->table, qtbl->alias, qtbl->num_fields);
 			qtbl = NULL;
 		}
 		qry = NULL;
 	}
	if (app_gui->query != NULL) 
		g_object_unref((GObject *) (app_gui->query));
 	app_gui->query = NULL;
 	 	
	g_print("\nE N T I T Y %d \n", g_random_int_range(1,100));
//	bima_dump_object(app_gui->app_data->entities);
	g_print("\nR E L A T I O N S %d \n", g_random_int_range(1,100));
//	bima_dump_object(app_gui->app_data->relations);

*/
	gtk_widget_show ((GtkWidget *)app_gui);	

	gtk_main();
	return 0;
}
