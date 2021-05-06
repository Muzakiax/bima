#ifndef __BIMA_CGTK_UTILS_H__
#define __BIMA_CGTK_UTILS_H__

#include <glib.h>
#include <glib-object.h>
#include <bima-plugin.h>

void free_local_list();
void append_to_local_list(gchar *var);
gboolean is_exists_in_local_list(gchar *var);

void cgtk_gen_module_gtype(FILE *ofile, BimaAppGui *app_gui ) ;
void cgtk_gen_module_class(FILE *ofile, BimaAppGui *app_gui ) ;
void cgtk_gen_module_function(FILE *ofile, BimaAppGui *app_gui ) ;

void cgtk_gen_entity_gtype(FILE *ofile, BimaAppGui *app_gui ) ;
void cgtk_gen_entity_class(FILE *ofile, BimaAppGui *app_gui ) ;
void cgtk_gen_entity_function(FILE *ofile, BimaAppGui *app_gui ) ;

void cgtk_gen_entity_attribute(FILE *ofile, BimaAppGui *app_gui);
void cgtk_gen_entity_data_assignment(FILE *ofile, BimaAppGui *app_gui);
void cgtk_gen_entity_data_all_assignment(FILE *ofile, BimaAppGui *app_gui);

//@VarEntityAttributeInsertList@
void cgtk_gen_entity_attribute_list(FILE *ofile, BimaAppGui *app_gui);
//@VarEntityAttributeInsertValues@
void cgtk_gen_entity_attribute_insert_values(FILE *ofile, BimaAppGui *app_gui);

//@VarEntityAttributeSetUpadte@
void cgtk_gen_entity_attribute_set_update(FILE *ofile, BimaAppGui *app_gui ) ;
//@VarEntityKeyParamStr@
void cgtk_gen_entity_key_param_str(FILE *ofile, BimaAppGui *app_gui) ;

gchar* bima_cgtk_get_class_format(gchar *str) ;
gchar* bima_cgtk_get_function_format(gchar *str) ;

#endif
