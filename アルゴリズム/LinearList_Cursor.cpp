#include <stdio.h>
#include <stdlib.h>

#define Null -1

typedef int Index;

typedef struct {
	int no;           /*�ԍ�*/
	char name[20];    /*���O*/
}Member;

typedef struct{
	Member data;
	Index next;
	Index Dnext;
}Node;

typedef struct{
	Node *n;
	Index head;
	Index max;
	Index deleted;
	Index crnt;
}List;

void Initialize(List *list, int size);
void Print(const List *list);
void InsertRear(List *list, const Member *x);
void InsertAfter(List *list, Index idx, const Member *x);
void PrintMember(const Member *x);
static Index GetIndex(List *list);
static void SetNode(Node *n, const Member *x, Index next);

void Initialize(List *list, int size){
	list->n = (Node *)calloc(size, sizeof(Node));
	list->head = Null;
	list->crnt = Null;
	list->max = Null;
	list->deleted = Null;
}

void Print(const List *list){

	if (list->head == Null) {
		printf("�m�[�h������܂���ł���\n");
	}
	else {
		Index ptr = list->head;

		while (ptr != Null) {
			PrintMember(&list->n[ptr].data);
			ptr = list->n[ptr].next;
		}
	}
}

void InsertRear(List *list, const Member *x){
	if (list->head == Null){
		Index ptr = list->head;
		list->head = list->crnt = GetIndex(list);
		SetNode(&list->n[list->head], x, ptr);
	}
	else{
		Index ptr = list->head;
		while (list->n[ptr].next != Null){
			ptr = list->n[ptr].next;
		}
		list->n[ptr].next = list->crnt = GetIndex(list);
		SetNode(&list->n[list->n[ptr].next], x, Null);
	}
}

void InsertAfter(List *list, Index idx, const Member *x){
	Index New = GetIndex(list);

	list->n[New].next = list->n[idx].next;
	list->n[idx].next = New;

	SetNode(&list->n[list->n[idx].next], x, list->n[list->n[idx].next].next);
}

void PrintMember(const Member *x){
	printf("No%d�F	%s\n", x->no, x->name);
}

static Index GetIndex(List *list){
	if (list->deleted == Null){
		return ++(list->max);
	}
	else{
		Index rec = list->deleted;
		list->deleted = list->n[rec].Dnext;
		return rec;
	}
}

static void SetNode(Node *n, const Member *x, Index next){
	n->data = *x;
	n->next = next;
}

int main(void){
	int i = 0;
	int oper, number;
	List list;

	Initialize(&list, 500);

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
			Index p;
			p = list.head;
			printf("�w�肳�ꂽ�ʒu�̂P���Ƀm�[�h��}�����܂��F"); scanf("%d", &number);
			printf("�ԍ��F");    scanf("%d", &x.no);
			printf("���O�F");    scanf("%s", &x.name);

			if (list.head == Null) {
				printf("�m�[�h������܂���ł����B\n");
			}
			else{
				while (1){
					i++;
					if (i == number){
						InsertAfter(&list, p, &x);
						break;
					}
					if (list.n[p].next == Null){
						printf("\n�m�[�h���I�[�o�[���܂����B\n");
						break;
					}
					p = list.n[p].next;
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