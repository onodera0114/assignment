#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node* next;
} Node;

typedef struct {
	Node* head;
	Node* crnt;
} List;


typedef struct {
	int max;
	int num;
	List stk;
} Stack;

void Initialize(Stack* stack);
void push(Stack* stack, char x);
char pop(Stack* stack);
static Node* AllocNode(void);
static void SetNode(Node* n, char x, Node* next);
int Judg(char str, char oper);

void Initialize(Stack* stack) {
	stack->stk.head = NULL;
	stack->stk.crnt = NULL;
}

void push(Stack* stack, char x) {

	if (stack->stk.head == NULL) {
		Node* ptr = stack->stk.head;
		stack->stk.head = stack->stk.crnt = AllocNode();
		SetNode(stack->stk.crnt, x, NULL);
	}
	else {
		Node* ptr = AllocNode();
		stack->stk.crnt->next = ptr;
		stack->stk.crnt = ptr;
		SetNode(stack->stk.crnt, x, NULL);
	}
}

char pop(Stack* stack) {
	char s;
	if (stack->stk.head == NULL) {
		return -1;
	}
	else {
		Node* ptr = stack->stk.head;

		while (1) {
			if (ptr->next == NULL) {
				stack->stk.crnt = ptr;
				s = stack->stk.crnt->data;
				stack->stk.head = stack->stk.crnt = NULL;
				return s;
			}
			if (ptr->next->next == NULL) {
				stack->stk.crnt = ptr;
				s = stack->stk.crnt->next->data;
				stack->stk.crnt->next = NULL;
				return s;
			}
			ptr = ptr->next;
		}
		return 0;
	}
}

static Node* AllocNode(void) {
	return (Node*)calloc(1, sizeof(Node));
}

static void SetNode(Node* n, char x, Node* next) {
	n->data = x;
	n->next = next;
}

int Judg(char str, char oper) {
	switch (str){
	case '{':
		if (oper == '}')
			return 0;
		else
			return 1;
	case '(':
		if (oper == ')')
			return 0;
		else
			return 1;
	case '[':
		if (oper == ']')
			return 0;
		else
			return 1;
	}
}


int main(void) {
	int i, judg = 0;
	static char str;
	static char x[1000];
	Stack stack;

	Initialize(&stack);
	printf("•¶š—ñF");
	scanf("%s", &x);

	for (i = 0; i < strlen(x); i++) {
		switch (x[i]){
		case '{':
		case '(':
		case '[':
			push(&stack, x[i]);
			break;
		case '}':
			while (1) {
				str = pop(&stack);
				if (str == '{' || str == '(' || str == '[') {
					judg = Judg(str, '}');
					break;
				}
			}
			break;
		case ')':
			while (1) {
				str = pop(&stack);
				if (str == '{' || str == '(' || str == '[') {
					judg = Judg(str, ')');
					break;
				}
			}
			break;
		case ']':
			while (1) {
				str = pop(&stack);
				if (str == '{' || str == '(' || str == '[') {
					judg = Judg(str, ']');
					break;
				}
			}
			break;
		default:
			push(&stack, x[i]);
			break;

		}
		if (judg == 1) {
			printf("•s®‡\n");
			break;
		}
	}
	if (judg == 0){
		while (1){
			str = pop(&stack);
			if (str == '{' || str == '(' || str == '['){
				printf("•s®‡\n");
				break;
			}
			if (str == -1){
				printf("®‡\n");
				break;
			}
		}
		
	}
	return 0;
}
