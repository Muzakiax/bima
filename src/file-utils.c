/***************************************************************************
 *            file-utils.c
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

#include <string.h>
#include "file-utils.h"

gchar *
get_file_name_without_ext(char *file)
{
	char *tmp;
	gchar *ret;
	tmp = strchr(file, '/');
	while (tmp) {
		ret = tmp;
		tmp = strchr(tmp+1, '/');
	}
	//g_print("%s\n",get_file_name_ext(file));
	//if ( get_file_name_ext(file) != NULL )
		ret = g_strndup(ret+1, strlen(ret)- strlen(get_file_name_ext(file)) - 2 );
	//else
	//	ret = g_strndup(ret+1, strlen(ret) - 2 );
	
	return ret;
}

gchar *
get_file_name_ext(char *file)
{
	char *tmp;
	gchar *ret=NULL;
	tmp = strchr(file, '.');
	while (tmp) {
		ret = tmp;
		tmp = strchr(tmp+1, '.');
	}
	if (ret == NULL)
		ret = g_strdup("") ; //, strlen(ret)-5);
	else
		ret = g_strdup(ret+1) ; //, strlen(ret)-5);
		
	return ret;
}


gchar *
get_dir_name (char *file)
{
	char *tmp;
	gchar *ret;
	tmp = strchr(file, '/');
	
	if (!tmp)
		return g_strdup("./");
		
	while (tmp) {
		ret = tmp;
		tmp = strchr(tmp+1, '/');
	}
	ret = g_strndup(file, strlen(file) - strlen(ret) );
	return ret;
}
