#include <string.h> 
#include "bima-cgtk-utils.h"
#include "bima-utils.h"

extern GList *local_list;

void
free_local_list()
{
	GList *list;
	for (list=g_list_first(local_list);list != NULL; list = list->next){
		if (list->data) 
			g_free(list->data); 
	}
	g_list_free(local_list);
}

void
append_to_local_list(gchar *var)
{
	local_list = g_list_append(local_list, g_strdup(var));
}

gboolean
is_exists_in_local_list(gchar *var) {
	gboolean exists;
	GList *list;
	exists = FALSE;
	
	for (list=g_list_first(local_list);list != NULL; list = list->next){
		if (list->data) 
			if (!g_ascii_strcasecmp(var, (gchar *) list->data ))
				return TRUE;
	}
	return FALSE;	
}

// convert er_demo to ErDemo
gchar*
bima_cgtk_get_gtype_format(gchar *str) 
{
	gchar *result = NULL , *s, *tmp;
	gint i, len;
	
	len = strlen(str);	
	tmp = g_new(char , len);
	
	i = 0 ;
	for ( s = str; *s; s++)	{
		if (( *s == '-' ) || ( *s == '_' )) {
			*s++;
		}
		tmp[i] = g_ascii_toupper(*s);
		
		i++;
	}
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}

void
cgtk_gen_module_gtype(FILE *ofile, BimaAppGui *app_gui ) 
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "module_id", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_gtype_format(str_tmp));
}

void
cgtk_gen_module_class(FILE *ofile, BimaAppGui *app_gui ) 
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "module_id", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_class_format(str_tmp));
}

void
cgtk_gen_module_function(FILE *ofile, BimaAppGui *app_gui ) 
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "module_id", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_function_format(str_tmp));
}

void 
cgtk_gen_entity_gtype(FILE *ofile, BimaAppGui *app_gui )
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "name", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_gtype_format(str_tmp));

}

void 
cgtk_gen_entity_class(FILE *ofile, BimaAppGui *app_gui ) 
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "name", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_class_format(str_tmp));

}

void 
cgtk_gen_entity_function(FILE *ofile, BimaAppGui *app_gui ) 
{
	gchar *str_tmp=NULL;
	
	g_object_get(app_gui->cur_obj, "name", &str_tmp, NULL);
	if ( str_tmp != NULL)
		fprintf(ofile, "%s", bima_cgtk_get_function_format(str_tmp));

}

void
destroy_list_attribute(GList *list) 
{
	GList *l;
	for (l=g_list_first(list);l != NULL; l = l->next){
		if (l->data) 
			g_object_unref((GObject *) l->data); 
	}
}

void 
cgtk_gen_entity_attribute(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	
	GList *list, *list1 ;
	entity = (BimaEntity *)app_gui->cur_obj;
	//attr_list = entity->attributes;
	
	for (list= g_list_first(bima_entity_get_all_attribute(entity, app_gui->app_data));list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		//cgtk_gen_class_attribute(ofile,attribute,"");
		if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
			fprintf(ofile, "  gchar *%s;\n", g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
			fprintf(ofile, "  gchar *%s;\n", g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
			fprintf(ofile, "  gint %s;\n", g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("date", attribute->field_type)) {
			fprintf(ofile, "  GDate *%s;\n",g_ascii_strdown(attribute->name,-1));
		}
	}
}

void 
cgtk_gen_entity_data_assignment_attribute(FILE *ofile, BimaAttribute *attribute, gchar *prefix, gint col)
{
		if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,0);\n", col );
			fprintf(ofile, "  entity->%s%s = gda_value_stringify(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,0);\n", col );
			fprintf(ofile, "  entity->%s%s = gda_value_stringify(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,0);\n", col );
			fprintf(ofile, "  entity->%s%s = g_value_get_int(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("date", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,0);\n", col );
			fprintf(ofile, "  entity->%s%s = g_date_new();\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			fprintf(ofile, "  g_date_set_parse(entity->%s%s, gda_value_stringify(gval));\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			
			//fprintf(ofile, "  GdaTimeStamp *_ts%d = gda_value_get_timestamp(gval);;\n",col);
			//fprintf(ofile, "  entity->%s%s = g_date_new_dmy((GDateDay) _ts%d->day,(GDateMonth) _ts%d->month,(GDateYear) _ts%d->year);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1),col,col,col);
			//fprintf(ofile, "  GDate %s%s;\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
}

void 
cgtk_gen_entity_data_assignment(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	gint row, col;
	GList *list, *list1 ;
	entity = (BimaEntity *)app_gui->cur_obj;
	//attr_list = entity->attributes;
	row = 0;
	col = 0;
	
	for (list= g_list_first(bima_entity_get_all_attribute(entity, app_gui->app_data));list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		cgtk_gen_entity_data_assignment_attribute(ofile,attribute,"",col);
		col++;
	}
}

void 
cgtk_gen_entity_data_all_assignment_attribute(FILE *ofile, BimaAttribute *attribute, gchar *prefix, gint col)
{
		if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,i);\n", col );
			fprintf(ofile, "  entity->%s%s = gda_value_stringify(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,i);\n", col );
			fprintf(ofile, "  entity->%s%s = gda_value_stringify(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,i);\n", col );
			fprintf(ofile, "  entity->%s%s = g_value_get_int(gval);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("date", attribute->field_type)) {
			fprintf(ofile, "  gval = (GValue *)gda_data_model_get_value_at(gdm,%d,i);\n", col );
			fprintf(ofile, "  entity->%s%s = g_date_new();\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			fprintf(ofile, "  g_date_set_parse(entity->%s%s, gda_value_stringify(gval));\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
}

void 
cgtk_gen_entity_data_all_assignment(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	gint row, col;
	GList *list, *list1 ;
	entity = (BimaEntity *)app_gui->cur_obj;
	//attr_list = entity->attributes;
	row = 0;
	col = 0;
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		cgtk_gen_entity_data_all_assignment_attribute(ofile,attribute,"",col);
		col++;
	}
	
	for (list1= g_list_first(entity->foreign_key);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;
		else
			continue ;
		
		fk_entity = (BimaEntity *)bima_get_object_by_prop(app_gui->app_data->entities, "id",fk->pk_obj_id);
		for (list= g_list_first(fk_entity->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
			if (attribute->is_key == 1) {
				cgtk_gen_entity_data_all_assignment_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
				col++;
			}
		}
	}

	for (list1= g_list_first(entity->foreign_attr);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;

		relation = (BimaRelation *)bima_get_object_by_prop(app_gui->app_data->relations, "id",fk->pk_obj_id);
		for (list= g_list_first(relation->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
			cgtk_gen_entity_data_all_assignment_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
			col++;
		}
	}

}

//@VarEntityAttributeInsertList@
void 
cgtk_gen_entity_attribute_list(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	gint row, col;
	GList *list, *list1 ;

	entity = (BimaEntity *)app_gui->cur_obj;
	col = 0;
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;

		if (col == 0)	
			fprintf(ofile, "%s",g_ascii_strdown(attribute->name,-1));
		else
			fprintf(ofile, ",%s",g_ascii_strdown(attribute->name,-1));

		col++;
	}
	
	for (list1= g_list_first(entity->foreign_key);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;
		else
			continue ;
		
		fk_entity = (BimaEntity *)bima_get_object_by_prop(app_gui->app_data->entities, "id",fk->pk_obj_id);
		for (list= g_list_first(fk_entity->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
			if (attribute->is_key == 1) {
				if (col == 0)
					fprintf(ofile, "%s_%s", fk->name,g_ascii_strdown(attribute->name,-1));
				else
					fprintf(ofile, ",%s_%s", fk->name,g_ascii_strdown(attribute->name,-1));

//				cgtk_gen_entity_data_assignment_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
				col++;
			}
		}
	}

	for (list1= g_list_first(entity->foreign_attr);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;

		relation = (BimaRelation *)bima_get_object_by_prop(app_gui->app_data->relations, "id",fk->pk_obj_id);
		for (list= g_list_first(relation->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;

				if (col == 0)
					fprintf(ofile, "%s_%s", fk->name,g_ascii_strdown(attribute->name,-1));
				else
					fprintf(ofile, ",%s_%s", fk->name,g_ascii_strdown(attribute->name,-1));

			col++;
		}
	}
}

void 
cgtk_gen_entity_insert_values_attribute(FILE *ofile, BimaAttribute *attribute, gchar *prefix, gint col)
{
		if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {

			fprintf(ofile, "  if ( entity->%s%s )\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\"'%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\",'%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			
			fprintf(ofile, "  else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\"NULL\",NULL);\n");
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\",NULL\",NULL);\n");
		}
		else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
			fprintf(ofile, "  if ( entity->%s%s )\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\"'%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\",'%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			fprintf(ofile, "  else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\"NULL\",NULL);\n");
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\",NULL\",NULL);\n");		
		}
		else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
			if ( col == 0)
				fprintf(ofile, "  sql = g_strconcat(sql , g_strdup_printf(\"'%%d'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  sql = g_strconcat(sql , g_strdup_printf(\",'%%d'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("date", attribute->field_type)) {
			fprintf(ofile, "  if ( entity->%s%s ) {\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			fprintf(ofile, "  \t gchar buf%d[15];\n", col);

			if ( col == 0)
				fprintf(ofile, "  \t g_date_strftime(buf%d, 14, \" '%%F'\", entity->%s%s);\n", col,g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t g_date_strftime(buf%d, 14, \",'%%F'\", entity->%s%s);\n", col,g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			
			fprintf(ofile, "  \t sql = g_strconcat(sql , buf%d, NULL);\n", col);
			fprintf(ofile, "  } else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\"NULL\",NULL);\n");
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\",NULL\",NULL);\n");		
		}
}

//@VarEntityAttributeInsertValues@
void cgtk_gen_entity_attribute_insert_values(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	gint row, col;
	GList *list, *list1 ;

	entity = (BimaEntity *)app_gui->cur_obj;
	col = 0;
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		cgtk_gen_entity_insert_values_attribute(ofile,attribute, "",col);
		col++;
	}
	
	for (list1= g_list_first(entity->foreign_key);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;
		else
			continue ;
		
		fk_entity = (BimaEntity *)bima_get_object_by_prop(app_gui->app_data->entities, "id",fk->pk_obj_id);
		for (list= g_list_first(fk_entity->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
			if (attribute->is_key == 1) {
				cgtk_gen_entity_insert_values_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
				col++;
			}
		}
	}

	for (list1= g_list_first(entity->foreign_attr);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;

		relation = (BimaRelation *)bima_get_object_by_prop(app_gui->app_data->relations, "id",fk->pk_obj_id);
		for (list= g_list_first(relation->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
				cgtk_gen_entity_insert_values_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
			col++;
		}
	}

}


void 
cgtk_gen_entity_set_update_attribute(FILE *ofile, BimaAttribute *attribute, gchar *prefix, gint col)
{
/*
	if ( entity->locations )
		sql = g_strconcat(sql , g_strdup_printf(" locations = '%s',", entity->locations), NULL);
	else 
		sql = g_strconcat(sql , " locations = NULL, ", NULL);
*/
		if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
			fprintf(ofile, "  if ( entity->%s%s )\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\" %s%s = '%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\",%s%s = '%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			
			fprintf(ofile, "  else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\" %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\", %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
			fprintf(ofile, "  if ( entity->%s%s )\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\" %s%s = '%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql , g_strdup_printf(\",%s%s = '%%s'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			
			fprintf(ofile, "  else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\" %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\", %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
			if ( col == 0)
				fprintf(ofile, "  sql = g_strconcat(sql , g_strdup_printf(\" %s%s = '%%d'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  sql = g_strconcat(sql , g_strdup_printf(\", %s%s = '%%d'\", entity->%s%s), NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
		else if (!g_ascii_strcasecmp("date", attribute->field_type)) {
			fprintf(ofile, "  if ( entity->%s%s ) {\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			fprintf(ofile, "  \t gchar buf%d[15];\n", col);
			fprintf(ofile, "  \t g_date_strftime(buf%d, 14, \" '%%F'\", entity->%s%s);\n", col,g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));

			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql, \" %s%s = \" , buf%d, NULL);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), col);
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql, \", %s%s = \" , buf%d, NULL);\n",g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1), col);
			fprintf(ofile, "   } else\n");
			if ( col == 0)
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\" %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
			else
				fprintf(ofile, "  \t sql = g_strconcat(sql ,\", %s%s = NULL\",NULL);\n", g_ascii_strdown(prefix,-1),g_ascii_strdown(attribute->name,-1));
		}
}

//@VarEntityAttributeSetUpadte@
void cgtk_gen_entity_attribute_set_update(FILE *ofile, BimaAppGui *app_gui ) 
{
	BimaEntity *entity, *fk_entity;
	BimaAttribute *attribute;
	BimaForeignKey *fk;
	BimaRelation *relation;
	gint row, col;
	GList *list, *list1 ;

	entity = (BimaEntity *)app_gui->cur_obj;
	col = 0;
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		if (attribute->is_key != 1) {
			cgtk_gen_entity_set_update_attribute(ofile,attribute, "",col);
			col++;
		}
	}
	
	for (list1= g_list_first(entity->foreign_key);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;
		else
			continue ;
		
		fk_entity = (BimaEntity *)bima_get_object_by_prop(app_gui->app_data->entities, "id",fk->pk_obj_id);
		for (list= g_list_first(fk_entity->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
			if (attribute->is_key == 1) {
				cgtk_gen_entity_set_update_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
				col++;
			}
		}
	}

	for (list1= g_list_first(entity->foreign_attr);list1 != NULL; list1 = list1->next){
		if (list1->data) 
			fk = (BimaForeignKey *)list1->data;

		relation = (BimaRelation *)bima_get_object_by_prop(app_gui->app_data->relations, "id",fk->pk_obj_id);
		for (list= g_list_first(relation->attributes);list != NULL; list = list->next){
			if (list->data) 
				attribute = (BimaAttribute *)list->data;
				cgtk_gen_entity_set_update_attribute(ofile,attribute, g_strdup_printf("%s_", fk->name),col);
			col++;
		}
	}
}

//@VarEntityKeyParamStr@
void cgtk_gen_entity_key_param_str(FILE *ofile, BimaAppGui *app_gui) 
{
	BimaEntity *entity;
	BimaAttribute *attribute;
	GList *list ;
	gboolean is_first;

	entity = (BimaEntity *)app_gui->cur_obj;
	is_first = TRUE;
	
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		
		if (attribute->is_key == 1) {
			if (is_first) {
				is_first = FALSE;
			} else
				fprintf(ofile,",");

			fprintf(ofile, " entity->%s ", g_ascii_strdown(attribute->name,-1));
		}
	}

}

void 
cgtk_gen_key_param(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity;
	BimaAttribute *attribute;
	GList *list ;
	gboolean is_first;

	entity = (BimaEntity *)app_gui->cur_obj;
	is_first = TRUE;
	
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		
		if (attribute->is_key == 1) {
			if (is_first) {
				is_first = FALSE;
			} else
				fprintf(ofile,",");

			if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
				fprintf(ofile, " gchar *%s", g_ascii_strdown(attribute->name,-1));
			}
			else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
				fprintf(ofile, " gchar *%s", g_ascii_strdown(attribute->name,-1));
			}
			else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
				fprintf(ofile, " gint %s", g_ascii_strdown(attribute->name,-1));
			}
		}
	}
}

void 
cgtk_gen_key_param_sql(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity;
	BimaAttribute *attribute;
	GList *list ;
	gboolean is_first;

	entity = (BimaEntity *)app_gui->cur_obj;
	is_first = TRUE;
	
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		
		if (attribute->is_key == 1) {
			if (is_first) {
				is_first = FALSE;
			} else
				fprintf(ofile," and ");

			if (!g_ascii_strcasecmp("varchar", attribute->field_type)) {
				fprintf(ofile, " %s = '%%s'", g_ascii_strdown(attribute->name,-1));
			}
			else if (!g_ascii_strcasecmp("char", attribute->field_type)) {
				fprintf(ofile, " %s = '%%s'", g_ascii_strdown(attribute->name,-1));
			}
			else if (!g_ascii_strcasecmp("integer", attribute->field_type)) {
				fprintf(ofile, " %s = %%d", g_ascii_strdown(attribute->name,-1));
			}
		}
	}
}

void 
cgtk_gen_key_param_str(FILE *ofile, BimaAppGui *app_gui)
{
	BimaEntity *entity;
	BimaAttribute *attribute;
	GList *list ;
	gboolean is_first;

	entity = (BimaEntity *)app_gui->cur_obj;
	is_first = TRUE;
	
	for (list= g_list_first(entity->attributes);list != NULL; list = list->next){
		if (list->data) 
			attribute = (BimaAttribute *)list->data;
		
		if (attribute->is_key == 1) {
			if (is_first) {
				is_first = FALSE;
			} else
				fprintf(ofile,",");

			fprintf(ofile, " %s ", g_ascii_strdown(attribute->name,-1));
		}
	}
}

gchar*
bima_cgtk_get_class_format(gchar *str) 
{
	gchar *result = NULL , *s, *tmp;
	gint i, len;
	gboolean to_upper = TRUE;
	
	len = strlen(str);	
	tmp = g_new(char , len);
	
	i = 0 ;
	for ( s = str; *s; s++)	{
		if (( *s == '-' ) || ( *s == '_' )) {
			to_upper = TRUE;
			*s++;
		}
		if ( to_upper ) {
			tmp[i] = g_ascii_toupper(*s);
			to_upper = FALSE;
		}
		else
			tmp[i] = g_ascii_tolower(*s);
		
		i++;
	}
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}

gchar*
bima_cgtk_get_function_format(gchar *str) 
{
	gchar *result = NULL , *s, *tmp;
	gint i, len;
	
	len = strlen(str);	
	tmp = g_new(char , len);
	
	i = 0 ;
	for ( s = str; *s; s++)	{
		if (( *s == '-' ) || ( *s == '_' )) {
			*s++;
		}
		tmp[i] = g_ascii_tolower(*s);
		
		i++;
	}
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}
