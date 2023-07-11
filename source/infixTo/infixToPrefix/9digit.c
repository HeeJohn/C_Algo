/*
	name : º≠»Ò¡ÿ
	last_edit : 23.07.11
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_L 50 // max_length of expression
#define MAX_DIGIT 10 // max_length of digit
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MALLOC(p,s)\
	if(!((p)= malloc(s)))\
	{	fprintf(stderr,"Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

/*------struct & enum type definition--------*/
typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, operand, space
}precedence;

typedef struct node* stackPointer;
typedef struct node {
	double tk;
	stackPointer link;
}stackNode;

/*--global declaration--*/
stackPointer top = NULL; //operand
stackPointer oprTop = NULL; //operator
char expr[MAX_L];

/*----------------function---------------*/
precedence getToken(char* symbol, int* n);
char printToken(precedence t);
int changeToInt(); // atoi();
double eval();
void prefix();
precedence W_token();
void stackisEmpty();
void push(double t, stackPointer* top);
double pop(stackPointer* top);
void input(); // input
void overFlow(); // handling error
/*----------------function---------------*/

int main()
{
	input(); printf("\n>>infix expression : \"%s\"", expr); //input

	prefix(); printf("\n>>prefix expression : \"%s\"\n", expr); //prefix

	printf(">>carculated prefix expression..Result : %f\n\n", eval()); //result

	return 0;
}

/* -------------- input ------------- */

void input()
{
	char c = 0;
	int repeat ,count;
	count = repeat = 0;

	printf(">>Enter an infix expression that is a combination of integers(up to %d) => ", MAX_DIGIT);

	for ( ; count < MAX_L && c!='\n' ; count++) // repeat until MAX_L or '\n'typed.
	{
		c= getchar(); 
		if (c >= '0' && c <= '9') repeat++;
		else repeat = 0;

		if (repeat > MAX_DIGIT - 1) overFlow(); //error check 
		else expr[count] = c;
	}
	expr[count-1] = 0; // make string
}

void overFlow()
{
	fprintf(stderr, "Error, Max_digit is %d, but you put more than max", MAX_DIGIT - 1);
	exit(EXIT_FAILURE);
}

/* ---------------------------- pop & push ------------------------- */
void push(double t, stackPointer* top)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));

	temp->tk = t;

	if (*top)//stack created before.
	{
		temp->link = *top;
		*top = temp;
	}
	else//there was no stack created.
	{
		temp->link = NULL; // indicates it is the bottom node of the stack.
		*top = temp;
	}
}

double pop(stackPointer* top)
{
	stackPointer temp = *top;
	double token = 0.0;

	if (temp)
	{
		token = temp->tk;
		*top = temp->link;
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

/* ---------------------------covert infix to prefix ------------------------- */
void prefix()
{
	char symbol;
	precedence token;

	int i = strlen(expr) - 1; //reading index

	/* in-stack precedence(isp), incoming precedence(icp) */
	/* priority ==> lparen, rparen, plus, minus, times, divide, mod, eos */
	int isp[] = { 19,0,12,12,13,13,13,0 };
	int icp[] = { 19,20,12,12,13,13,13,0 };

	push(eos, &oprTop); //before any operator pushed in.
	
	for (token = getToken(&symbol, &i); i != -2; token = getToken(&symbol, &i))
	{
		if (token == operand)
			push(' ', &top);
		else if (token == lparen)
		{
			/*save tokens until left paren comes out, but not save lparen*/
			while ((token = pop(&oprTop)) != rparen)
			{
				push(printToken(token), &top);
				push(' ', &top);
			}
		}
		else
		{
			while (isp[(int)(oprTop->tk)] > icp[token])// check priority between operator
			{
				push(printToken(pop(&oprTop)), &top);
				push(' ', &top);
			}
			push(token, &oprTop);
		}
	}

	while ((token = pop(&oprTop)) != eos) // rest
	{
		push(printToken(token), &top);
		push(' ', &top);
	}

	int p;

	for (p = 0; top != NULL; p++) // make string.
		expr[p] = pop(&top);
	expr[p] = 0;
}

/* ---------------------------getToken & printToken ------------------------- */

precedence getToken(char* symbol, int* i)
{
	/*take the next token.
	symbol is a charactoer infix expression,
	token is represented by its enumerated value.*/

	*symbol = expr[(*i)--];

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
	case ' ': return space; break;
	default:
		if ((*symbol >= '0') && (*symbol <= '9')) //error check
		{
			for (; (*symbol >= '0') && (*symbol <= '9'); *symbol = expr[(*i)--])
				push(*symbol, &top);
			(*i)++;

			return operand;
		}
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
	default:printf("wrong token\n"); return 0;
	}
}

/* ------------- caculate the prefix expression (evaluate) ---------------- */
/*only insert operand until token is operator.*/
double eval()
{
	precedence token;
	char symbol;
	double op1, op2;
	int n = strlen(expr) - 1;

	for (token = getToken(&symbol, &n); n != -2; token = getToken(&symbol, &n))
	{
		if (token == space); // skip
		else if (token == operand)
			push(changeToInt(), &oprTop); // insert stack
		else
		{
			op1 = pop(&oprTop); // delete stack
			op2 = pop(&oprTop);
			switch (token)//token==operator
			{
			case plus: push(op1 + op2, &oprTop); break;
			case minus: push(op1 - op2, &oprTop); break;
			case times: push(op1 * op2, &oprTop); break;
			case divide: push(op1 / op2, &oprTop); break;
			case mod: push((int)op1 % (int)op2, &oprTop); break;
			}
		}
	}
	return pop(&oprTop); // return result;
}

int changeToInt()
{
	char degit[MAX_DIGIT];
	int i = 0;

	while (top != NULL)
		degit[i++] = (char)pop(&top);
	degit[i] = 0;

	return atoi(degit);
}
