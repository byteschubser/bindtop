/*
 * interface.h
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "bindtop.h"

int getXMLFile(char*, char*);
int delXMLFile(char*);
bindtop_Settings_Type readConfigFile(char *);

#endif /* INTERFACE_H_ */
