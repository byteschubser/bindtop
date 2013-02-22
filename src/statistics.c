/*
 * statistics.c
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "bindtop.h"
#include "interface.h"

static void ZabbixCommand(bindtop_Settings_Type bindtop_Settings, char *key, char *value) {
	char *command;
	command = malloc(sizeof(bindtop_Settings.zabbix_sender) +
						sizeof(bindtop_Settings.zabbix_node) +
						sizeof(bindtop_Settings.zabbix_server) +
						sizeof(bindtop_Settings.zabbix_port) +
						sizeof(key) +
						sizeof(value) +
						sizeof(" -z ") +
						sizeof(" -p ") +
						sizeof(" -s ") +
						sizeof(" -k ") +
						sizeof(" -o "));
	strcpy(command, bindtop_Settings.zabbix_sender);
	strcat(command, " -z ");
	strcat(command, bindtop_Settings.zabbix_server);
	strcat(command, " -p ");
	strcat(command, bindtop_Settings.zabbix_port);
	strcat(command, " -s ");
	strcat(command, bindtop_Settings.zabbix_node);
	strcat(command, " -k ");
	strcat(command, key);
	strcat(command, " -o ");
	strcat(command, value);
	system(command);
	free(command);
}

int getBindStatisticsZabbix(bindtop_Settings_Type bindtop_Settings) {
	xmlDocPtr bindtop_xmlDocPtr;
	xmlNodeSetPtr bindtop_nodeset;
	xmlXPathObjectPtr bindtop_result;
	xmlXPathContextPtr bindtop_xmlPathCtx;
	xmlChar *key;
	xmlChar *value;
	int i;
	xmlChar *xpath_incoming_queries = (xmlChar*) "/isc/bind/statistics/server/queries-in/rdtype/*";

	getXMLFile(bindtop_Settings.url, bindtop_Settings.tmp_file);
	bindtop_xmlDocPtr = xmlParseFile(bindtop_Settings.tmp_file);
	bindtop_xmlPathCtx = xmlXPathNewContext(bindtop_xmlDocPtr);
	bindtop_result = xmlXPathEvalExpression(xpath_incoming_queries, bindtop_xmlPathCtx);
	xmlXPathFreeContext(bindtop_xmlPathCtx);
	if (bindtop_result) {
		bindtop_nodeset = bindtop_result->nodesetval;
	    for (i = 0; i < bindtop_nodeset->nodeNr; i++) {
	    	key = xmlNodeListGetString(bindtop_xmlDocPtr, bindtop_nodeset->nodeTab[i]->xmlChildrenNode, 1);
	    	i++;
	    	value = xmlNodeListGetString(bindtop_xmlDocPtr, bindtop_nodeset->nodeTab[i]->xmlChildrenNode, 1);
	        ZabbixCommand(bindtop_Settings, key, value);
	        xmlFree(key);
	        xmlFree(value);
	    }
	    xmlXPathFreeObject(bindtop_result);
	}
	xmlFreeDoc(bindtop_xmlDocPtr);
	xmlCleanupParser();
	delXMLFile(bindtop_Settings.tmp_file);
	return EXIT_SUCCESS;
}
