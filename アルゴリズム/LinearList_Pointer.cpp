#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int no;           /*�ԍ�*/
	char name[20];    /*���O*/
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
	printf("No%d�F	%s\n", x->no, x->name);
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
		printf("�@[�������e]\n");
		printf("�@1:�����Ƀm�[�h��ǉ�\n�@2:�w��ʒu�Ƀm�[�h��}��\n�@3:���X�g�̕\��\n\n�������e�F");
		scanf("%d", &oper);
		printf("\n");
		switch (oper)
		{
		case 1:
			printf("�ԍ��F");    scanf("%d", &x.no);
			printf("���O�F");    scanf("%s", &x.name);
			InsertRear(&list, &x);
			printf("\n");
			break;
		case 2:
			Node *p; 
			p = list.head;
			printf("�w�肳�ꂽ�ʒu�̂P���Ƀm�[�h��}�����܂��F"); scanf("%d", &number);
			printf("�ԍ��F");    scanf("%d", &x.no);
			printf("���O�F");    scanf("%s", &x.name);

			if (list.head == NULL) {
				printf("�m�[�h������܂���ł����B\n");
			}
			else{
				while (1){
					i++;
					if (i == number){
						InsertAfter(&list, p, &x);
						break;
					}
					if (p->next == NULL){
						printf("\n�m�[�h���I�[�o�[���܂����B\n");
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