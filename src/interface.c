/*
 * interface.c
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/nanohttp.h>
#include "bindtop.h"

bindtop_Settings_Type readConfigFile(char *ConfigFile) {
	bindtop_Settings_Type *bindtop_Settings;
	GKeyFile *GConfigFile;
	GKeyFileFlags flags;
	GError *error = NULL;

	GConfigFile = g_key_file_new ();
	flags = G_KEY_FILE_KEEP_COMMENTS;
	if (!g_key_file_load_from_file (GConfigFile, ConfigFile, flags, &error)) {
	    g_error (error->message);
	    exit(EXIT_FAILURE);
	  }
	bindtop_Settings = g_slice_new (bindtop_Settings_Type);
	bindtop_Settings->url = g_key_file_get_string(GConfigFile, "FILE", "URL", NULL);
	bindtop_Settings->tmp_file = g_key_file_get_string(GConfigFile, "FILE", "TMP_FILE", NULL);
	bindtop_Settings->zabbix_server = g_key_file_get_string(GConfigFile, "ZABBIX", "SERVER", NULL);
	bindtop_Settings->zabbix_sender = g_key_file_get_string(GConfigFile, "ZABBIX", "SENDER", NULL);
	bindtop_Settings->zabbix_port = g_key_file_get_string(GConfigFile, "ZABBIX", "PORT", NULL);
	bindtop_Settings->zabbix_node = g_key_file_get_string(GConfigFile, "ZABBIX", "NODE", NULL);
	return *bindtop_Settings;
}

int getXMLFile(char *url, char *tmp_file) {
	int ret;

	xmlNanoHTTPInit();
	ret = xmlNanoHTTPFetch(url, tmp_file, NULL);
	xmlNanoHTTPCleanup();
	if (ret == -1)
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

int delXMLFile(char *tmp_file) {
	int ret;
	char *rm = "rm -f ";
	char *command;

	command = malloc(sizeof(rm) + sizeof(tmp_file));
	if (command == NULL) {
		fprintf(stderr, "Error allocating %i bytes of memory",sizeof(rm) + sizeof(tmp_file));
		return EXIT_FAILURE;
	} else {
		strcpy(command, rm);
		strcat(command, tmp_file);
		ret = system(command);
		free(command);
		if (ret == -1)
			return EXIT_FAILURE;
		else
		return EXIT_SUCCESS;
	}
}
