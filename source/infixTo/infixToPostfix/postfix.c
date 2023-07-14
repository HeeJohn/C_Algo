/*
	program : postfix
	name : HuiJun Seo
	last_edit : 23.07.11
*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_L 10 // max_length of expression
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s)\
	if(!((p)= malloc(s)))\
	{	fprintf(stderr,"Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

/*------struct & enum type definition--------*/
typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, operand
}precedence;


typedef struct node* stackPointer;
typedef struct node {
	double tk;
	stackPointer link;
}stackNode;

/*--global declaration--*/
stackPointer top = NULL;
char expr[MAX_L];

/*----------------function---------------*/
precedence getToken(char* symbol, int* n);
char printToken(precedence t);
double eval();
void postfix();
precedence W_token();
void stackisEmpty();
void push(double t);
double pop();

/*----------------function---------------*/
int main()
{
	printf(">>Enter an infix expression that is a combination of single numbers => ");
	scanf("%s", expr);

	postfix();
	printf("\n\n>>postfix expression : \"%s\"\n", expr);

	puts(">>carculated postfix expression..");
	printf(">>Result : %f", eval());

	return 0;
}

/* ---------------------------- pop & push ------------------------- */
void push(double t)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));

	temp->tk = t;

	if (top)//stack created before.
	{
		temp->link = top;
		top = temp;
	}
	else//there was no stack created.
	{
		temp->link = NULL; // indicates it is the bottom node of the stack.
		top = temp;
	}
}

double pop()
{
	stackPointer temp = top;
	double token = 0.0;

	if (temp)
	{
		token = temp->tk;
		top = temp->link;
	}
	else
		stackisEmpty();

	free(temp);

	return token;
}

void stackisEmpty()
{
	fprintf(stderr, "\nstack is Empty!\n");
	exit(EXIT_FAILURE);
}

/* ---------------------------covert infix to postfix ------------------------- */
void postfix()
{
	char symbol;
	precedence token;
	int i = 0; //reading index
	int p = 0; //writing index

	/* in-stack precedence(isp), incoming precedence(icp) */
	/* priority ==> lparen, rparen, plus, minus, times, divide, mod, eos */
	int isp[] = { 0,19,12,12,13,13,13,0 };
	int icp[] = { 20,19,12,12,13,13,13,0 };

	push(eos); //before any token pushed in.

	for (token = getToken(&symbol, &i); token != eos; token = getToken(&symbol, &i))
	{
		if (token == operand)
			expr[p++] = symbol;
		else if (token == rparen)
		{
			/*save tokens until left paren comes out, but not save lparen*/
			while ((token = pop()) != lparen)
				expr[p++] = printToken(token);
		}
		else
		{
			while (isp[(int)top->tk] >= icp[token])// check priority between operator
				expr[p++] = printToken(pop());

			push(token);
		}
	}
	while ((token = pop()) != eos)
		expr[p++] = printToken(token);

	expr[p] = 0;//put eos at the end
}

/* ---------------------------getToken & printToken ------------------------- */

precedence getToken(char* symbol, int* i)
{
	/*take the next token.
	symbol is a charactoer infix expression,
	token is represented by its enumerated value.*/

	*symbol = expr[(*i)++];

	switch (*symbol)
	{
	case '(':return lparen; break;
	case ')': return rparen; break;
	case '+': return plus; break;
	case '-': return minus; break;
	case '/': return divide; break;
	case '*': return times; break;
	case '%': return mod; break;
	case '\0': return eos; break;
	default:
		if ((*symbol >= '0') && (*symbol <= '9')) //error check
			return operand;
		else
			return  W_token();
	}
}

precedence W_token()
{
	fprintf(stderr, "It is an inappropriate token");
	exit(EXIT_FAILURE);
}

char printToken(precedence t)
{
	/* reconvert enumerated value to character type */
	switch (t)
	{
	case lparen: return '('; break;
	case rparen: return ')'; break;
	case plus: return '+'; break;
	case minus: return '-'; break;
	case divide: return '/'; break;
	case times: return '*'; break;
	case mod: return '%'; break;
	case eos: return '\0'; break;
	default: return 0;
	}
}

/* ------------- caculate the postfix expression (evaluate) ---------------- */
/*only insert operand until token is operator.*/
double eval()
{
	precedence token;
	char symbol;
	double op1, op2;
	int n = 0;

	token = getToken(&symbol, &n);

	while (token != eos)
	{
		if (token == operand)
			push((double)symbol - '0'); // insert stack
		else
		{
			op2 = pop(); // delete stack
			op1 = pop();
			switch (token)//token==operator
			{
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push((int)op1 % (int)op2); break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop(); // return result;
}


