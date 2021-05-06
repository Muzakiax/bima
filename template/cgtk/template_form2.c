#include <gtk/gtk.h>


GtkWidget*
create_@VarForm(Name)@ (void)
{
  GtkWidget *widget_window;
  GtkWidget *main_vbox;
  GtkWidget *main_vpaned;
  GtkWidget *master_vbox;  
  GtkWidget *main_scrolledwindow;
  GtkWidget *main_viewport;
  GtkWidget *widgetTable;
  GtkWidget *label_top;
  
@VarDeclareMainWidget@

  GtkWidget *main_notebook;
  GtkWidget *model;
  GtkWidget *column;
  GtkWidget *renderer;
      
@VarDecNBTree@

  GtkWidget *main_hbuttonbox;
  GtkWidget *btnAdd;
  GtkWidget *btnSave;
  GtkWidget *btnBack;
  GtkWidget *btnForward;
  GtkWidget *btnPreview;

  widget_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (widget_window), ("@VarForm(TITLE)@"));
  gtk_window_set_default_size (GTK_WINDOW (widget_window), 700, 500);

  main_vbox = gtk_vbox_new (FALSE, 5);
  gtk_widget_show (main_vbox);
  gtk_container_add (GTK_CONTAINER (widget_window), main_vbox);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 5);

  main_vpaned = gtk_vpaned_new ();
  gtk_widget_show (main_vpaned);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_vpaned, TRUE, TRUE, 0);

  master_vbox = gtk_vbox_new (FALSE, 5);
  gtk_widget_show (master_vbox);
  gtk_paned_pack1 (GTK_PANED (main_vpaned), master_vbox, FALSE, TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (master_vbox), 5);

  label_top = gtk_label_new (("<span size=\"xx-large\">@VarForm(TITLE)@</span>"));
  gtk_widget_show (label_top);
  gtk_box_pack_start (GTK_BOX (master_vbox), label_top, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label_top), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label_top), 0, 0.1);

  main_scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (main_scrolledwindow);
  gtk_box_pack_start (GTK_BOX (master_vbox), main_scrolledwindow, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (main_scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  main_viewport = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (main_viewport);
  gtk_container_add (GTK_CONTAINER (main_scrolledwindow), main_viewport);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (main_viewport), GTK_SHADOW_NONE);

  widgetTable = gtk_table_new (7, 2, FALSE);
  gtk_widget_show (widgetTable);
  gtk_container_add (GTK_CONTAINER (main_viewport), widgetTable);
  gtk_container_set_border_width (GTK_CONTAINER (widgetTable), 3);
  gtk_table_set_row_spacings (GTK_TABLE (widgetTable), 5);
  gtk_table_set_col_spacings (GTK_TABLE (widgetTable), 5);

@VarDefMainWidget@

  main_notebook = gtk_notebook_new ();
  gtk_widget_show (main_notebook);
  gtk_paned_pack2 (GTK_PANED (main_vpaned), main_notebook, TRUE, TRUE);

@VarDefNBTree@

/*
  child_scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (child_scrolledwindow1);
  gtk_container_add (GTK_CONTAINER (main_notebook), child_scrolledwindow1);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (child_scrolledwindow1), GTK_SHADOW_IN);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (child_scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  child_treeview1 = gtk_tree_view_new ();
  gtk_widget_show (child_treeview1);
  gtk_container_add (GTK_CONTAINER (child_scrolledwindow1), child_treeview1);

  label12 = gtk_label_new (("label12"));
  gtk_widget_show (label12);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (main_notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (main_notebook), 1), label12);
*/

  main_hbuttonbox = gtk_hbutton_box_new ();
  gtk_widget_show (main_hbuttonbox);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_hbuttonbox, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (main_hbuttonbox), 2);
  gtk_box_set_spacing (GTK_BOX (main_hbuttonbox), 5);

  btnAdd = gtk_button_new_from_stock ("gtk-add");
  gtk_widget_show (btnAdd);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), btnAdd);
  GTK_WIDGET_SET_FLAGS (btnAdd, GTK_CAN_DEFAULT);

  btnSave = gtk_button_new_from_stock ("gtk-save");
  gtk_widget_show (btnSave);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), btnSave);
  GTK_WIDGET_SET_FLAGS (btnSave, GTK_CAN_DEFAULT);

  btnBack = gtk_button_new_from_stock ("gtk-go-back");
  gtk_widget_show (btnBack);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), btnBack);
  GTK_WIDGET_SET_FLAGS (btnBack, GTK_CAN_DEFAULT);

  btnForward = gtk_button_new_from_stock ("gtk-go-forward");
  gtk_widget_show (btnForward);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), btnForward);
  GTK_WIDGET_SET_FLAGS (btnForward, GTK_CAN_DEFAULT);

  btnPreview = gtk_button_new_from_stock ("gtk-print-preview");
  gtk_widget_show (btnPreview);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), btnPreview);
  GTK_WIDGET_SET_FLAGS (btnPreview, GTK_CAN_DEFAULT);

  return widget_window;
}
