#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node* next;
} Node;

typedef struct {
	Node *head;
	Node *crnt;
} List;


typedef struct {
	int max;
	int num;
	List stk;
} Stack;

void Initialize(Stack *stack);
void push(Stack *stack, char x);
void pop(Stack *stack);
static Node* AllocNode(void);
static void SetNode(Node *n, char x, Node *next);
void Print(const Stack *stack);


void Initialize(Stack *stack) {
	stack->stk.head = NULL;
	stack->stk.crnt = NULL;
}

void push(Stack *stack, char x) {

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

void pop(Stack *stack) {
	if (stack->stk.head == NULL) {
		printf("\nアンダーフローしました。\n");
	}
	else {
		Node* ptr = stack->stk.head;

		while (1) {
			if (ptr->next == NULL) {
				stack->stk.crnt = ptr;
				printf("\n");
				printf("popしたデータ：%s\n", &stack->stk.crnt->data);
				stack->stk.head = stack->stk.crnt = NULL;
				break;
			}
			if (ptr->next->next == NULL) {
				stack->stk.crnt = ptr;
				printf("\n");
				printf("popしたデータ：%s\n", &stack->stk.crnt->next->data);
				stack->stk.crnt->next = NULL;
				break;
			}
			ptr = ptr->next;
		}
	}
}

static Node* AllocNode(void) {
	return (Node*)calloc(1, sizeof(Node));
}

static void SetNode(Node* n, char x, Node* next) {
	n->data = x;
	n->next = next;
}

void Print(const Stack *stack) {
	if (stack->stk.head == NULL) {
		printf("データがありません\n");
	}
	else {
		Node* ptr = stack->stk.head;

		while (ptr != NULL) {
			printf("%s　", &ptr->data);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

int main(void) {
	int oper;
	static char x;
	Stack stack;

	Initialize(&stack);

	do {
		printf("1:push　　2:pop　　3:表示　　それ以外：終了\n処理内容:");
		scanf("%d", &oper);

		switch (oper) {
		case 1:
			printf("\n");
			printf("pushするデータ：");
			scanf("%s", &x);
			push(&stack, x);
			printf("\n");
			break;
		case 2:
			pop(&stack);
			printf("\n");
			break;
		case 3:
			printf("\n");
			Print(&stack);
			printf("\n");
			break;
		default:
			break;
		}
	} while (oper >= 1 && oper <= 3);
	return 0;
}
