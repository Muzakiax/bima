#ifndef __@StrUpper(Name)@_H__
#define __@StrUpper(Name)@_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#define @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@         (@Lower(Name)@_get_type ())
#define @Upper(Name)@(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@, @FirstUpper(Name)@))
#define @Upper(Name)@_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@, @FirstUpper(Name)@Class))
#define @Upper(Prefix)@_IS_@Upper(Name)@_@Upper(Suffix)@(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@))
#define @Upper(Prefix)@_IS_@Upper(Name)@_@Upper(Suffix)@_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@))
#define @Upper(Name)@_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), @Upper(Prefix)@_TYPE_@Upper(Name)@_@Upper(Suffix)@, @FirstUpper(Name)@Class))

#define @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@         (frm_department_get_type ())
#define @Upper(EntityModuleId)@_@StrUpper(Name)@(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@, FrmDepartment))
#define @Upper(EntityModuleId)@_@StrUpper(Name)@_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@, FrmDepartmentClass))
#define @Upper(EntityModuleId)@_IS_@StrUpper(Name)@(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@))
#define @Upper(EntityModuleId)@_IS_@StrUpper(Name)@_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@))
#define @Upper(EntityModuleId)@_@StrUpper(Name)@_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), @Upper(EntityModuleId)@_TYPE_@StrUpper(Name)@, FrmDepartmentClass))


typedef struct _@FirstUpper(Name)@ @FirstUpper(Name)@;
typedef struct _@FirstUpper(Name)@Private @FirstUpper(Name)@Private;
typedef struct _@FirstUpper(Name)@Class @FirstUpper(Name)@Class;

struct _@FirstUpper(Name)@ {
	GtkWindow parent;

  GList *list;
  gboolean is_edit;
  gboolean is_add;

  GtkWidget *lbl_@Upper(Name)@;
  GtkWidget *lbl_Number;
  GtkWidget *txt_Number;
  GtkWidget *lbl_Name;
  GtkWidget *txt_Name;
  GtkWidget *lbl_NumberOfEmployees;
  GtkWidget *txt_NumberOfEmployees;
  GtkWidget *lbl_Locations;
  GtkWidget *txt_Locations;

  GtkWidget *lbl_fk_manages;
  GtkWidget *cmb_fk_manages_model;
  GtkWidget *cmb_fk_manages_renderer;
  GtkWidget *cmb_fk_manages;
  GtkWidget *lbl_StartDate;
  GtkWidget *txt_StartDate;
  
  GtkWidget *btnAdd;
  GtkWidget *btnEdit;
  GtkWidget *btnBack;
  GtkWidget *btnForward;
  GtkWidget *btnPreview;
	//@FirstUpper(Name)@Private *priv;
};

struct _@FirstUpper(Name)@Class {
	GtkWindowClass parent_class;
	/* Add Signal Functions Here */
};

GType @StrLower(Name)@_get_type();
@FirstUpper(Name)@ *@StrLower(Name)@_new();

#endif
