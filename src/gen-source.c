/***************************************************************************
 *            gen-source.c
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
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gen-source.h"
//#include "bima-cgtk-utils.h"
/*
 *  xxxxx   @yyyyyyyyy@   zzzzz
 *        fnd1      fnd2
 */
gchar *
gen_find_token(gchar **source, gchar **next)
{
	gchar *token;
	gchar *fnd1 , *fnd2;
	gchar *tmp;
	gint num1, num2;

	//*next = NULL;
	token = NULL;

	fnd1 = strchr(*source, '@');
	if (fnd1) {
		fnd2 = strchr(fnd1+1, '@');
		if (fnd2) {
			if (fnd2 != (fnd1+1) ) {
				// lengt of token 
				num1 = (fnd2-fnd1+1) ;
				//	length of -->xxxxx   <--
				num2 = fnd1 - *source ;
				
				tmp = g_strdup(*source );
				
				token = g_strndup(fnd1 , num1 );
				// -->   zzzzz<--
				*next = g_strdup(fnd2+1);
				g_free(*source);
				*source = g_strndup(tmp, num2 );
				g_free(tmp);
			}
		}
	}
	return token;
}

// convert er_demo to ErDemo
gchar*
gen_first_upper(gchar *str) 
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
	//automatically null terminate
	result = g_strndup(tmp, i);
	g_free(tmp);
	return result;
}

// convert er_demo to ERDEMO
gchar*
gen_upper(gchar *str) 
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

// convert er_demo to erdemo
gchar*
gen_lower(gchar *str) 
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

gchar* 
gen_str_function(gchar *str_func, gchar *str) 
{
	gchar *output = NULL;
	
	if ((str == NULL) || (str_func == NULL )) 
		return NULL;
		
	if (!g_ascii_strcasecmp("FirstUpper",str_func )) {
		output = gen_first_upper(str);
		//g_print("FirstUpper %s \n", output );
	}	
	else if (!g_ascii_strcasecmp("StrUpper",str_func )) {
		output = g_ascii_strup(str,-1);
	}
	else if (!g_ascii_strcasecmp("Upper",str_func )) {
		output = gen_upper(str);
	}
	else if (!g_ascii_strcasecmp("StrLower",str_func )) {
		output = g_ascii_strdown(str,-1);
	}
	else if (!g_ascii_strcasecmp("Lower",str_func )) {
		output = gen_lower(str);
	}
	//if (output)
	//	g_print("%s(%s) => %s\n ", str_func, str, output);
	return output;
}

gchar *
get_token_value(BimaAppGui *appgui, gchar *token)
{
	gchar *str_value=NULL , *str_tmp;
	BimaEntity *main_entity;
	BimaTemplateForm *tform;
/*
	if BIMA_IS_ENTITY(appgui->cur_obj) {
		main_entity = (BimaEntity *) appgui->cur_obj;
	}
	else {
		g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
		main_entity = (BimaEntity *) bima_get_object_by_prop(appgui->app_data->entities,"id",str_tmp);
		g_free(str_tmp);
	}
*/	
	if (!g_ascii_strcasecmp("Name",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->name );
		} else {
			str_value = g_strdup( ((BimaForm *) appgui->cur_obj)->name );		
		}
	}
	else if (!g_ascii_strcasecmp("Id",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->id );
		} else {
			str_value = g_strdup( ((BimaForm *) appgui->cur_obj)->id );		
		}
	}
	else if (!g_ascii_strcasecmp("Title",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->name );
		} else {
			str_value = g_strdup( ((BimaForm *) appgui->cur_obj)->title );		
		}
	}
	else if (!g_ascii_strcasecmp("ModuleId",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->module_id );
		} else {
			str_value = g_strdup( ((BimaForm *) appgui->cur_obj)->module_id );	
		}
	}
	else if (!g_ascii_strcasecmp("EntityName",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->name );
		} else {
			g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
			main_entity = (BimaEntity *) bima_get_object_by_prop(appgui->app_data->entities,"id",str_tmp);
			g_free(str_tmp);
			str_value = g_strdup( main_entity->name );		
		}
	}
	else if (!g_ascii_strcasecmp("EntityId",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->id );
		} else {
			g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
			main_entity = (BimaEntity *) bima_get_object_by_prop(appgui->app_data->entities,"id",str_tmp);
			g_free(str_tmp);

			str_value = g_strdup( main_entity->id );		
		}
	}
	else if (!g_ascii_strcasecmp("EntityModuleId",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->module_id );
		} else {
			g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
			main_entity = (BimaEntity *) bima_get_object_by_prop(appgui->app_data->entities,"id",str_tmp);
			g_free(str_tmp);

			str_value = g_strdup( main_entity->module_id );		
		}
	}	else if (!g_ascii_strcasecmp("Id",token )) {
		if BIMA_IS_ENTITY(appgui->cur_obj) {
			str_value = g_strdup( ((BimaEntity *) appgui->cur_obj)->id );
		} else {
			str_value = g_strdup( ((BimaForm *) appgui->cur_obj)->id );		
		}
	}

	else if (!g_ascii_strcasecmp("Prefix",token )) {
		if BIMA_IS_FORM(appgui->cur_obj) {
			str_tmp = g_strdup( ((BimaForm *) appgui->cur_obj)->template_id );	
			//g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
			tform = (BimaTemplateForm *) bima_get_object_by_prop(appgui->app_data->template->tforms,"id",str_tmp);
			if (tform == NULL ) 
				tform = (BimaTemplateForm *) bima_get_object_by_prop(appgui->app_data->template->treports,"id",str_tmp);
			
			g_free(str_tmp);
			if (tform) 
				str_value = g_strdup( tform->prefix );		
		}
	}
	else if (!g_ascii_strcasecmp("Suffix",token )) {
		if BIMA_IS_FORM(appgui->cur_obj) {
			str_tmp = g_strdup( ((BimaForm *) appgui->cur_obj)->template_id );	
			//g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
			tform = (BimaTemplateForm *) bima_get_object_by_prop(appgui->app_data->template->tforms,"id",str_tmp);
			if (tform == NULL ) 
				tform = (BimaTemplateForm *) bima_get_object_by_prop(appgui->app_data->template->treports,"id",str_tmp);
			
			g_free(str_tmp);
			if (tform) 
				str_value = g_strdup( tform->suffix );		
		}
	}
	return str_value;
}

gint
gen_source(gchar *tfilename,gchar *ofilename,BimaAppGui *appgui)
{
	FILE *tfile, *ofile; 
	gchar *buffer, *last_buffer;
	gchar *token;
	gchar *str_tmp,*tmp, *str_output, *str_func_var;
	BimaEntity *main_entity;
	
	buffer=NULL;
	last_buffer=NULL;
	token=NULL;
	main_entity= NULL;
	
	tfile = fopen(tfilename, "r");
	if (!tfile) 
		return 1;

	ofile = fopen(ofilename, "w");
	if (!ofile) 
		return 1;
	
	if BIMA_IS_ENTITY(appgui->cur_obj) {
		main_entity = (BimaEntity *) appgui->cur_obj;
	}
	else {
		g_object_get(appgui->cur_obj, "primary_obj_id", &str_tmp, NULL);
		main_entity = (BimaEntity *) bima_get_object_by_prop(appgui->app_data->entities,"id",str_tmp);
		g_free(str_tmp);
	}
	buffer = (char *) malloc (sizeof (char) * 180);
	while (fgets(buffer,180,tfile) != NULL) {
		token = gen_find_token(&buffer, &last_buffer);
		
		while (token != NULL) {
			fprintf(ofile, "%s",buffer);
			tmp = strchr(token, '(');
			str_func_var = NULL;
			str_output = NULL;
			if (tmp) {
				str_tmp = g_strndup(token+1, tmp-token-1);
				str_func_var = g_strndup(tmp+1, strlen(token)-(strlen(str_tmp) + 4));
				tmp = NULL;
			}
			else 
				str_tmp = g_strdup(token);

			//g_print("%s %s\n ", token ,str_tmp );
			
//			if (gen_cgtk_source(ofile, token, appgui) == 0) {			

			if (bima_plugin_generate(BIMA_PLUGIN(appgui->app_data->template->plugin), ofile, token, appgui) == 0) {
				if (!g_ascii_strcasecmp("VarSQLStr",str_tmp )) {
					if (!g_ascii_strcasecmp("@VarSQLStr(SELECT)@", token)) {
						if (appgui->query->fields) 
							fprintf(ofile, "SELECT %s", bima_query_get_fields_str(appgui->query->fields));
					}
					else if (!g_ascii_strcasecmp("@VarSQLStr(FROM)@", token)) {
						if (appgui->query->tables) 
							fprintf(ofile, "FROM %s", bima_query_get_tables_str(appgui->query));
					}
					else if (!g_ascii_strcasecmp("@VarSQLStr(WHERE)@", token)) {
						if (appgui->query->wheres) 
							fprintf(ofile, "WHERE %s", bima_query_field_get_str(appgui->query->wheres));
					}
					else if (!g_ascii_strcasecmp("@VarSQLStr(GROUPBY)@", token)) {
						if (appgui->query->groups) 
							fprintf(ofile, " GROUP BY %s ", bima_query_get_fields_str(appgui->query->groups));	
					}
					else if (!g_ascii_strcasecmp("@VarSQLStr(HAVING)@", token)) {
						if (appgui->query->havings) 
							fprintf(ofile, " HAVING %s ", bima_query_field_get_str(appgui->query->havings));
					}
					else if (!g_ascii_strcasecmp("@VarSQLStr(ORDER)@", token)) {
					}
				}
				else if (!g_ascii_strcasecmp("VarMainTable", str_tmp)) {
					if (main_entity) {
						if (!g_ascii_strcasecmp("@VarMainTable(NAME)@", token)) {
							if (main_entity->name) 
								fprintf(ofile, "%s", main_entity->name);
						}
						else if (!g_ascii_strcasecmp("@VarMainTable(KEYSTR)@", token)) {
							if (main_entity->num_of_key > 0) 
								fprintf(ofile, bima_entity_get_pk_string(main_entity," || ", main_entity->name));
						}
						else if (!g_ascii_strcasecmp("@VarMainTable(ALIASKEYSTR)@", token)) {
							if (main_entity->num_of_key > 0) 
								fprintf(ofile, bima_entity_get_pk_string(main_entity," || ", bima_query_get_entity_alias(appgui->query , main_entity)));
						}
					}
				}
				else if (!g_ascii_strcasecmp("VarEntityName",str_tmp )) {
					if (main_entity->name) 
						fprintf(ofile, "%s", main_entity->name);					
				}
				else if (!strcmp("@VarFormName@", token)) {
					if (BIMA_IS_FORM(appgui->cur_obj)) {
						fprintf(ofile, ((BimaForm *)(appgui->cur_obj))->name);
					}
				}
				else if (!g_ascii_strcasecmp("VarForm",str_tmp )) {
					if (!g_ascii_strcasecmp("@VarForm(NAME)@", token)) {
						if (BIMA_IS_FORM(appgui->cur_obj)) 
							fprintf(ofile, ((BimaForm *)(appgui->cur_obj))->name);
					} else if (!g_ascii_strcasecmp("@VarForm(TITLE)@", token)) {
						if (BIMA_IS_FORM(appgui->cur_obj)) 
							fprintf(ofile, ((BimaForm *)(appgui->cur_obj))->title);
					}
				}
				else if (str_func_var) {
					//g_print("str_func_var %s(%s) \n", str_tmp, str_func_var);
					str_output = get_token_value (appgui, str_func_var);
					//g_print("%s ==> %s \n", str_output, gen_str_function(str_tmp, str_output));
					//str_output = gen_str_function(str_tmp, str_output);
					fprintf(ofile, "%s", gen_str_function(str_tmp, str_output));
					g_free(str_output);
				} 	
				else {
					str_output = get_token_value (appgui, token);
					if (str_output) {
						fprintf(ofile, str_output);
						g_free(str_output);
					} else 
						fprintf(ofile, token);
				}
			} 
			g_free(str_tmp );

			g_free(buffer);
			buffer = NULL;
			buffer = last_buffer;
			last_buffer = NULL;
			g_free(token);
			token = NULL;
			token = gen_find_token(&buffer, &last_buffer);
		}

		if (buffer) {
			fprintf(ofile, "%s",buffer);
			g_free(buffer);
		}

		buffer = (char *) malloc (sizeof (char) * 180);
		if (!buffer) {
			printf("can't alloc buffer ");
			return 1;
		}		
	}
	
	fclose(ofile);	
	fclose(tfile);

	return 0 ;
}

