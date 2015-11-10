#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	char expr[32];
	uint32_t oldValue;
	struct watchpoint *next;
} WP;

bool free_wp(int num);
int check_wp();
void show_wp();
WP* new_wp();

#endif
