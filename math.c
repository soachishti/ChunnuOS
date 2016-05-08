#include <system.h>
#define MAX_D 256
float math_stack[MAX_D];
int math_depth;
 
float math_pow(int a, int b) {
	float res = 1;
	for (int i = 0; i < b; i++) {
		res = res*a;
	}
	return res;
}

void math_push(float v)
{
	if (math_depth >= MAX_D) puts("math: stack overflow\n");
	math_stack[math_depth++] = v;
}
 
float math_pop()
{
	if (!math_depth) puts("math: stack underflow\n");
	return math_stack[--math_depth];
}

void math_binop(char op) {
	float b = math_pop();
	float a = math_pop();
	if (op == '-') math_push(a-b);
	else if (op == '+') math_push(a+b);
	else if (op == '*') math_push(a*b);
	else if (op == '/') {
		if (b == 0) 
			puts("math: division by zero.\n");
		else 
			math_push(a/b);
	}
	else if (op == '^') math_push(math_pow(a,b));	
}
 
int is_digit(char tmp) {
	return (tmp >= '0' && tmp <= '9');
}

float math_rpn(char *s)
{
	char prev = 0;
	float a = 1;
	math_depth = 0;
	int i; 	
	for (i = 0; i <  strlen(s); i++) {
		if (is_digit(s[i]))  {
			if (is_digit(prev)) {
				a = (a*10) + s[i]-48;
			}
			else {
				a = s[i]-48;	
			}
		}

		else if (s[i] == ' ')	{
			if (a >= 0) {
				math_push(a);
				//print_float(a);
			}
			a = -1;
		}
		else if (s[i] == 'a')	math_binop('+');
		else if (s[i] == 's')	math_binop('-');
		else if (s[i] == 't')	math_binop('*');
		else if (s[i] == 'd')	math_binop('/');
		else if (s[i] == 'r')	math_binop('^');
		else {
			puts("math: unknown operator\n");
		}
		prev = s[i];
	}
 
	if (math_depth != 1) puts("math: stack leftover\n");
 	return math_pop();
}