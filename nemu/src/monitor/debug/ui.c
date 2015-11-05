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

static int cmd_w(char *args) {
	char* tmp = strtok(args, " ");
	if (tmp == NULL)
	{
		printf("Please input the right argument.\n");
		return -1;
	}

	WP* wp = new_wp();
	if (wp == NULL)
	{
		printf("Add watch points failed.\n");
		return -1;
	}

	wp->expr = tmp;
	bool success = true;
	wp->oldValue = expr(tmp, &success);
	if (success == false)
	{
		printf("Calculate the expression failed.\n");
		return -1;
	}
	
	return 0;
}

static int cmd_d(char *args) {
	char *tmp = strtok(args, " ");
	int wpnum = -1;
	if (sscanf(tmp, "%d", &wpnum) == 0)
	{
		printf("Please input the right argument.\n");
		return -1;
	}
	//find the watch point and delete it
	if (delete_wp_num(wpnum) == 0) return -1;
	return 0;
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
			printf("  %s : 0x%08x\n", regsl[i], cpu.gpr[i]._32);
		for (i = 0; i < 8; ++i)
			printf("  %s : 0x%04x\n", regsw[i], cpu.gpr[i]._16);
		for (i = 0; i < 4; ++i)
		{
			printf("  %s : 0x%02x\n", regsb[i], cpu.gpr[i]._8[0]);
			printf("  %s : 0x%02x\n", regsb[i+4], cpu.gpr[i]._8[1]);
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
	//printf("%s\n", args);
	int n, addr, i;
	sscanf(args, "%d", &n);
	if (n == 0)
	{
		printf("Please input the right arguments.\n");
		return 0;
	}
	while (*args == ' ') ++args;
	while (*args >= '0' && *args <= '9') ++args;
	bool success = true;
	addr = expr(args, &success);//调用表达式求值
	if (success == false) 
	{
		//表达式非法，无法求值
		printf("Please input the right arguments.\n");
		return 0;
	}

	//printf("%d\n", addr);
	printf("start:[0x%08x]\n", addr);
	for (i = 0; i < n; ++i)
	{
		printf("  0x%08x  ",addr + 4*i);
		int j;
		for (j = 0; j < 4; ++j)
			printf("  %02x", hwaddr_read(addr + 4*i + j, 1));
		printf("\n");
	}
	printf("\n");
	return 0;
}
static int cmd_p(char *args)
{
	if (args == NULL) 
	{
		printf("Please input the argument.\n");
		return 0;
	}
	bool success = true;
	uint32_t result = expr(args, &success);
	if (success == false) 
	{
		printf("Expression invalid.\n");
		return 0;
	}
	printf("  %d    :    0x%x\n", result, result);
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
	{ "i", "Show the register info or watching points info", cmd_info},
	{ "x", "Scan the memory", cmd_x},
	{ "p", "Expression calculation", cmd_p},
	{ "w", "Add watch point", cmd_w},
	{ "d", "Delete a watch point", cmd_d}
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
