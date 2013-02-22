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

	bindtop_Settings = readConfigFile(argv[1]);
	getBindStatisticsZabbix(bindtop_Settings);

}
