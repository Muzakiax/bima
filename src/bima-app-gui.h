/* Generated by GOB (v2.0.13)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>
#ifndef __BIMA_APP_GUI_H__
#define __BIMA_APP_GUI_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <libxml/xmlreader.h>
#include "callback.h"
#include "bima-app-data.h"
#include "file-utils.h"
#include "bima-query.h"



typedef enum {
	STATE_PARSE,
	STATE_TABLE,
	STATE_VIEW,
	STATE_REPORT,
	STATE_FORM,
	STATE_OPTION,
	STATE_GENERATE
} BimaState;


/*
 * Type checking and casting macros
 */
#define BIMA_TYPE_APP_GUI	(bima_app_gui_get_type())
#define BIMA_APP_GUI(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_app_gui_get_type(), BimaAppGui)
#define BIMA_APP_GUI_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_app_gui_get_type(), BimaAppGui const)
#define BIMA_APP_GUI_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), bima_app_gui_get_type(), BimaAppGuiClass)
#define BIMA_IS_APP_GUI(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), bima_app_gui_get_type ())

#define BIMA_APP_GUI_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), bima_app_gui_get_type(), BimaAppGuiClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_BIMA_APP_GUI__
#define __TYPEDEF_BIMA_APP_GUI__
typedef struct _BimaAppGui BimaAppGui;
#endif
struct _BimaAppGui {
	GtkWindow __parent__;
	/*< public >*/
	BimaAppData * app_data;
	GObject * cur_obj;
	BimaQuery * query;
	GtkWidget * main_left_image;
	GtkWidget * main_notebook;
	GtkWidget * back_button;
	GtkWidget * forward_button;
	GtkEntry * step1_file_entry;
	GtkWidget * step1_text_parse;
	GtkWidget * step1_app_combo;
	GtkWidget * step2_main_label;
	GtkEntry * step2_name_entry;
	GtkWidget * step2_main_treeview;
	GtkWidget * step2_main_notebook;
	GtkWidget * step2_page1_table;
	GtkWidget * step2_page2_table;
	GtkWidget * step2_sql_textview;
	GtkWidget * step5_left_table;
	GtkWidget * step5_right_table;
	GtkEntry * step5_output_dir_entry;
	GtkWidget * step6_generate_button;
	GtkWidget * step6_generate_treeview;
	GtkWidget * popup_menu;
	BimaState state;
};

/*
 * Class definition
 */
typedef struct _BimaAppGuiClass BimaAppGuiClass;
struct _BimaAppGuiClass {
	GtkWindowClass __parent__;
};


/*
 * Public methods
 */
GType	bima_app_gui_get_type	(void);
void 	bima_app_gui_fill_step1_combo	(BimaAppGui * self,
					gchar * template_dir);
void 	bima_app_gui_show_modules	(BimaAppGui * self,
					GList * next_list,
					gchar * parent_id,
					GtkTreeIter parent_iter);
void 	bima_app_gui_show_tables	(BimaAppGui * self,
					gchar * module_id,
					GtkTreeIter module_iter);
void 	bima_app_gui_show_views	(BimaAppGui * self);
void 	bima_app_gui_show_reports	(BimaAppGui * self);
void 	bima_app_gui_show_forms	(BimaAppGui * self);
void 	bima_app_gui_show_current_state	(BimaAppGui * self);
GtkWidget * 	bima_app_gui_new	(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
