/***************************************************************************
 *            bima-utils.h
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

#ifndef __BIMA_UTILS_H__
#define __BIMA_UTILS_H__

#include <glib.h>
#include <glib-object.h>

GList *
bima_get_l_object_by_prop(GList *list , gchar *prop, gchar* value);

GObject *
bima_get_object_by_prop(GList *list , gchar *prop, gchar* value);

void 
bima_sql_parser(gchar *sql);

gchar* bima_get_class_format(gchar *str) ;
gchar* bima_get_function_format(gchar *str) ;

#endif
