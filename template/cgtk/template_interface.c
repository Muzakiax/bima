
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "interface.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)


@VarSignalMainButton@

void
on_main_window_destroy (GtkObject *object, gpointer user_data)
{
	gtk_main_quit();
}


GtkWidget*
create_main_window (void)
{
  GtkWidget *main_window;
  GtkWidget *main_vbox;
  GtkWidget *main_scrlwin;
  GtkWidget *main_viewport;
  GtkWidget *main_menu_vbox;
  @VarDeclareMainButton@
  GtkWidget *main_close_btn;

  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (main_window), ("window2"));
  gtk_window_set_default_size (GTK_WINDOW (main_window), 250, 550);

  main_vbox = gtk_vbox_new (FALSE, 5);
  gtk_widget_show (main_vbox);
  gtk_container_add (GTK_CONTAINER (main_window), main_vbox);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 5);

  main_scrlwin = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (main_scrlwin);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_scrlwin, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (main_scrlwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  main_viewport = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (main_viewport);
  gtk_container_add (GTK_CONTAINER (main_scrlwin), main_viewport);

  main_menu_vbox = gtk_vbox_new (FALSE, 3);
  gtk_widget_show (main_menu_vbox);
  gtk_container_add (GTK_CONTAINER (main_viewport), main_menu_vbox);
  gtk_container_set_border_width (GTK_CONTAINER (main_menu_vbox), 3);

  @VarDefMainButton@

/*  button4 = gtk_button_new_with_mnemonic (("button4"));
  gtk_widget_show (button4);
  gtk_box_pack_start (GTK_BOX (main_menu_vbox), button4, FALSE, FALSE, 0);
*/

  main_close_btn = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_show (main_close_btn);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_close_btn, FALSE, FALSE, 0);

  g_signal_connect (G_OBJECT (main_window), "destroy",
                    G_CALLBACK (on_main_window_destroy),
                    NULL);

  g_signal_connect (G_OBJECT (main_close_btn), "clicked",
                    G_CALLBACK (on_main_window_destroy),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (main_window, main_window, "main_window");
  GLADE_HOOKUP_OBJECT (main_window, main_vbox, "main_vbox");
  GLADE_HOOKUP_OBJECT (main_window, main_scrlwin, "main_scrlwin");
  GLADE_HOOKUP_OBJECT (main_window, main_viewport, "main_viewport");
  GLADE_HOOKUP_OBJECT (main_window, main_menu_vbox, "main_menu_vbox");
//  GLADE_HOOKUP_OBJECT (main_window, button4, "button4");

  GLADE_HOOKUP_OBJECT (main_window, main_close_btn, "main_close_btn");

  return main_window;
}



