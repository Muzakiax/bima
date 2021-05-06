/***************************************************************************
 *            callback.h
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

#ifndef __BIMA_CALLBACK_H__
#define __BIMA_CALLBACK_H__

#include <gtk/gtk.h>

#ifndef __TYPEDEF_BIMA_APP_GUI__
#define __TYPEDEF_BIMA_APP_GUI__
typedef struct _BimaAppGui BimaAppGui;
#endif

void
on_step1_file_brow_btn_clicked (GtkButton       *button,
                               BimaAppGui         *bgui);

void
on_step1_file_entry_changed 	(GtkEntry *entry,
								BimaAppGui *bgui);

void
on_step1_parse_btn_clicked (GtkButton       *button,
                               BimaAppGui   *bgui);

void
on_step2_treeview_sel_changed(GtkTreeSelection       *selection,
                                BimaAppGui *bgui);

void
on_step3_treeview_sel_changed(GtkTreeSelection       *selection,
                                BimaAppGui *bgui);

gboolean
on_step2_main_treeview_event (GtkWidget  *widget,
                            GdkEvent        *event,
                            BimaAppGui *bgui);

void
on_step2_name_entry_changed 	(GtkEntry *entry,
								BimaAppGui *bgui);

gboolean
on_step2_sql_textview_focus_out(GtkWidget  *textview,
                            GdkEventFocus        *event,
                            BimaAppGui *bgui);
                            
void
on_back_button_clicked ( GtkButton *button, BimaAppGui *bgui );

void
on_forward_button_clicked (GtkButton *button, BimaAppGui *bgui);


void
on_step5_output_dir_entry_changed    (GtkEntry       *entry,
                                   BimaAppGui         *bgui);

void
on_step5_browse_button_clicked    (GtkButton       *button,
                                   BimaAppGui         *bgui);
void
on_step6_generate_button_clicked (GtkButton       *button,
                                 BimaAppGui *bgui);

void
on_popup_mnu_add_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui);

void
on_popup_mnu_remove_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui);

void
on_popup_mnu_refresh_activate (GtkMenuItem     *menuitem,
                          BimaAppGui *bgui);

#endif /*__BIMA_CALLBACK_H__*/
