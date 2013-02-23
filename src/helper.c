/*
 * helper.c
 *
 *  Created on: Feb 23, 2013
 *      Author: ukiewel
 */

#include <stdio.h>

void debug(char *message, int isdebug) {
	if (isdebug == 1)
		fprintf(stderr, message);
}
