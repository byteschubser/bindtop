/*
 * interface.h
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "bindtop.h"

int getXMLFile(bindtop_Settings_Type);
int delXMLFile(bindtop_Settings_Type);
bindtop_Settings_Type readConfigFile(char *);

#endif /* INTERFACE_H_ */
