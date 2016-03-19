#include <stdio.h>
#include <string.h>
#include "trap.h"

char buf[128];

/* This function is defined only to make the newlibc linkable.
 * Without it, errors will be reported during linking.
 * But the execution flow should not reach here.
 */
void *sbrk(int incr) {
	nemu_assert(0);
	return NULL;
}

int main() {
//set_bp();
	sprintf(buf, "%s", "Hello world!\n");
//set_bp();
	int res = strcmp("1", "1");
//set_bp();
	nemu_assert(res == 0);
set_bp();
	sprintf(buf, "%d + %d = %d\n", 1, 1, 2);
	nemu_assert(strcmp(buf, "1 + 1 = 2\n") == 0);
//set_bp();

	sprintf(buf, "%d + %d = %d\n", 2, 10, 12);
	nemu_assert(strcmp(buf, "2 + 10 = 12\n") == 0);
//set_bp();

	HIT_GOOD_TRAP;
	return 0;
}
