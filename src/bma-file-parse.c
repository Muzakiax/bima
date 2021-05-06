/***************************************************************************
 *            bma-file-parse.c
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

#include "bma-file-parse.h"

extern void
bima_insert_parse_log(gchar *log);

BimaAttribute* 
bma_file_parse_attribute(xmlDocPtr xml_doc, xmlNodePtr xml_node_parent)
{
	BimaAttribute* attribute=NULL;
	xmlNodePtr  xml_node;
	
	attribute = bima_attribute_new();
	attribute->id = (gchar *) xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	attribute->name = (gchar *) xmlGetProp(xml_node_parent,(const xmlChar *) "name");
	attribute->is_weak = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "is_weak"));
	attribute->is_key = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "is_key"));
	attribute->not_null = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "not_null"));
	attribute->field_type = xmlGetProp(xml_node_parent,(const xmlChar *) "field_type");
	attribute->length = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "length"));
	attribute->control_type = xmlGetProp(xml_node_parent,(const xmlChar *) "control_type");

	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Parameter")) {
			attribute->parameter = xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode,1);
			//g_printf("attribute->parameter %s\n",attribute->parameter);
		} else if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Description")) {
			attribute->description = xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode,1);
		} else if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Title")) {
			attribute->title = xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode,1);
		}
		
		xml_node = xml_node->next;
	}

	bima_insert_parse_log(
		g_strdup_printf("\t Attribute name  : %s, key:%d\n",attribute->name,attribute->is_key));

	return attribute;

}

BimaForeignKey*
bma_file_parse_foreign_key(xmlDocPtr xml_doc, xmlNodePtr xml_node_parent)
{
	BimaForeignKey *fk = NULL;
	//xmlNodePtr  xml_node;
	xmlChar *prop_val;
		
	fk = bima_foreign_key_new();
	
	//if (!fk)
	//	return NULL;
		
	fk->pk_obj_id = xmlGetProp(xml_node_parent,(const xmlChar *) "primary_key_id");
	prop_val = xmlGetProp(xml_node_parent,(const xmlChar *) "relation_type");

	if (!xmlStrcmp(prop_val, (const xmlChar *) "REL_NONE")) {
		fk->relation_type = REL_NONE;
	} else if (!xmlStrcmp(prop_val, (const xmlChar *) "REL_1TO1")) {
		fk->relation_type = REL_1TO1;
	} else if (!xmlStrcmp(prop_val, (const xmlChar *) "REL_1TOM")) {
		fk->relation_type = REL_1TOM;
	} else if (!xmlStrcmp(prop_val, (const xmlChar *) "REL_MTO1")) {
		fk->relation_type = REL_MTO1;
	} else if (!xmlStrcmp(prop_val, (const xmlChar *) "REL_MTOM")) {
		fk->relation_type = REL_MTOM;
	}

	bima_insert_parse_log(
		g_strdup_printf("\t Foreign Key name  : %s\n",fk->pk_obj_id));

	return fk;
}

BimaEntity*
bma_file_parse_entity(xmlDocPtr xml_doc, xmlNodePtr xml_node_parent) 
{
	BimaEntity* entity=NULL;
	BimaAttribute *attribute = NULL;
	BimaForeignKey *fk = NULL;

	xmlNodePtr xml_node, xml_node_child;

	entity = bima_entity_new();

	entity->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	entity->name = (gchar *) xmlGetProp(xml_node_parent,(const xmlChar *) "name");
	entity->module_id = xmlGetProp(xml_node_parent,(const xmlChar *) "module");
	entity->is_weak = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "is_weak"));
	//entity->num_of_key = atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "num_of_key"));
	entity->abbreviation = xmlGetProp(xml_node_parent,(const xmlChar *) "abbreviation");

	bima_insert_parse_log(
		g_strdup_printf("\t Entity name  : %s, weak:%d\n",entity->name,entity->is_weak));
	
	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Attributes")) {
			xml_node_child = xml_node->xmlChildrenNode;
			while (xml_node_child != NULL) {
				attribute = bma_file_parse_attribute(xml_doc, xml_node_child);
				bima_entity_add_attribute(entity, attribute);
				xml_node_child = xml_node_child->next;
			}
		} else if (!xmlStrcmp(xml_node->name, (const xmlChar *)"ForeignKeys")) {
			xml_node_child = xml_node->xmlChildrenNode;
			while (xml_node_child != NULL) {
				fk = bma_file_parse_foreign_key(xml_doc, xml_node_child);
				bima_entity_add_foreign_key(entity, fk);
				
				xml_node_child = xml_node_child->next;
			}
		} else if (!xmlStrcmp(xml_node->name, (const xmlChar *)"ForeignAttributes")) {
			xml_node_child = xml_node->xmlChildrenNode;
			while (xml_node_child != NULL) {
				fk = bma_file_parse_foreign_key(xml_doc, xml_node_child);
				bima_entity_add_foreign_attribute(entity, fk);
				
				xml_node_child = xml_node_child->next;
			}
		}
		xml_node = xml_node->next;
	}

	return entity;
}

BimaRelation*
bma_file_parse_relation(xmlDocPtr xml_doc, xmlNodePtr xml_node_parent) 
{
	BimaRelation* relation=NULL;
	BimaAttribute *attribute = NULL;
	BimaForeignKey *fk = NULL;

	xmlNodePtr xml_node, xml_node_child;

	relation = bima_relation_new();

	relation->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	relation->name = xmlGetProp(xml_node_parent,(const xmlChar *) "name");
	relation->module_id = xmlGetProp(xml_node_parent,(const xmlChar *) "module");
	relation->left_card = xmlGetProp(xml_node_parent,(const xmlChar *) "left_card");
	relation->right_card = xmlGetProp(xml_node_parent,(const xmlChar *) "right_card");
	relation->is_rotated= atoi(xmlGetProp(xml_node_parent,(const xmlChar *) "is_rotated"));
	relation->abbreviation = xmlGetProp(xml_node_parent,(const xmlChar *) "abbreviation");

	bima_insert_parse_log(
		g_strdup_printf("\t Relation name  : %s \n",relation->name));

	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Attributes")){
			xml_node_child = xml_node->children;
			while (xml_node_child != NULL) {
				attribute = bma_file_parse_attribute(xml_doc, xml_node_child);
				bima_relation_add_attribute(relation, attribute);
				xml_node_child = xml_node_child->next;
			}
		} else if (!xmlStrcmp(xml_node->name, (const xmlChar *)"ForeignKeys"))  {
			xml_node_child = xml_node->children;
			while (xml_node_child != NULL) {

				fk = bma_file_parse_foreign_key(xml_doc, xml_node_child);
				bima_relation_add_foreign_key(relation, fk);
				
				xml_node_child = xml_node_child->next;
			}
		}
		xml_node = xml_node->next;
	}

	return relation;
}

BimaModule* 
bma_file_parse_module(xmlDocPtr xml_doc, xmlNodePtr xml_node_parent)
{
	BimaModule* module=NULL;
	xmlNodePtr  xml_node;
	
	module = bima_module_new();
	module->id = xmlGetProp(xml_node_parent,(const xmlChar *) "id");
	module->name = xmlGetProp(xml_node_parent,(const xmlChar *) "name");
	module->parent_id = xmlGetProp(xml_node_parent,(const xmlChar *) "parent_id");

	xml_node = xml_node_parent->xmlChildrenNode;
	while (xml_node != NULL) {
		if (!xmlStrcmp(xml_node->name, (const xmlChar *) "Description")) {
			module->description = xmlNodeListGetString(xml_doc, xml_node->xmlChildrenNode,1);
		}
		xml_node = xml_node->next;
	}

	bima_insert_parse_log(
		g_strdup_printf("\t name  : %s parent:%s\n",module->name,module->parent_id));

	return module;

}

void
bma_file_reparse(BimaAppData *app_data)
{
	gint i;
	GList *fk_list, *list;
	BimaEntity *entity=NULL, *entity_pk;
	//BimaAttribute *attribute=NULL;
	BimaForeignKey *fk = NULL;

		for ( i = 0 ; i < 2 ; i++) {
			if (i == 0 )
				list = g_list_first(app_data->entities);
			else 
				list = g_list_first(app_data->relations);

			while (list != NULL) {
				entity = (BimaEntity *) (list->data);
				
				fk_list = g_list_first(entity->foreign_key);
				while (fk_list != NULL) {
					fk = (BimaForeignKey *) (fk_list->data);

					entity_pk = bima_get_object_by_prop(app_data->entities, "id", fk->pk_obj_id);

					if (entity_pk) 
						fk->name = entity_pk->abbreviation;
					else
						fk->name = entity->abbreviation;
					
					fk_list = fk_list->next;
				}
				
				list = list->next;
			}
		}
}

void
bma_file_parse (gchar *bma_file, BimaAppData *app_data)
{

	xmlDocPtr xml_doc;
	xmlNodePtr xml_node, xml_parent_node;
	xmlChar *prop_val;

	GObject *bma_obj=NULL;
//	GList *list;

	xmlKeepBlanksDefault(0);

	xml_doc = xmlParseFile(bma_file);
	if (xml_doc == NULL) {
		g_print("not dia file\n");
		return;
	} else {
		g_print("found dia file\n");
	}

//	app_data->diagram_type = DIAGRAM_ER;

	xml_parent_node = xmlDocGetRootElement(xml_doc);
	xml_parent_node = xml_parent_node->xmlChildrenNode;

	while ((xml_parent_node != NULL) ) {
		if (!xmlStrcmp(xml_parent_node->name, (const xmlChar *)"Modules")) {
			xml_node = xml_parent_node->xmlChildrenNode;
			while (xml_node != NULL) {

				bima_insert_parse_log("Module Found\n");
				bma_obj = (GObject *) bma_file_parse_module(xml_doc , xml_node);
				bima_app_data_add_module(app_data,(BimaModule *)bma_obj);
				
				xml_node = xml_node->next;
			}
		} else if (!xmlStrcmp(xml_parent_node->name, (const xmlChar *)"Entities")) {
			xml_node = xml_parent_node->xmlChildrenNode;
			while (xml_node != NULL) {

				bima_insert_parse_log("Entity Found\n");
				bma_obj = (GObject *) bma_file_parse_entity(xml_doc , xml_node);
				bima_app_data_add_entity(app_data,(BimaEntity *)bma_obj);
				xml_node = xml_node->next;
			}
		} else if (!xmlStrcmp(xml_parent_node->name, (const xmlChar *)"Relations")) {
			xml_node = xml_parent_node->xmlChildrenNode;
			while (xml_node != NULL) {
				bima_insert_parse_log("Relation Found\n");
				bma_obj = (GObject *) bma_file_parse_relation(xml_doc , xml_node);
				bima_app_data_add_relation(app_data,(BimaRelation *)bma_obj);				
				xml_node = xml_node->next;
			}
		}

		xml_parent_node = xml_parent_node->next;
	}
	xmlFreeDoc(xml_doc);
	bma_file_reparse(app_data);
}
