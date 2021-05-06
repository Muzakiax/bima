
#include <string.h> /* memset() */
#include "bima-phpweb.h"

/* here are local prototypes */
static void bima_phpweb_plugin_init (BimaPhpWebPlugin * o) ;
static void bima_phpweb_plugin_class_init (BimaPhpWebPluginClass * c) ;

/* pointer to the class of our parent */
static BimaPluginClass *parent_class = NULL;

GList *local_list;
gint varc;

BIMA_PLUGIN_REGISTER_TYPE(BimaPhpWebPlugin, bima_phpweb_plugin)

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
	varc++;
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

void
phpweb_gen_defn_main_index(FILE *ofile, GList *flist)
{
	GList *tlist;
	BimaForm *form;

	for (tlist=g_list_first(flist);tlist != NULL; tlist = tlist->next){
  		form = (BimaForm *) tlist->data;

		fprintf(ofile, "\t<tr>\n");
		fprintf(ofile, "\t\t<td> <a href=\"%s.php\" name=\"%s\">%s</a> </td>\n", form->name , form->name, form->title);
		fprintf(ofile, "\t</tr>\n");

  	}
}


static void
___finalize(GObject *obj_self)
{
	BimaPhpWebPlugin *self  = BIMA_CGTK_PLUGIN (obj_self);

	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);

	if(self->name) { g_free ((gpointer) self->name); self->name = NULL; }
	if(self->author) { g_free ((gpointer) self->author); self->author = NULL; }
}

static void 
bima_phpweb_plugin_init (BimaPhpWebPlugin * o )
{
	o->name = g_strdup("Web PHP Plugin");;
	o->author = g_strdup("Anas Muzakir");;
}

static void  
bima_phpweb_plugin_activate (BimaPlugin * plugin, BimaAppGui * app_gui)
{
		return;
}

static void  
bima_phpweb_plugin_deactivate (BimaPlugin * plugin, BimaAppGui * app_gui)
{
		return;
}

void
phpweb_gen_update_sql_an_attribute(FILE *ofile, BimaAttribute * attribute)
{
	gchar *name, *param;
	//char *str_tok, *str_tok2;
	gint i ;
	BimaEntity *entity = NULL;

	i = 0;

	if (attribute == NULL) {
		return;
	} else {
		// to avoid duplicate variable name
		name = g_strdup(attribute->name);
		if (is_exists_in_local_list(name)) {
			g_free(name);
			
			if (attribute->parent) 
				entity = (BimaEntity *)(attribute->parent);
			if (entity) {
				name = g_strdup_printf("%s_%s",entity->name,attribute->name);
			} else {
				name = g_strdup_printf("%s%d",attribute->name, varc);
			}
			entity = NULL;
		} else {
			append_to_local_list(name);
		}

		if (!g_ascii_strcasecmp("Integer", attribute->field_type)) {
			fprintf(ofile, " %s = $%s ", attribute->name, name);
		}
		else {
			fprintf(ofile, " %s = '$%s' ", attribute->name, name);
		}
	}
}

void
phpweb_gen_update_sql_str(FILE *ofile, gchar *main_entity_name, BimaAppGui *app_gui)
{

	GObject *attribute;
	BimaQueryField *qfield;
	BimaQueryTable *qtable, *qtbl;	
	gchar *name;
	gint n,n_field, fld, n_table,tbl;
	n_table = 0;
	n_table = bima_query_get_number_of_tables(app_gui->query);
	n_table += bima_query_get_number_of_sub_query(app_gui->query);

	n_field = bima_query_get_number_of_fields(app_gui->query);

	n=0;
	// looping for each table, to group show field base on table name
	// or one table base on table_name parameter	
	for ( tbl = 0 ; tbl < n_table; tbl++ ) { 
		qtbl = bima_query_get_nth_table(app_gui->query,tbl);
		
		if (qtbl->sub_query != NULL) 
			continue; 
		
		if ( (main_entity_name == NULL) || ((main_entity_name) && (!g_ascii_strcasecmp(main_entity_name, qtbl->table)) && (n==0))) {

			name = g_strdup_printf("%s",qtbl->table);
			fprintf(ofile,"UPDATE %s SET ", name);
			
			// now, loop for field in table
			for (fld=0; fld < n_field ; fld++) {
				qtable = NULL;
				qfield = NULL;
			
				attribute = bima_query_get_nth_attribute(app_gui->query,fld, &qtable, &qfield);
				// tbl hsl query attr hrs sama degan tabel iterasi
				if ( (attribute) && ( 
				     ((qtable->alias) && (qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias)) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) || 
				     ((qtable->alias) && (qtbl->alias) && (!qtable->table) && (!qtbl->table) && (!g_ascii_strcasecmp(qtable->alias, qtbl->alias))) || 
					 ((!qtable->alias) && (!qtbl->alias) && (qtable->table) && (qtbl->table) && (!g_ascii_strcasecmp(qtable->table, qtbl->table))) 
				 	) 
			   	) {
			   		
			   		if ( n != 0 ) {
			   			fprintf(ofile," , " );
			   		}

					if (BIMA_IS_ATTRIBUTE(attribute))
						phpweb_gen_update_sql_an_attribute(ofile, (BimaAttribute *) attribute);
	
					//if ( BIMA_IS_FOREIGN_KEY(attribute))
					//	cgtk_gen_decl_widget_an_fk(ofile, (BimaForeignKey *) attribute);
				}
				n++;
			}
		}
	}
}

static int  
bima_phpweb_plugin_generate (FILE * ofile, gchar * token, BimaAppGui * app_gui)
{
	gchar *str_tmp;
	BimaEntity *main_entity;
	gint tkn_code;
	if (!g_ascii_strcasecmp("@VarIndexPHP@", token)) {
		tkn_code = 1;
		if (app_gui->app_data->forms)
			phpweb_gen_defn_main_index(ofile, app_gui->app_data->forms);
		if (app_gui->app_data->reports)
			phpweb_gen_defn_main_index(ofile, app_gui->app_data->reports);			

	}
	else if (!g_ascii_strcasecmp("@VarDatabaseConnection@", token)) {
		tkn_code = 1;
		fprintf(ofile, "dbname=%s host=localhost user=%s password=%s",app_gui->app_data->db_name, app_gui->app_data->db_user_name, app_gui->app_data->db_user_pass);	
	}
	else if (!g_ascii_strcasecmp("@VarUpdateSQLStr@", token)) {
		tkn_code = 1;

		g_object_get(app_gui->cur_obj, "primary_obj_id", &str_tmp, NULL);
		main_entity = (BimaEntity *) bima_get_object_by_prop(app_gui->app_data->entities,"id",str_tmp);
		g_free(str_tmp);
		
		phpweb_gen_update_sql_str(ofile, main_entity->name, app_gui);

	}

	return tkn_code;
}


static void 
bima_phpweb_plugin_class_init (BimaPhpWebPluginClass * c )
{
	GObjectClass *g_object_class  = (GObjectClass*) c;
	BimaPluginClass *plugin_class = BIMA_PLUGIN_CLASS(c);
	
	parent_class = g_type_class_ref (BIMA_TYPE_PLUGIN);
	
	g_object_class->finalize = ___finalize;

	plugin_class->activate = bima_phpweb_plugin_activate;
	plugin_class->deactivate = bima_phpweb_plugin_deactivate;
	plugin_class->generate = bima_phpweb_plugin_generate;	
}
