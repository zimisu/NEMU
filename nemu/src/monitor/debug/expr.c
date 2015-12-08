#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <elf.h>

extern Elf32_Sym *symtab;
extern int nr_symtab_entry;
extern char* strtab;

enum {
	NOTYPE = 256, EQ, DEC_NUM, HEX_NUM, NEQ, AND, 
		OR, MINUS, DER, REG, NOT, BITAND, BITOR, BITXOR, VAR
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
	{"0x[0-9a-f]+", HEX_NUM},			// hexadecimal number
	{"[0-9]+", DEC_NUM},			// decimal number
	{"!=", NEQ},					// not equal
	{"&&", AND},					// and
	{"\\|\\|", OR},					// or
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"-", '-'},						// sub
	{"\\*", '*'},					// mul or dereference
	{"/", '/'},						// div
	{"\\(", '('},					// (
	{"\\)", ')'},					// )
	{"\\$[a-z]{2,3}", REG},			// register
	{"&", BITAND},					// bit and
	{"\\|", BITOR},					// bit or
	{"\\^", BITXOR},				// bit xor
	{"!", NOT},						// not
	{"[a-zA-Z_][a-zA-Z_0-9]*", VAR}	// variable
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
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
///////////////////////////////
	printf("~~~%s\n", strtab);
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

				//Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
			 		case NOTYPE:
						break;//空格，什麼也不做
					default: 
					 	//将type写入tokens
						tokens[nr_token].type = rules[i].token_type;
						int j;
						//复制字符串
						for (j = 0; j < substr_len; j++)
							tokens[nr_token].str[j] = substr_start[j];
						tokens[nr_token].str[substr_len] = '\0';
						//tokens数量增加
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
	if (tokens[p].type != '(' || tokens[q].type != ')') 
		//左右不为括号
		return false;

	int count = 0, i;
	for (i = p; i <= q; i++)
		//每次出现 ( count加1，出现 ) count减1，若出现负数则括号不匹配
		if (tokens[i].type == '(') ++count; 
		else if (tokens[i].type == ')')
		{
			-- count;
			if (count < 0)// ‘)' 比 '(' 数量多，非法表达式
			{
				*success =   false;
				return false;
			}
			//括号提前匹配完成
			if (count == 0 && i != q)  return false;
		}
	if (count != 0)
	{
		// '('数量不等于  ')'数量
		*success = false;
		return false;
	}
	return 1;
}

#define NOP 10 //不是一个有效操作符的优先级

int getPriority(int type)
{
	switch (type){
		case MINUS: return 7;   // 负号
		case DER:	return 7;   // 解引用
		case NOT:	return 7;	// !	
		case '*':	return 6;	
		case '/':	return 6;
		case '+':	return 5;
		case '-':	return 5;
		case BITAND:return 4;
		case BITOR:	return 3;
		case BITXOR:return 4;
		case AND:	return 2;
		case OR:	return 1;
		case EQ:	return 0;	// ==
		case NEQ:	return 0;	// !=
	}
	return NOP;// 不是一个有效操作符
}
/*
bool isCertainToken(int type)
{
	switch type:
		
}
*/

bool nameCmp(char* s1, uint32_t size1, char* s2, uint32_t size2)
{
	uint32_t i;
	printf("-----nameCmp-----\n");
	printf("%u  %u\n",size1, size2);
	if (size1 != size2) return 0;
	for (i = 0; i < size1; i++) printf("%c",s1[i]);
	printf("\n");
	for (i = 0; i < size2; i++) printf("%c", s2[i]);
	printf("\n");
	for (i = 0; i < size1; i++)
		if (s1[i] != s2[i])
			return 0;
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
		uint32_t tmp = 0, i;
		if (tokens[p].type == HEX_NUM)//十六进制数
		{
			for (i = 2; i < strlen(tokens[p].str); i++)
			{
				int num;
				char c = tokens[p].str[i];
				if (c >= 'a' && c <= 'f') num = c - 'a' + 10;
				else num = c - '0';
				tmp = tmp*16 + num;
			}
		} else 
		if (tokens[p].type == DEC_NUM)//十进制数
		{
			for (i = 0; i < strlen(tokens[p].str); i++)
				tmp = tmp*10 + tokens[p].str[i] - '0';
		} else
		if (tokens[p].type == VAR)  //变量
		{
			tmp = 0;
			for (i = 0; i < nr_symtab_entry; i++)
				if (nameCmp(tokens[p].str, strlen(tokens[p].str),
							symtab[i].st_name + strtab, symtab[i].st_size))
				{
					tmp = symtab[i].st_value;
					break;
				}
			if (tmp == 0) {
				*success = 0;
				return 0;
			}
		} else
		if (tokens[p].type == REG)//寄存器
		{
			int j;
			for (j = 0; j < 8; j++)
			{
				if (strcmp(regsl[j] , tokens[p].str+1)==0) return cpu.gpr[j]._32;
				if (strcmp(regsw[j], tokens[p].str+1)==0) return cpu.gpr[j]._16;
			}
			for (j = 0; j < 4; j++)
			{
				if (strcmp(regsb[j ], tokens[p].str+1)==0)  return cpu.gpr[j]._8[0];
				if (strcmp(regsb[j+4], tokens[p].str+1)==0) return cpu.gpr[j]._8[1];
			}
			if (strcmp("$eip", tokens[p].str) == 0) return cpu.eip;
			printf("Invalid register.\n");
			*success = false;
			return 0;
		} else
		{
			*success = false;
			return 0;
		}
		return tmp;
	}
	else if (check_parentheses(p, q, success) == true)
		return eval(p+1, q-1, success);//取出括号继续递归
	else 
	{
		if (*success == false) return 0;//检查括号匹配时是否返回不合法
		int minPriority = NOP;//默认优先级，即为非法操作符的优先级
		int i;
		int countp = 0;//count parentheses括号计数，'('加1，')'减1
		//查找op操作符
		for (i = p; i <= q; i++){
			int type = tokens[i].type;
			if (type == '(') ++countp;
			else if (type == ')') -- countp;
			//查找所有操作符中最低的优先级
			if (getPriority(type)<minPriority && countp==0) //op操作符不能在括号内
				minPriority = getPriority(type);
		}
		if (minPriority == NOP) //未找到op操作符
		{
			*success = false;
			return 0;
		}
		countp = 0;
		//从右往左查找优先级等于minPriority的操作符，作为op
		for (i = q; i >= p; i--) {
			int type = tokens[i].type;
			if (type == '(') ++ countp;
			else if (type == ')') --countp;
			if (getPriority(type) == minPriority && countp==0)
			{
			 	if (type == DER)// 为单目dereference 解引用*
				{
			 		uint32_t addr = eval(p+1 , q, success);
					return hwaddr_read(addr, 4);
				} else
				if (type == MINUS)//为单目 负号-
			 		return  -eval(p+1, q, success);
				else
				if (type == NOT) //为单目 !
				 	return !eval(p+1, q, success);

				uint32_t val1 = eval(p, i-1, success);
				uint32_t val2 = eval(i+1, q, success);

				if (*success == false) return 0;

				switch (type){//为双目运算符
					case '+':		return val1 + val2;
					case '-':		return val1 - val2;
					case '*':		return val1 * val2;
					case '/':
						if (val2 == 0) { 
							*success = false; 
							return 0;
						}
						return val1 / val2;
					case AND:		return val1 && val2;
					case OR:		return val1 || val2;
					case EQ:		return val1 == val2;
					case NEQ:		return val1 != val2;
					case BITOR:		return val1 | val2;
					case BITAND:	return val1 & val2;
					case BITXOR:	return val1 ^ val2;

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
	//判断* - 是否解引用或负号
	for (i = 0; i < nr_token; i++)
	{
		if (tokens[i].type == '*' && (i==0 || getPriority(tokens[i-1].type)<NOP || tokens[i-1].type == '('))
			//前一个操作符拥有优先级，为解引用
			tokens[i].type = DER;
		else
			//同上。为负号
		if (tokens[i].type == '-' && (i==0 || getPriority(tokens[i-1].type)<NOP || tokens[i-1].type == '('))
			tokens[i].type = MINUS;
	}
	return eval(0, nr_token-1, success);
	

	panic("please implement me");
	return 0;
}

