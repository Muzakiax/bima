#include "@StrLower(Name)@.h"
#include "department.h"
#include "employee.h"
 
static void @StrLower(Name)@_class_init(@FirstUpper(Name)@Class *klass);
static void @StrLower(Name)@_init(@FirstUpper(Name)@ *sp);
static void @StrLower(Name)@_finalize(GObject *object);

struct _@FirstUpper(Name)@Private {
	/* Place Private Members Here */
};

typedef struct _@FirstUpper(Name)@Signal @FirstUpper(Name)@Signal;
typedef enum _@FirstUpper(Name)@SignalType @FirstUpper(Name)@SignalType;

enum _@FirstUpper(Name)@SignalType {
	/* Place Signal Types Here */  
	SIGNAL_TYPE_EXAMPLE,
	LAST_SIGNAL
};

struct _@FirstUpper(Name)@Signal {
	@FirstUpper(Name)@ *object;
};

static guint @StrLower(Name)@_signals[LAST_SIGNAL] = { 0 };
static GtkWindowClass *parent_class = NULL;

extern GdaConnection *connection;
static ErDemo1@FirstUpper(Name)@@FirstUpper(Suffix)@ *entity=NULL;

GType
@StrLower(Name)@_get_type()
{
	static GType type = 0;

	if(type == 0) {
		static const GTypeInfo our_info = {
			sizeof (@FirstUpper(Name)@Class),
			NULL,
			NULL,
			(GClassInitFunc)@StrLower(Name)@_class_init,
			NULL,
			NULL,
			sizeof (@FirstUpper(Name)@),
			0,
			(GInstanceInitFunc)@StrLower(Name)@_init,
		};

		type = g_type_register_static(GTK_TYPE_WINDOW, 
			"@FirstUpper(Name)@", &our_info, 0);
	}

	return type;

}

static void
@StrLower(Name)@_class_init(@FirstUpper(Name)@Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	parent_class = g_type_class_peek_parent(klass);
	object_class->finalize = @StrLower(Name)@_finalize;
	
	/* Create signals here:
	   @StrLower(Name)@_signals[SIGNAL_TYPE_EXAMPLE] = g_signal_new(...)
 	*/
}

static void
@StrLower(Name)@_init(@FirstUpper(Name)@ *self)
{
	GError *error = NULL;
	__create_gui(self) ;
	self->is_edit = FALSE;
	self->is_add = FALSE;
	g_printf("init ...\n");

	self->list = @Lower(EntityModuleId)@_@Lower(EntityName)@_get_data_all(connection, &error);
	if (self->list == NULL) 
		return;
	if (self->list->data)
		@StrLower(Name)@_show_data(self, (@Lower(EntityModuleId)@@FirstUpper(EntityName)@ *)(self->list->data));

	gtk_widget_set_sensitive(self->btnBack, FALSE);
	//obj->priv = g_new0(@FirstUpper(Name)@Private, 1);
	/* Initialize private members, etc. */
}

void 
@StrLower(Name)@_show_empty_data(@FirstUpper(Name)@ *self) 
{
/*
	@CGtkSetWidgetDefaultValue@
*/
	gtk_entry_set_text(self->txt_Number,"");
	gtk_entry_set_text(self->txt_Name,"");
	gtk_entry_set_text(self->txt_NumberOfEmployees,"");
	gtk_entry_set_text(self->txt_Locations,"");
	gtk_entry_set_text(self->txt_StartDate,"");
	gtk_combo_box_set_active(self->cmb_fk_manages,-1);

/*
  gchar *manages_ssn;
  
  GtkWidget *cmb_fk_manages_model;
  GtkWidget *cmb_fk_manages_renderer;
  GtkWidget *cmb_fk_manages;
*/
}


void 
@StrLower(Name)@_show_data(@FirstUpper(Name)@ *self, ErDemo1@FirstUpper(Name)@ *entity) 
{
	GtkTreeStore *model;
	GtkTreeIter iter;
	gboolean valid;
	gchar *id ; 

/*
	@CgtkFormInputShowData
*/
	gtk_entry_set_text(self->txt_Number,g_strdup_printf("%d", entity->number));
	gtk_entry_set_text(self->txt_Name,entity->name);
	gtk_entry_set_text(self->txt_NumberOfEmployees,g_strdup_printf("%d", entity->numberofemployees));
	if	(entity->locations)
		gtk_entry_set_text(self->txt_Locations,g_strdup(entity->locations));
	else 
		gtk_entry_set_text(self->txt_Locations,"");
	gtk_entry_set_text(self->txt_StartDate,g_strdup_printf("%d-%d-%d",  entity->manages_startdate->month, entity->manages_startdate->day, entity->manages_startdate->year));

	gtk_combo_box_set_active(self->cmb_fk_manages,-1);
	
	model = GTK_TREE_STORE (gtk_combo_box_get_model(self->cmb_fk_manages));
	valid = gtk_tree_model_get_iter_first(model, &iter);
	while (valid && entity->manages_ssn) 
	{
		gtk_tree_model_get( GTK_TREE_MODEL (model), &iter, 1, &id, -1);
		
		if (!g_ascii_strcasecmp(id, entity->manages_ssn)) {
			gtk_combo_box_set_active_iter(self->cmb_fk_manages,&iter);
		}
		
		valid = gtk_tree_model_iter_next(model, &iter);
	}
}

void
on_txt_locations_changed (GtkEntry *entry,
						@FirstUpper(Name)@ *self)
{
	if (entity == NULL ) 
		return ;
		
	if (self->list == NULL)
		return;
	//entity = (ErDemo1@FirstUpper(Name)@@FirstUpper(Suffix)@ *) self->list->data;
	if (strlen(gtk_entry_get_text(entry))>0){
		//g_printf("%s-%s-\n",entity->locations,g_strdup(gtk_entry_get_text(entry)));
		g_free(entity->locations);
		entity->locations = g_strdup(gtk_entry_get_text(entry));
	} else {
		g_free(entity->locations);
		entity->locations =NULL;
	}
}

void
on_btnAdd_clicked ( GtkButton       *button,
                        @FirstUpper(Name)@   *self)
{
	if ((self->is_edit) || (self->is_add)) {
	  // cancel
	  gtk_button_set_label(self->btnEdit, "gtk-edit");
	  gtk_button_set_label(button, "gtk-add");
	  gtk_widget_set_sensitive((GtkWidget *)self->btnBack, TRUE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnForward, TRUE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnPreview, TRUE);
	  self->is_edit = FALSE;
	  self->is_add = FALSE;
	  g_object_unref((GObject *)entity);
	  entity = NULL;
	  @StrLower(Name)@_show_data(self, (@Lower(EntityModuleId)@@FirstUpper(EntityName)@ *)(self->list->data));	  
	} else {
	  gtk_button_set_label(self->btnEdit, "gtk-save");
	  gtk_button_set_label(button, "gtk-cancel");
	  gtk_widget_set_sensitive((GtkWidget *)self->btnBack, FALSE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnForward, FALSE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnPreview, FALSE);	  
	  entity = @Lower(EntityModuleId)@_@Lower(EntityName)@_new();
	  @StrLower(Name)@_show_data(self, entity);	  
	  self->is_add = TRUE;
	} 
}

void
on_btnEdit_clicked ( GtkButton       *button,
                        @FirstUpper(Name)@   *self)
{
	GError *error = NULL;
	
	if ((self->is_edit) || (self->is_add)) {
		// save now ...
		if ((self->is_edit) && (entity)) {
		    @Lower(EntityModuleId)@_@Lower(EntityName)@_update_data(entity, connection, &error);
		    g_object_unref((GObject *) self->list->data);
		    self->list->data = (gpointer) entity;
		    entity = NULL;
	  	} else if ((self->is_add) && (entity)) {
		    @Lower(EntityModuleId)@_@Lower(EntityName)@_insert_data(entity, connection, &error);
		    g_object_unref((GObject *) entity);
		    entity = NULL;
		}

	  gtk_button_set_label(button, "gtk-edit");
	  gtk_button_set_label(self->btnAdd, "gtk-add");
	  gtk_widget_set_sensitive((GtkWidget *)self->btnBack, TRUE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnForward, TRUE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnPreview, TRUE);
	  self->is_edit = FALSE;
	  self->is_add = FALSE;
	} else {
	  gtk_button_set_label(button, "gtk-save");
	  gtk_button_set_label(self->btnAdd, "gtk-cancel");
	  gtk_widget_set_sensitive((GtkWidget *)self->btnBack, FALSE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnForward, FALSE);
	  gtk_widget_set_sensitive((GtkWidget *)self->btnPreview, FALSE);	  
	  self->is_edit = TRUE;
	  entity = @Lower(EntityModuleId)@_@Lower(EntityName)@_copy((@Lower(EntityModuleId)@@FirstUpper(EntityName)@ *) self->list->data);
	  @StrLower(Name)@_show_data(self, entity);
	} 
}

void
on_btnForward_clicked ( GtkButton       *button,
                        @FirstUpper(Name)@   *self)
{
	if (self->list->next == NULL) {
		gtk_widget_set_sensitive(button, FALSE);
		return;
	}

	self->list = self->list->next;
	if (self->list->data)
		@StrLower(Name)@_show_data(self, (@Lower(EntityModuleId)@@FirstUpper(EntityName)@ *)(self->list->data));

	if (self->list->prev != NULL) 
		gtk_widget_set_sensitive(self->btnBack, TRUE);

}


void
on_btnBack_clicked ( GtkButton       *button,
                        @FirstUpper(Name)@   *self)
{
	if (self->list->prev == NULL) {
		gtk_widget_set_sensitive(button, FALSE);
		return;
	}
	
	self->list = self->list->prev;
	if (self->list->data)
		@StrLower(Name)@_show_data(self, (@Lower(EntityModuleId)@@FirstUpper(EntityName)@ *)(self->list->data));

	if (self->list->next != NULL) 
		gtk_widget_set_sensitive(self->btnForward, TRUE);

}

void
__create_gui(@FirstUpper(Name)@ *self) 
{  
  GtkWidget *main_vbox;
  GtkWidget *main_scrolledwindow;
  GtkWidget *main_viewport;
  GtkWidget *widgetTable;
  GtkWidget *label_top;

  GtkWidget *main_hbuttonbox;
  
  main_vbox = gtk_vbox_new (FALSE, 5);
  gtk_widget_show (main_vbox);
  gtk_container_add (GTK_CONTAINER (self), main_vbox);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 5);

  label_top = gtk_label_new (("<span size=\"xx-large\">@Title@</span>"));
  gtk_widget_show (label_top);
  gtk_box_pack_start (GTK_BOX (main_vbox), label_top, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label_top), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label_top), 0, 0.1);

  main_scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (main_scrolledwindow);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_scrolledwindow, TRUE, TRUE, 0);
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

  self->lbl_@Upper(Name)@ = gtk_label_new (("<b>DEPARTMENT</b>"));
  gtk_widget_show (self->lbl_@Upper(Name)@);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_@Upper(Name)@, 0, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (self->lbl_@Upper(Name)@), TRUE);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_@Upper(Name)@), 0, 0.5);
  self->lbl_Number = gtk_label_new (("Number : "));
  gtk_widget_show (self->lbl_Number);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_Number, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_Number), 0, 0.5);
  self->txt_Number = gtk_entry_new ();
  gtk_widget_show (self->txt_Number);
  gtk_table_attach (GTK_TABLE (widgetTable), self->txt_Number, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  self->lbl_Name = gtk_label_new (("Name : "));
  gtk_widget_show (self->lbl_Name);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_Name, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_Name), 0, 0.5);
  self->txt_Name = gtk_entry_new ();
  gtk_widget_show (self->txt_Name);
  gtk_table_attach (GTK_TABLE (widgetTable), self->txt_Name, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  self->lbl_NumberOfEmployees = gtk_label_new (("NumberOfEmployees : "));
  gtk_widget_show (self->lbl_NumberOfEmployees);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_NumberOfEmployees, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_NumberOfEmployees), 0, 0.5);
  self->txt_NumberOfEmployees = gtk_entry_new ();
  gtk_widget_show (self->txt_NumberOfEmployees);
  gtk_table_attach (GTK_TABLE (widgetTable), self->txt_NumberOfEmployees, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  self->lbl_Locations = gtk_label_new (("Locations : "));
  gtk_widget_show (self->lbl_Locations);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_Locations, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_Locations), 0, 0.5);
  self->txt_Locations = gtk_entry_new ();
  gtk_widget_show (self->txt_Locations);
  gtk_table_attach (GTK_TABLE (widgetTable), self->txt_Locations, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

	g_signal_connect ((gpointer) self->txt_Locations, "changed",
					G_CALLBACK (on_txt_locations_changed),
					self);
  
  //foreign key manages 
  self->lbl_fk_manages = gtk_label_new (("manages : "));
  gtk_widget_show (self->lbl_fk_manages);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_fk_manages, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_fk_manages), 0, 0.5);
  self->cmb_fk_manages_model = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
  self->cmb_fk_manages = gtk_combo_box_new_with_model(self->cmb_fk_manages_model);
  self->cmb_fk_manages_renderer = gtk_cell_renderer_text_new();
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(self->cmb_fk_manages), 
  		self->cmb_fk_manages_renderer, TRUE );
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(self->cmb_fk_manages), 
  		self->cmb_fk_manages_renderer, "text",0, NULL );
  gtk_widget_show (self->cmb_fk_manages);
  gtk_table_attach (GTK_TABLE (widgetTable), self->cmb_fk_manages, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  self->lbl_StartDate = gtk_label_new (("StartDate : "));
  gtk_widget_show (self->lbl_StartDate);
  gtk_table_attach (GTK_TABLE (widgetTable), self->lbl_StartDate, 0, 1, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (self->lbl_StartDate), 0, 0.5);
  self->txt_StartDate = gtk_entry_new ();
  gtk_widget_show (self->txt_StartDate);
  gtk_table_attach (GTK_TABLE (widgetTable), self->txt_StartDate, 1, 2, 6, 7,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);


  main_hbuttonbox = gtk_hbutton_box_new ();
  gtk_widget_show (main_hbuttonbox);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_hbuttonbox, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (main_hbuttonbox), 2);
  gtk_box_set_spacing (GTK_BOX (main_hbuttonbox), 5);

  self->btnAdd = gtk_button_new_from_stock ("gtk-add");
  gtk_widget_show (self->btnAdd);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), self->btnAdd);
  GTK_WIDGET_SET_FLAGS (self->btnAdd, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer)  (self->btnAdd), "clicked",
								G_CALLBACK (on_btnAdd_clicked),
								self);

  self->btnEdit = gtk_button_new_from_stock ("gtk-edit");
  gtk_widget_show (self->btnEdit);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), self->btnEdit);
  //GTK_WIDGET_SET_FLAGS (btnSave, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer)  (self->btnEdit), "clicked",
								G_CALLBACK (on_btnEdit_clicked),
								self);

  self->btnBack = gtk_button_new_from_stock ("gtk-go-back");
  gtk_widget_show (self->btnBack);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), self->btnBack);
  GTK_WIDGET_SET_FLAGS (self->btnBack, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer)  (self->btnBack), "clicked",
								G_CALLBACK (on_btnBack_clicked),
								self);

  self->btnForward = gtk_button_new_from_stock ("gtk-go-forward");
  gtk_widget_show (self->btnForward);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), self->btnForward);
  GTK_WIDGET_SET_FLAGS (self->btnForward, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer)  (self->btnForward), "clicked",
								G_CALLBACK (on_btnForward_clicked),
								self);

  self->btnPreview = gtk_button_new_from_stock ("gtk-print-preview");
  gtk_widget_show (self->btnPreview);
  gtk_container_add (GTK_CONTAINER (main_hbuttonbox), self->btnPreview);
  GTK_WIDGET_SET_FLAGS (self->btnPreview, GTK_CAN_DEFAULT);

	@StrLower(Name)@_fill_combo(self);
}

void
@StrLower(Name)@_fill_combo(@FirstUpper(Name)@ *self) 
{
		GtkTreeStore *model;
		GtkTreeIter iter;
		//GtkTreeIter child_iter, grand_iter;
		GList *list, *l_tmp2;
		GError *error = NULL;
		VvEmployee *entity;
		
		list = vv_employee_get_data_all(connection, &error);
		//model = GTK_TREE_STORE (gtk_tree_view_get_model(GTK_TREE_VIEW (self->cmb_fk_manages)));
		model = GTK_TREE_STORE (gtk_combo_box_get_model(self->cmb_fk_manages));
		gtk_tree_store_clear(GTK_TREE_STORE(model));

		for (list=g_list_first(list);list != NULL; list = list->next) {
			entity = (VvEmployee *) (list->data);
			gtk_tree_store_append ( model,&iter , NULL );
			gtk_tree_store_set (model, &iter, 0 ,  entity->name,1, entity->ssn, 2, "entity", -1);			
		}
}

static void
@StrLower(Name)@_finalize(GObject *object)
{
	@FirstUpper(Name)@ *cobj;
	cobj = @Upper(Name)@(object);
	
	/* Free private members, etc. */
		
	//g_free(cobj->priv);
	G_OBJECT_CLASS(parent_class)->finalize(object);
}

@FirstUpper(Name)@ *
@StrLower(Name)@_new()
{
	@FirstUpper(Name)@ *obj;
	
	obj = @Upper(Name)@(g_object_new(@Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@, NULL));
	
	return obj;
}
