#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	int a, b;
	char op;
	char *q_s = getenv("QUERY_STRING");
	char *pc;
	sscanf(q_s, "a=%d&b=%d&op=%c", &a, &b, &op);
	if (op == '+') {
		printf("%d + %d = %d\n", a, b, a + b);
	} else if (op == '-') {
		printf("%d - %d = %d\n", a, b, a - b);
	} else if (op == '*') {
		printf("%d * %d = %d\n", a, b, a * b);
	} else if (op == '/') {
		printf("%d / %d = %d\n", a, b, a / b);
	} else
	return 0;
}
