#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int no;           /*番号*/
	char name[20];    /*名前*/
}Member;

typedef struct __node{
	Member data;
	struct __node *next;
}Node;

typedef struct {
	Node *head;
	Node *crnt;
}List;

void Initialize(List *list);
void Print(const List *list);
void InsertRear(List *list, const Member *x);
void InsertAfter(List *list, Node *p, const Member *x);
void PrintMember(const Member *x);
static Node *AllocNode(void);
static void SetNode(Node *n, const Member *x, Node *next);

void Initialize(List *list) {
	list->head = NULL;
	list->crnt = NULL;
}

void Print(const List *list) {
	if (list->head == NULL) {
		printf("\n");
	}
	else {
		Node *ptr = list->head;

		while (ptr != NULL) {
			PrintMember(&ptr->data);
			ptr = ptr->next;
		}
	}
}

void PrintMember(const Member *x){
	printf("No%d：	%s\n", x->no, x->name);
}

void InsertRear(List *list, const Member *x) {
	if (list->head == NULL) {
		Node *ptr = list->head;
		list->head = list->crnt = AllocNode();
		SetNode(list->head, x, ptr);
	}

	else {
		Node *ptr = list->head;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next, x, NULL);
	}
}

void InsertAfter(List *list, Node *p, const Member *x) {
	Node *n = AllocNode();

	n->next = p->next;
	p->next = n;

	SetNode(p->next, x, p->next->next);
}

static Node* AllocNode(void) {
	return (Node *)calloc(1, sizeof(Node));
}

static void SetNode(Node *n, const Member *x, Node *next) {
	n->data = *x;
	n->next = next;
}

int main(void) {
	int oper, number, i = 0;
	List list;

	Initialize(&list);

	do {
		Member x;
		printf("　[処理内容]\n");
		printf("　1:末尾にノードを追加\n　2:指定位置にノードを挿入\n　3:リストの表示\n\n処理内容：");
		scanf("%d", &oper);
		printf("\n");
		switch (oper)
		{
		case 1:
			printf("番号：");    scanf("%d", &x.no);
			printf("名前：");    scanf("%s", &x.name);
			InsertRear(&list, &x);
			printf("\n");
			break;
		case 2:
			Node *p; 
			p = list.head;
			printf("指定された位置の１つ後ろにノードを挿入します："); scanf("%d", &number);
			printf("番号：");    scanf("%d", &x.no);
			printf("名前：");    scanf("%s", &x.name);

			if (list.head == NULL) {
				printf("ノードがありませんでした。\n");
			}
			else{
				while (1){
					i++;
					if (i == number){
						InsertAfter(&list, p, &x);
						break;
					}
					if (p->next == NULL){
						printf("\nノードがオーバーしました。\n");
						break;
					}
					p = p->next;
				}
				i = 0;
			}
			printf("\n");
			break;
		case 3:
			Print(&list);
			printf("\n");
			break;
		}
	} while (oper >= 1 && oper <= 3);

	return 0;
}