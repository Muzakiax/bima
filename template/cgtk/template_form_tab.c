#include <gtk/gtk.h>


GtkWidget*
create_@VarForm(Name)@ (void)
{
  GtkWidget *widget_window;
  GtkWidget *vbox3;
  GtkWidget *scrolledwindow2;
  GtkWidget *viewport2;
  GtkWidget *widgetTable;
  GtkWidget *label_top;
  
@VarDeclareWidget@

  GtkWidget *hbuttonbox1;
  GtkWidget *btnAdd;
  GtkWidget *btnSave;
  GtkWidget *btnBack;
  GtkWidget *btnForward;
  GtkWidget *btnPreview;

  widget_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (widget_window), ("@VarForm(TITLE)@"));

  vbox3 = gtk_vbox_new (FALSE, 5);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (widget_window), vbox3);
  gtk_container_set_border_width (GTK_CONTAINER (vbox3), 5);

  label_top = gtk_label_new (("<span size=\"xx-large\">@VarForm(TITLE)@</span>"));
  gtk_widget_show (label_top);
  gtk_box_pack_start (GTK_BOX (vbox3), label_top, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label_top), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label_top), 0, 0.1);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_box_pack_start (GTK_BOX (vbox3), scrolledwindow2, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport2 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport2);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport2), GTK_SHADOW_NONE);

  widgetTable = gtk_table_new (7, 2, FALSE);
  gtk_widget_show (widgetTable);
  gtk_container_add (GTK_CONTAINER (viewport2), widgetTable);
  gtk_container_set_border_width (GTK_CONTAINER (widgetTable), 3);
  gtk_table_set_row_spacings (GTK_TABLE (widgetTable), 5);
  gtk_table_set_col_spacings (GTK_TABLE (widgetTable), 5);

@VarDefWidget@

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_start (GTK_BOX (vbox3), hbuttonbox1, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox1), 2);
  gtk_box_set_spacing (GTK_BOX (hbuttonbox1), 5);

  btnAdd = gtk_button_new_from_stock ("gtk-add");
  gtk_widget_show (btnAdd);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), btnAdd);
  GTK_WIDGET_SET_FLAGS (btnAdd, GTK_CAN_DEFAULT);

  btnSave = gtk_button_new_from_stock ("gtk-save");
  gtk_widget_show (btnSave);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), btnSave);
  GTK_WIDGET_SET_FLAGS (btnSave, GTK_CAN_DEFAULT);

  btnBack = gtk_button_new_from_stock ("gtk-go-back");
  gtk_widget_show (btnBack);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), btnBack);
  GTK_WIDGET_SET_FLAGS (btnBack, GTK_CAN_DEFAULT);

  btnForward = gtk_button_new_from_stock ("gtk-go-forward");
  gtk_widget_show (btnForward);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), btnForward);
  GTK_WIDGET_SET_FLAGS (btnForward, GTK_CAN_DEFAULT);

  btnPreview = gtk_button_new_from_stock ("gtk-print-preview");
  gtk_widget_show (btnPreview);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), btnPreview);
  GTK_WIDGET_SET_FLAGS (btnPreview, GTK_CAN_DEFAULT);

  return widget_window;
}
