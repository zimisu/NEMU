#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	char* expr;
	uint32_t oldValue;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */


} WP;

bool delete_wp_num(int num);
int check_wp();
void show_wp();
WP* new_wp();

#endif
