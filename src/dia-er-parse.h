/***************************************************************************
 *            dia-er-parse.h
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

#ifndef __DIA_ER_PARSE_H__
#define __DIA_ER_PARSE_H__
//#include <gtk/gtk.h>

#include "bima-app-data.h"

void
dia_er_parse (gchar *er_file, BimaAppData *app_dt);

void 
dia_er_parse_foreign_key(BimaAppData *app_dt) ;

#endif
