#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, DEC_NUM, HEX_NUM, NEQ, AND, OR

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"0x\\d+", HEX_NUM},			// hexadecimal number
	{"\\d+", DEC_NUM},				// decimal number
	{"!=", NEQ},					// not equal
	{"&&", AND},					// and
	{"||", OR},						// or
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"-", '-'},						// sub
	{"\\*", '*'},					// mul or dereference
	{"/", '/'}						// div
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret != 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;


static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case NOTYPE:
						break;
					
					default: 
						tokens[nr_token].type = rules[i].token_type;
						int j;
						for (j = 0; j < substr_len; j++)
							tokens[nr_token].str[j] = substr_start[j];
						++nr_token;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int p, int q, bool *success) {
	if (tokens[p].type != '(' || tokens[q].type != ')') {
		//左右不为括号
		*success = false;
		return false;
	}
	int count = 0, i;
	for (i = p; i <= q; i++)
		if (tokens[i].type == '(')
			++count; 
		else if (tokens[i].type == ')')
		{
			-- count;
			if (count < 0)
			{
				*success = false;
				return 0;
			}
			if (count == 0 && i != q)
			{
				return false;
			}
		}
	if (count != 0)
	{
		// '('数量不等于  ')'数量
		*success = false;
		return false;
	}
	return 1;
}

uint32_t eval(int p, int q, bool *success)
{
	if (p > q)
	{
		*success = false;
		return 0;
	}
	if (p == q)
	{
		uint32_t tmp = 0;
		int i;
		for (i = 0; i < strlen(tokens[p].str); i++)
			tmp = tmp*10 + tokens[p].str[i] - '0';
		return tmp;
	}
	else if (check_parentheses(p, q, success) == true)
	{
		return eval(p+1, q-1, success);
	}
	else 
	{
		//int maxPiority = -1;
		
	}
	if (*success == false) return 0;
	return 0;
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	
	/* TODO: Insert codes to evaluate the expression. */

	panic("please implement me");
	return 0;
}

