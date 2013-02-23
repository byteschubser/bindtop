/*
 * main.c
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "statistics.h"

int main(int argc, char *argv[]) {
	bindtop_Settings_Type bindtop_Settings;

	if ( argc != 2) {
		fprintf(stderr, "%s <config file>\n", argv[0]);
		return EXIT_FAILURE;
	} else {
		bindtop_Settings = readConfigFile(argv[1]);
		delXMLFile(bindtop_Settings.tmp_file);
		getBindStatisticsZabbix(bindtop_Settings);
		return EXIT_SUCCESS;
	}
}
