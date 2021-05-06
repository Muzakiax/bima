
void
bima_write_to_xml(char *file_name, ERDiagram *diagram)
{
	//clean
	xmlDocPtr new_doc;
	xmlNodePtr xml_node, xml_root_node;
	GList *tmp_list;
	
	EREntityNodeList entity_node;
	ERRelationNodeList relation_node;
	
	BimaView *tmp_view;
	BimaForm *tmp_object;
	
	if (!file_name)
		return;
	new_doc = xmlNewDoc("1.0");
	
	xml_root_node = xmlNewDocNode(new_doc, NULL,"Bima", NULL);
	entity_node = diagram->entities;
	relation_node = diagram->relations;
	//form_node = diagram->forms;
	xml_node = xmlNewChild( xml_root_node,NULL,"Diagram",NULL);
	while (entity_node != NULL ) {
		bima_entity_write_to_xml ( xml_node , entity_node);
		entity_node = entity_node->next;
	}

	while (relation_node != NULL ) {
		bima_relation_write_to_xml ( xml_node , relation_node);
		relation_node = relation_node->next;
	}
	
	xml_node = xmlNewChild( xml_root_node,NULL,"Views",NULL);	
	tmp_list = g_list_first(diagram->views);
	while (tmp_list ) {
		tmp_view = (BimaView *) tmp_list->data;
		bima_view_write_to_xml ( xml_node, tmp_view);		 
		tmp_list = g_list_next(tmp_list);
	}
	
	xml_node = xmlNewChild( xml_root_node ,NULL,"Forms",NULL);
	tmp_list = g_list_first(diagram->forms);
	while (tmp_list ) {
		tmp_object = ( BimaForm *) tmp_list->data;		
		bima_form_report_write_to_xml( xml_node, tmp_object);
		tmp_list = g_list_next(tmp_list);
	}

	xml_node = xmlNewChild( xml_root_node ,NULL,"Reports",NULL);
	tmp_list = g_list_first(diagram->reports);
	while (tmp_list ) {
		tmp_object = (BimaForm*) tmp_list->data;		
		bima_form_report_write_to_xml( xml_node, tmp_object);
		tmp_list = g_list_next(tmp_list);
	}

	xmlSaveFile(file_name, new_doc);
	xmlFreeDoc(new_doc);
	return ;
}
