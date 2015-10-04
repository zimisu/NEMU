#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args) {
	int steps = 1;
	char *arg = strtok(args, " ");
	if (arg == NULL) 
		steps = 1;
	else 
		sscanf(arg,"%d", &steps);
	cpu_exec(steps);
	return 0;
}
static int cmd_info(char *args) {
	char *arg;
	arg = strtok(args, " ");
	if (arg == NULL)
	{
		printf("Please input an arguments.\n");
		return 0;
	} else
	if (strcmp(arg, "r") == 0)
	{
		printf("register status:\n");
		int i;
		for (i = 0; i < 8; ++i)
			printf("  %s : 0x%x\n", regsl[i], cpu.gpr[i]._32);
		for (i = 0; i < 8; ++i)
			printf("  %s : 0x%x\n", regsw[i], cpu.gpr[i]._16);
		for (i = 0; i < 4; ++i)
		{
			printf("  %s : 0x%x\n", regsb[i*2], cpu.gpr[i]._8[0]);
			printf("  %s : 0x%x\n", regsb[i*2+1], cpu.gpr[i]._8[1]);
		}
	} else
	{
		printf("Arguments error.\n");
		return 0;
	}
	return 0;
}

int dram_read(hwaddr_t, size_t);
static int cmd_x(char *args)
{
	//int n = strtok(args, " ");
	//int addr = strtok(NULL, " ");
	int n, addr, i;
	sscanf(args, "%d%x", &n, &addr);
	for (i = 0; i < n; ++i)
	{
		//int content = dram_read(addr + 4*i, 4);
		printf("  %x  ",addr + 4*i);
		int j;
		for (j = 0; j < 4; ++j)
		{
			printf("  %x", hwaddr_read(addr + 4*i + j, 1));
		}
		printf("\n");
		//printf("  %x    0x%x\n", addr + i*4,dram_read(addr + i*4, 4));
	}
	printf("\n");
	return 0;
}

static int cmd_help(char *args);


static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Run with single step", cmd_si },
	{ "info", "Show the register info or watching points info", cmd_info },
	{ "x", "Scan the memory", cmd_x},
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
