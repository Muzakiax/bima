/***************************************************************************
 *            bima-utils.c
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

#include "bima-app-gui.h"
#include "bima-utils.h"
#include "qry_parser.h"

extern BimaAppGui *app_gui;

GList*
bima_get_l_object_by_prop(GList *list , gchar *prop, gchar* value)
{
	GObject *o;
	GList *olist;
	gchar *ovalue;
	olist = g_list_first(list);
	while (olist) {
		if (olist->data) {
			o = (GObject *)olist->data;
			g_object_get(o, prop, &ovalue, NULL);
			if ((ovalue) && (!g_ascii_strcasecmp(value, ovalue))) {
				g_free(ovalue);
				return olist;
			}
			g_free(ovalue);
		}
		olist=olist->next;
	}
	return NULL;		
}


GObject*
bima_get_object_by_prop(GList *list , gchar *prop, gchar* value)
{
	GObject *o;
	GList *olist;
	gchar *ovalue;

	olist = g_list_first(list);
	while (olist) {
		if (olist->data) {
			o = (GObject *)olist->data;
			g_object_get(o, prop, &ovalue, NULL);
			if ((ovalue) && (!g_ascii_strcasecmp(value, ovalue))) {
				g_free(ovalue);
				return o;
			}
			g_free(ovalue);
		}
		olist=olist->next;
	}
	return NULL;		
}

void 
bima_sql_parser(gchar *sql)
{
	if (app_gui->query != NULL) 
		g_object_unref((GObject *) (app_gui->query));
 	app_gui->query = NULL;

 	qry_scan_string(sql);
 	qryparse();	
 	bima_query_count_num_of_tables(app_gui->query);
 	bima_query_count_number_of_fields(app_gui->query);

}

gchar*
bima_get_class_format(gchar *str) 
{
	gchar *result = NULL , *s, *tmp;
	gint i, len;
	gboolean to_upper = TRUE;
	
	len = strlen(str);	
	tmp = g_new(char , len);
	
	i = 0 ;
	for ( s = str; *s; s++)	{
		if (( *s == '-' ) || ( *s == '_' )) {
			to_upper = TRUE;
			*s++;
		}
		if ( to_upper ) {
			tmp[i] = g_ascii_toupper(*s);
			to_upper = FALSE;
		}
		else
			tmp[i] = g_ascii_tolower(*s);
		
		i++;
	}
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}

gchar*
bima_get_function_format(gchar *str) 
{
	gchar *result = NULL , *s, *tmp;
	gint i, len;
	
	len = strlen(str);	
	tmp = g_new(char , len);
	
	i = 0 ;
	for ( s = str; *s; s++)	{
		if (( *s == '-' ) || ( *s == '_' )) {
			*s++;
		}
		tmp[i] = g_ascii_tolower(*s);
		
		i++;
	}
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}
