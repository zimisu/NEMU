#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, DEC_NUM, HEX_NUM, NEQ, AND, OR, MINUS, DER

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
	{"0x[0-9]+", HEX_NUM},			// hexadecimal number
	{"[0-9]+", DEC_NUM},				// decimal number
	{"!=", NEQ},					// not equal
	{"&&", AND},					// and
	{"\\|\\|", OR},						// or
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"-", '-'},						// sub
	{"\\*", '*'},					// mul or dereference
	{"/", '/'},						// div
	{"(", '('},						// (
	{")", ')'},						// )
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

#define NOP 10 //不是一个有效操作符

int getPriority(int type)
{
	switch (type){
		case MINUS: return 7;
		case DER: return 7;
		case '*': return 6;
		case '/': return 6;
		case '+': return 5;
		case '-': return 5;
		case AND: return 4;
		case OR: return 3;
		case EQ: return 2;
		case NEQ: return 2;
	}
	return NOP;// 不是一个有效操作符
}
/*
bool isCertainToken(int type)
{
	switch type:
		
}
*/
uint32_t eval(int p, int q, bool *success)
{
	printf("-------%d\n", *success);
	if (p > q)
	{
			printf("fuck----\n");
		*success = false;
		return 0;
	}
	if (p == q)
	{
		uint32_t tmp = 0, i;
		if (tokens[p].type == DEC_NUM)
		{
			for (i = 0; i < strlen(tokens[p].str); i++)
				tmp = tmp*10 + tokens[p].str[i] - '0';
			//printf("this is DEC_NUM   %d\n");
		} else 
		if (tokens[p].type == HEX_NUM)
		{
			for (i = 2; i < strlen(tokens[p].str); i++)
				tmp = tmp*16 + tokens[p].str[i] - '0';
		} else
		{
			printf("fuck----\n");
			*success = false;
			return 0;
		}
		return tmp;
	}
	else if (check_parentheses(p, q, success) == true)
	{
		//printf("fuck-----\n");
		return eval(p+1, q-1, success);
	}
	else 
	{
		if (*success == false) return 0;
		int minPriority = NOP;
		int i;
		int countp = 0;//count parentheses
		//查找op操作符
		for (i = p; i <= q; i++){
			int type = tokens[i].type;
			if (type == '(') ++countp;
			else if (type == ')') -- countp;//op操作符不能在括号内
			if (getPriority(type)<minPriority && countp==0)
				minPriority = getPriority(type);
		}
		if (minPriority == NOP) //未找到op操作符
		{
			*success = false;
			return 0;
		}
		countp = 0;
		for (i = q; i >= p; i--) {
			int type = tokens[i].type;
			if (type == '(') ++ countp;
			else if (type == ')') --countp;
			if (getPriority(type) == minPriority && countp==0)
			{
				if (type == DER)//为单目 解引用×
				{
					uint32_t addr = eval(p+1, q, success);
					if (*success == false) return 0;
					return hwaddr_read(addr, 4);
				} else
				if (type == MINUS)//为单目 负号-
				{
					uint32_t val = eval(p+1, q, success);
					if (*success == false) return 0;
					return -val;
				}
				printf("%d\n", *success);
				uint32_t val1 = eval(p, i-1, success);
				printf("%d\n", *success);

				if (*success == false) return 0;
				printf("this is switch %d %d %d\n", p, i , q);
				uint32_t val2 = eval(i+1, q, success);

				if (*success == false) return 0;
				printf("this is switch %d %d %d\n", p, i , q);
				switch (type){
					case '+': return val1 + val2;
					case '-': return val1 - val2;
					case '*': return val1 * val2;
					case '/': return val1 / val2;
					case AND: return val1 && val2;
					case OR:  return val1 || val2;
					case EQ:  return val1 == val2;
					case NEQ: return val1 != val2;
					default : assert(0);
				}

				break;
			}
		}
		

		//for (i = q; i >= p; i--)
		//	if (getPriority(tokens[i].type) == maxPriority)
	}
	return 0;
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	
	int i;
	for (i = 0; i < nr_token; i++)
	{
		if (tokens[i].type == '*' && (i==0 || getPriority(tokens[i-1].type)<NOP))
			//为解引用
			tokens[i].type = DER;
		else
		if (tokens[i].type == '-' && (i==0 || getPriority(tokens[i-1].type)<NOP))
			tokens[i].type = MINUS;
	}

	return eval(0, nr_token-1, success);
	

	panic("please implement me");
	return 0;
}

