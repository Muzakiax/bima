/***************************************************************************
 *            dia-er-parse.c
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
#include <glib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "dia-er-parse.h"
#include "bima-utils.h"


//GtkTextBuffer *output_buff;
GList *l_attributes = NULL;

extern void
bima_insert_parse_log(gchar *log);


gchar *
get_clean_content(gchar *content)
{
	gchar *tmp;
	if (content == NULL)
		return "0";
	tmp = g_strndup(content+1, strlen(content)-2);
	return tmp;
}

void
bima_dump_object(GList *list)
{
	GObject *o;
	GList *o_list;
	gchar *o_value;
	gchar *id;
	if (list==NULL) return ;
	o_list = g_list_first(list);
	while (o_list) {
		if (o_list->data) {
			o = (GObject *)o_list->data;
			if (!BIMA_IS_ATTRIBUTE(o)) 
				g_print("\n");
			g_object_get(o, "id", &id, NULL);
			g_object_get(o, "name", &o_value, NULL);
			g_print("Object %s: %s\n" ,id, o_value);
			if (BIMA_IS_ENTITY(o) || BIMA_IS_RELATION(o)) {
				if (((BimaEntity *)(o))->attributes)
					g_print("--> Attribute : \n" );
				bima_dump_object(((BimaEntity *)(o))->attributes);
			}
		}
		o_list=o_list->next;
	}
}


BimaEntity*
dia_er_parse_entity (xmlDocPtr xml_doc , xmlNodePtr xml_node_parent )
{
	BimaEntity* entity=NULL;
	xmlNodePtr xml_node;
	xmlChar *prop_val;

	entity = bima_entity_new();

	entity->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		prop_val = xmlGetProp(xml_node,(const xmlChar *) "name");
		if (!xmlStrcmp(prop_val, (const xmlChar *) "name")) {
			//entity->name = get_clean_content ( xml_node->children->children->content);
			entity->name = get_clean_content ( (gchar *)xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode->xmlChildrenNode,1));
			//entity->abbreviation = g_ascii_strdown(entity->name,-1);
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *)"weak")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *)"true")) 
				entity->is_weak = TRUE;
		}
		xml_node = xml_node->next;
	}
	bima_insert_parse_log(
		g_strdup_printf("\t name  : %s, weak:%d\n",entity->name,entity->is_weak));

	return entity;
}

BimaAttribute*
dia_er_parse_atrribute (xmlDocPtr xml_doc ,xmlNodePtr xml_node_parent )
{
	BimaAttribute* attribute=NULL;
	xmlNodePtr  xml_node;
	xmlChar *prop_val;
	
	attribute = bima_attribute_new();
	attribute->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		prop_val = xmlGetProp(xml_node,(const xmlChar *) "name");
		if (!xmlStrcmp(prop_val, (const xmlChar *) "name")) {
			attribute->name = get_clean_content ( (gchar *)xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode->xmlChildrenNode,1));
//			attribute->name = get_clean_content(xml_node->children->children->content);
			attribute->title = g_strdup(attribute->name);
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "key")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *) "true")) {
				attribute->is_key = TRUE;
				attribute->not_null = TRUE;
			}
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "weak_key")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *) "true")) attribute->is_weak = TRUE;
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "derived")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *) "true")) attribute->is_derived = TRUE;
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "multivalued")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *) "true")) attribute->is_multivalued = TRUE;
		}
		xml_node = xml_node->next;
	}

	if ( g_strrstr(g_ascii_strdown(attribute->name,-1),"date")) {
		if (attribute->field_type) g_free(attribute->field_type);
		attribute->field_type = NULL;

		attribute->field_type = g_strdup("date");
		attribute->length = 0;
	}
	else if ( g_strrstr(g_ascii_strdown(attribute->name,-1),"number")) {
		if (attribute->field_type) g_free(attribute->field_type);
		attribute->field_type = NULL;

		attribute->field_type = g_strdup("integer");
		attribute->length = 0;
	}
	else if ( g_strrstr(g_ascii_strdown(attribute->name,-1),"sex")) {
		if (attribute->control_type) g_free(attribute->control_type);
		attribute->control_type = NULL;
		attribute->control_type = g_strdup("Radio Button");
		attribute->parameter = g_strdup("M;Male;F;Female");
	}

	bima_insert_parse_log(
		g_strdup_printf("\t name  : %s, key:%d\n",attribute->name,attribute->is_key));

	return attribute;
}

BimaRelation*
dia_er_parse_relation (xmlDocPtr xml_doc ,xmlNodePtr xml_node_parent )
{
	BimaRelation* relation=NULL;
	xmlNodePtr xml_node;
	xmlChar *prop_val;

	relation = bima_relation_new();
	relation->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		prop_val = xmlGetProp(xml_node,(const xmlChar *) "name");
		if (!xmlStrcmp(prop_val, (const xmlChar *) "name")) {
			relation->name = get_clean_content ( (gchar *)xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode->xmlChildrenNode,1));
			//relation->name = get_clean_content ( xml_node->children->children->content);
			//relation->abbreviation = g_ascii_strdown(relation->name,-1);
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "left_card")) {
			relation->left_card = g_ascii_strdown(get_clean_content ( (gchar *)xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode->xmlChildrenNode,1)),-1);
			if (!g_ascii_strcasecmp("n",relation->left_card)) relation->left_card = g_strdup("m");
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "right_card")) {
			relation->right_card = g_ascii_strdown(get_clean_content ( (gchar *)xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode->xmlChildrenNode,1)),-1);
			if (!g_ascii_strcasecmp("n",relation->right_card)) relation->right_card = g_strdup("m");
		}
		else if (!xmlStrcmp(prop_val, (const xmlChar *) "rotated")) {
			prop_val = xmlGetProp(xml_node->xmlChildrenNode,(const xmlChar *) "val");
			if (!xmlStrcmp(prop_val, (const xmlChar *) "true")) relation->is_rotated = TRUE;
		}
		xml_node = xml_node->next;
	}
	bima_insert_parse_log(
		g_strdup_printf("\t name  : %s, is_rotated:%d\n",relation->name,relation->is_rotated));

	return relation;
}

void
dia_er_parse_connection (xmlNodePtr xml_node_parent,BimaAppData *dia_dt)
{
	GList *entity, *relation, *attribute;
	GList *tmp_list;
	BimaConnection *cnt_tmp=NULL;
	xmlNodePtr xml_node;
	gboolean is_total;
	gchar *to1, *to2;
	gchar *conn1, *conn2;
	xmlChar *prop_val=NULL;
	is_total = FALSE;

	xml_node = xml_node_parent->children;
	while (xml_node != NULL) {
		if (!xmlStrcmp(xml_node->name, (const xmlChar *)"connections")) {
			to1 = (gchar *) xmlGetProp(xml_node->children, (const xmlChar *)"to");
			conn1 = (gchar *) xmlGetProp(xml_node->children,(const xmlChar *)"connection");

			to2 = (gchar *) xmlGetProp(xml_node->children->next,(const xmlChar *)"to");
			conn2 = (gchar *)  xmlGetProp(xml_node->children->next,(const xmlChar *)"connection");

			if ((to1 == NULL) || (to2 == NULL ) || (conn1 == NULL )  || (conn2 == NULL ))
				return ;

			entity = bima_get_l_object_by_prop(dia_dt->entities, "id", to1);
			if (entity == NULL ) 
				entity = bima_get_l_object_by_prop(dia_dt->entities, "id", to2);
			relation = bima_get_l_object_by_prop(dia_dt->relations, "id", to1);
			if (relation == NULL ) {
				relation = bima_get_l_object_by_prop(dia_dt->relations, "id", to2);
				conn1 = conn2;
			}
			
			attribute = bima_get_l_object_by_prop(l_attributes, "id", to1);
			if (attribute == NULL )
				attribute = bima_get_l_object_by_prop(l_attributes, "id", to2);

			if (attribute != NULL) 	{
				l_attributes = g_list_remove_link(l_attributes,attribute);
				if ( entity != NULL || relation != NULL) {
				
					if (relation) 
						bima_relation_add_attribute((BimaRelation *) (relation->data), (BimaAttribute *) (attribute->data));
					else 
						bima_entity_add_attribute((BimaEntity *) (entity->data), (BimaAttribute *) (attribute->data));
					attribute->data = NULL;
					g_list_free(attribute);
				/*
					if (relation) entity = relation;
					tmp_list = ((BimaEntity *) (entity->data))->attributes;
					if ( (((BimaAttribute *) (attribute->data))->is_key == TRUE) && tmp_list) {
						// we put a key at the start of the list 
						tmp_list->prev = attribute;
						attribute->next = tmp_list;
						tmp_list = attribute; 
						((BimaEntity *) (entity->data))->num_of_key++;
					} else
						tmp_list = g_list_concat(tmp_list, attribute);
						
					((BimaEntity *) (entity->data))->attributes = tmp_list;
					((BimaAttribute *) (attribute->data))->parent = (GObject *) (entity->data);
				*/
					entity = NULL;
					relation  = NULL;
				}
			} if ((entity != NULL) && (relation != NULL )) {
				cnt_tmp = bima_connection_new();
				cnt_tmp->connection = atoi(conn1);
				cnt_tmp->entity_id = g_strdup(((BimaEntity *) (entity->data))->id);
				cnt_tmp->entity = (BimaEntity *) (entity->data);
				
				bima_relation_add_connection((BimaRelation *) (relation->data), cnt_tmp);
				//g_print("to1 %s entity %s , to2 %s rel %s %d \n", to1, cnt_tmp->entity->name, to2, ((BimaRelation *) (relation->data))->name , ((BimaRelation *) (relation->data))->num_of_connection);
			}
		}
		else {
			prop_val = xmlGetProp(xml_node,(const xmlChar *) "name");
			if (!xmlStrcmp(prop_val, (const xmlChar *)"total")) {
				prop_val = xmlGetProp(xml_node->children,(const xmlChar *) "val");
				if (!xmlStrcmp(prop_val, (const xmlChar *)"true") ) {
					is_total = TRUE;
				}
			}		
		}
		entity = NULL;
		relation = NULL;
		attribute = NULL;
		xml_node = xml_node->next;
	}

	if (cnt_tmp) {
		cnt_tmp->is_total = is_total;

		bima_insert_parse_log(
			g_strdup_printf("\tConnection entity_id:%s\n",cnt_tmp->entity_id));
	}
	
}

gchar *
dia_find_module(gchar **source)
{
	gchar *token;
	gchar *fnd1;
	gchar *tmp;
	gint num1;

	token = NULL;
	fnd1 = strchr(*source, '.');
	if (fnd1) {
		num1 = fnd1 - *source;
		token = g_strndup(*source , num1 );
		tmp = g_strdup(fnd1+1 );
		g_free(*source);
		*source = tmp;
	}
	return token;
}

void
dia_er_parse (gchar *er_file, BimaAppData *app_dt)
{
	xmlDocPtr xml_doc;
	xmlNodePtr xml_node, xml_layer;
	xmlChar *prop_val;

	GObject *dia_obj;
	GList *list;

	BimaModule *module=NULL;
	gchar *root_module_id = NULL, *module_id=NULL, *parent_module_id=NULL;
	gchar *token;
	gchar *name;
	xmlKeepBlanksDefault(0);

	xml_doc = xmlParseFile(er_file);
	if (xml_doc == NULL) {
		g_print("not dia file\n");
		return;
	} else {
		g_print("found dia file\n");
	}
	
	app_dt->diagram_type = DIAGRAM_ER;
	
	if (app_dt->modules != NULL) {
		list = g_list_first(app_dt->modules);
		if (list)
			module = (BimaModule *) list->data;
		root_module_id = module->id;
	}
	//g_printf("root %s\n",root_module_id);
	xml_layer = xmlDocGetRootElement(xml_doc);
	xml_layer = xml_layer->children;

	while ((xml_layer != NULL) ) {
		if (!xmlStrcmp(xml_layer->name, (const xmlChar *)"layer")) {
			xml_node = xml_layer->children;
			while (xml_node != NULL) {
			
				token = NULL;
				if (!parent_module_id) {
					g_free(parent_module_id);
					parent_module_id = NULL;
				}
				parent_module_id = g_strdup(root_module_id);

				if (module_id) {
					g_free(module_id);
					module_id = NULL;
				}
				
				//ER - Attribute ,ER - Entity , ER - Relationship
				prop_val = xmlGetProp(xml_node,(const xmlChar *)"type");
				if (!xmlStrcmp(prop_val,(const xmlChar *)"ER - Entity")) {
					bima_insert_parse_log("Entity Found\n");
					dia_obj = (GObject *) dia_er_parse_entity (xml_doc , xml_node);
					
					// looking module name 
					// if name = MDL.NAME , will parse MDL as Module 
					name = g_strdup(((BimaEntity *)dia_obj)->name);
					token = dia_find_module(&name);
					while (token) {
						if (module_id) {
							g_free(parent_module_id); parent_module_id = NULL;							
							parent_module_id = g_strdup(module_id) ;
							g_free(module_id); module_id = NULL;							
						}
						module_id = token;
						bima_app_data_create_and_add_module(app_dt, module_id , parent_module_id);
						token = dia_find_module(&name);
					}
					
					g_free(((BimaEntity *)dia_obj)->name);
					((BimaEntity *)dia_obj)->name = name;
					((BimaEntity *)dia_obj)->abbreviation = g_ascii_strdown(name,-1);

					if (module_id)
						((BimaEntity *)dia_obj)->module_id = g_strdup(module_id);
					else
						((BimaEntity *)dia_obj)->module_id = g_strdup(parent_module_id);
					
					bima_app_data_add_entity(app_dt,(BimaEntity *)dia_obj);
					//g_printf("mdl %s.%s\n", ((BimaEntity *)dia_obj)->module_id, ((BimaEntity *)dia_obj)->name);
					
				}
				else if (!xmlStrcmp(prop_val, (const xmlChar *) "ER - Relationship")) {
					bima_insert_parse_log("Relation Found\n");
					dia_obj = (GObject *) dia_er_parse_relation(xml_doc ,xml_node);

					// looking module name 
					// if name = MDL.NAME , will parse MDL as Module 
					name = g_strdup(((BimaRelation *)dia_obj)->name);
					token = dia_find_module(&name);
					while (token) {
						if (module_id) {
							g_free(parent_module_id); parent_module_id = NULL;							
							parent_module_id = g_strdup(module_id) ;
							g_free(module_id); module_id = NULL;							
						}
						module_id = token;
						bima_app_data_create_and_add_module(app_dt, module_id , parent_module_id);
						token = dia_find_module(&name);
					}
					
					g_free(((BimaRelation *)dia_obj)->name);
					((BimaRelation *)dia_obj)->name = name;
					((BimaRelation *)dia_obj)->abbreviation = g_ascii_strdown(name,-1);

					if (module_id) 
						((BimaRelation *)dia_obj)->module_id = g_strdup(module_id);
					else
						((BimaRelation *)dia_obj)->module_id = g_strdup(parent_module_id);

					bima_app_data_add_relation(app_dt,(BimaRelation *)dia_obj);
					
					//((BimaRelation *)dia_obj)->module_id = g_strdup(module_id);
					//bima_app_data_add_relation(app_dt,(BimaRelation *)dia_obj);
				}
				else if (!xmlStrcmp(prop_val, (const xmlChar *) "ER - Attribute")) {
					bima_insert_parse_log("Attribute Found\n");
					dia_obj = (GObject *) dia_er_parse_atrribute (xml_doc ,xml_node);
					l_attributes = g_list_append(l_attributes, (gpointer)dia_obj);
				}
				xml_node = xml_node->next;
			}
		}
		xml_layer = xml_layer->next;
	}
	
	xml_layer = xmlDocGetRootElement(xml_doc);
	xml_layer = xml_layer->children->next;

	while ((xml_layer != NULL) ) {
		if (!xmlStrcmp(xml_layer->name, (const xmlChar *)"layer")) {

			xml_node = xml_layer->children;
			while (xml_node != NULL) {

				prop_val = xmlGetProp(xml_node,(const xmlChar *)"type");
				if (!xmlStrcmp(prop_val, (const xmlChar *)"ER - Participation")) {
					bima_insert_parse_log("Participation Found\n");
					dia_er_parse_connection(xml_node, app_dt);
				}
				else if (!xmlStrcmp(prop_val, (const xmlChar *) "Standard - Line")) {
					bima_insert_parse_log("Standard Line Found\n");
					dia_er_parse_connection(xml_node, app_dt);
				}
				xml_node = xml_node->next;
			}
		}
		xml_layer = xml_layer->next;
	}
	xmlFreeDoc(xml_doc);
}

void 
dia_er_parse_foreign_key(BimaAppData *app_dt) 
{
	GList *rel_lst, *conn_lst, *conn_lst1, *tmp_lst;
	BimaRelation *rel_dt;
	BimaConnection *conn_dt;
	BimaForeignKey *fk_tmp;
	BimaEntity *ent_tmp;
	
	for (rel_lst = g_list_first(app_dt->relations);rel_lst != NULL; rel_lst = rel_lst->next){
		rel_dt = (BimaRelation *)(rel_lst->data);
//		g_print("%s %s to %s %d\n", rel_dt->name, rel_dt->left_card, rel_dt->right_card, rel_dt->num_of_connection);

		if 	( (
				((!strcmp("1",rel_dt->left_card)) && (!strcmp("m",rel_dt->right_card))) ||
				((!strcmp("m",rel_dt->left_card)) && (!strcmp("1",rel_dt->right_card)))
			  ) && (rel_dt->num_of_connection == 2)
			) 
		{
			// locate which connection is get 'M' , first or second 
			conn_lst  = g_list_first(rel_dt->connections);
			conn_lst1 = conn_lst->next;		
			conn_dt = ((BimaConnection *) (conn_lst->data));

						//is rotated
						/*  m l  --> this
							  2
						  1 /\ 3
						0 <    > 4
						  7 \/ 5
						    6
						   n r
						*/
			if (!(( (rel_dt->is_rotated == TRUE) && (conn_dt->connection < 4) && (!strcmp("m",rel_dt->left_card)) ) ||
				( (rel_dt->is_rotated == FALSE) && ( (conn_dt->connection <= 2) || (conn_dt->connection > 6) ) && (!strcmp("m",rel_dt->left_card)) ) ||
				( (rel_dt->is_rotated == TRUE) && (conn_dt->connection > 4)  && (!strcmp("m",rel_dt->right_card)) ) ||
				( (rel_dt->is_rotated == FALSE) && ( (conn_dt->connection > 2) || (conn_dt->connection <= 6) ) && (!strcmp("m",rel_dt->right_card)) )
				)) 
			{
				conn_lst1  = g_list_first(rel_dt->connections);
				conn_lst = conn_lst1->next;		
				conn_dt = ((BimaConnection *) (conn_lst->data));
			}
			rel_dt->rel_type = REL_MTO1;
			fk_tmp = bima_foreign_key_new();

			ent_tmp = ((BimaConnection *) (conn_lst1->data))->entity;
			fk_tmp->pk_obj_id = g_strdup(ent_tmp->id);
			fk_tmp->relation = rel_dt;
			if (ent_tmp == ((BimaConnection *) (conn_lst->data))->entity) 
				fk_tmp->name = rel_dt->abbreviation; //g_strdup(rel_dt->name);
			else 
				fk_tmp->name = ent_tmp->abbreviation; //g_strdup(ent_tmp->name);

			fk_tmp->relation_type = REL_MTO1;
			ent_tmp = ((BimaConnection *) (conn_lst->data))->entity;			
			bima_entity_add_foreign_key(ent_tmp,fk_tmp);
			//ent_tmp->foreign_key = g_list_append(ent_tmp->foreign_key, (gpointer)fk_tmp);

			// if reltion have attribute, 
			// we add foreign attribute to the entity
			if (rel_dt->attributes != NULL ) {
				for (tmp_lst = g_list_first(rel_dt->attributes);tmp_lst != NULL; tmp_lst = tmp_lst->next){
					fk_tmp = bima_foreign_key_new();

					fk_tmp->pk_obj_id = g_strdup(rel_dt->id);
					fk_tmp->name = rel_dt->abbreviation; //g_strdup(rel_dt->name);
					fk_tmp->relation = rel_dt;
					
					//ent_tmp->foreign_attr = g_list_append(ent_tmp->foreign_attr, (gpointer)fk_tmp);	
					bima_entity_add_foreign_attribute(ent_tmp,fk_tmp);
				}
			}
		
		} // m to n relation
		else if	( ((!g_ascii_strcasecmp("m",rel_dt->left_card)) && (!g_ascii_strcasecmp("m",rel_dt->right_card))) ||
					(rel_dt->num_of_connection > 2)
				) 
		{
			rel_dt->rel_type = REL_MTOM;

			for (conn_lst = g_list_first(rel_dt->connections);conn_lst != NULL; conn_lst = conn_lst->next){
				fk_tmp = bima_foreign_key_new();
				ent_tmp = ((BimaConnection *) (conn_lst->data))->entity;
				fk_tmp->pk_obj_id = g_strdup(ent_tmp->id);
				fk_tmp->name = ent_tmp->abbreviation; //g_strdup(ent_tmp->name);
				fk_tmp->relation_type = REL_MTO1;
				//rel_dt->foreign_key = g_list_append(rel_dt->foreign_key, (gpointer)fk_tmp);
				bima_relation_add_foreign_key(rel_dt,fk_tmp);
			}
		} // 1 to 1 relation
		else 
		{ 
			rel_dt->rel_type = REL_1TO1;
		
			if ( ((BimaConnection *)(conn_lst->data))->is_total ) {
				conn_lst1  = g_list_first(rel_dt->connections);
				conn_lst = conn_lst1->next;
			} else {
				conn_lst  = g_list_first(rel_dt->connections);
				conn_lst1 = conn_lst->next;
			}

			g_return_if_fail(conn_lst1!=NULL);
			g_return_if_fail(conn_lst!=NULL);

			fk_tmp = bima_foreign_key_new();
			
			ent_tmp = ((BimaConnection *) (conn_lst->data))->entity;
			fk_tmp->pk_obj_id = g_strdup(ent_tmp->id);
			fk_tmp->name = rel_dt->abbreviation; //g_strdup(rel_dt->name);
			fk_tmp->relation_type = REL_1TO1;
			ent_tmp = ((BimaConnection *) (conn_lst1->data))->entity;
			//ent_tmp->foreign_key = g_list_append(ent_tmp->foreign_key, (gpointer)fk_tmp);
			bima_entity_add_foreign_key(ent_tmp,fk_tmp);
			if (rel_dt->attributes != NULL ) {
				for (tmp_lst = g_list_first(rel_dt->attributes);tmp_lst != NULL; tmp_lst = tmp_lst->next){
					fk_tmp = bima_foreign_key_new();

					fk_tmp->pk_obj_id = g_strdup(rel_dt->id);
					fk_tmp->name = rel_dt->abbreviation; //g_strdup(rel_dt->name);
					fk_tmp->relation = rel_dt;
					
					//ent_tmp->foreign_attr = g_list_append(ent_tmp->foreign_attr, (gpointer)fk_tmp);
					bima_entity_add_foreign_attribute(ent_tmp,fk_tmp);
				}
			}
		}
	}
}
