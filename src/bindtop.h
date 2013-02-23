/*
 * bindtop.h
 *
 *  Created on: Feb 21, 2013
 *      Author: ukiewel
 */

#ifndef BINDTOP_H_
#define BINDTOP_H_

typedef struct
{
  char *url;
  char *tmp_file;
  char *zabbix_server;
  char *zabbix_sender;
  char *zabbix_port;
  char *zabbix_node;
  int debug;
} bindtop_Settings_Type;

#define NO_MEMORY 		1000
#define NO_CONFIG_FILE	1001

void debug(char*, int);

#endif /* BINDTOP_H_ */
