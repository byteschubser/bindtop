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
	bindtop_Settings->debug = g_key_file_get_integer(GConfigFile, "DEBUG", "DEBUG", NULL);
	return *bindtop_Settings;
}

int getXMLFile(bindtop_Settings_Type bindtop_Settings) {
	int ret;

	xmlNanoHTTPInit();
	ret = xmlNanoHTTPFetch(bindtop_Settings.url, bindtop_Settings.tmp_file, NULL);
	xmlNanoHTTPCleanup();
	if (ret == -1) {
		debug("Unable to fetch xml data from bind. Aborting...\n", bindtop_Settings.debug);
		exit(NO_XML_DATA);
	} else
		return EXIT_SUCCESS;
}

int delXMLFile(bindtop_Settings_Type bindtop_Settings) {
	int ret;
	char *rm = "rm -f ";
	char *command;

	command = malloc(sizeof(rm) + sizeof(bindtop_Settings.tmp_file));
	if (command == NULL) {
		debug("Error allocating memory.\n", bindtop_Settings.debug);
		debug("Please delete the temporary file by your own!\n", bindtop_Settings.debug);
		exit(NO_MEMORY);
	} else {
		strcpy(command, rm);
		strcat(command, bindtop_Settings.tmp_file);
		ret = system(command);
		free(command);
		if (ret == -1) {
			debug("Error deleting the temporary file.\n", bindtop_Settings.debug);
			return EXIT_FAILURE;
		} else
			return EXIT_SUCCESS;
	}
}
