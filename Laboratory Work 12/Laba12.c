#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node 
{
	char word[20];
	struct Node* next, * prev;
} Node;

typedef struct List 
{
	int size;
	Node* head, * tail;
}List;

List* initialization() 
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->tail = NULL;
	tmp->head = tmp->tail;
	return tmp;
}

void pushBack(List* list, char* word) 
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) 
	{
		exit(1);
	}
	strcpy(tmp->word, word);
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail != NULL) 
	{
		list->tail->next = tmp;
	}
	list->tail = tmp;
	if (list->head == NULL) 
	{
		list->head = tmp;
	}
	list->size++;
}

void deletelist(List** list) 
{
	Node* tmp = (*list)->head;
	Node* next = NULL;
	while (tmp) 
	{
		next = tmp->next;
		tmp->prev = NULL;//������� ����� � ���������� ���������
		tmp->next = NULL;//������� ����� �� ��������� ���������
		free(tmp);//����������� �������
		tmp = next;//��� �����
	}
	(*list)->head = NULL;//������� ������ ������
	(*list)->tail = NULL;//������� ����� ������
	free(*list);//����������� ������
	(*list) = NULL;
}

void create(List** list) 
{
	char str[200], * w, * p;
	printf("Enter string:\n");
	gets(str);
	p = strstr(str, ".");
	w = strtok(str, " ");
	while (w != NULL && p > w) 
	{
		pushBack(*list, w);
		w = strtok(NULL, " .");
	}
}

void display(List* lst) 
{
	Node* tmp = lst->head;
	while (tmp != NULL)
	{
		printf("%s ", tmp->word);
		tmp = tmp->next;
	}
}

List* task(List* lst)
{
	int j = 0, index = 0;
	if (lst == NULL)
	{
		printf("There is no data in the node.\n");
		return(NULL);
	}
	char str1[20] = { NULL }, str[20] = { NULL };
	Node* p = lst->head, *pp = NULL;
	Node* newNode = (Node*)malloc(sizeof(Node));
	while (p)
	{
		if (strlen(str1) < (strlen(p->word)))//���������� �����
		{
			strcpy(str1, p->word);//���� ����� ����� ��������� �������, ���������� ���
			pp = p;//���������� ���������� �� �����
		}
		p = p->next;//��� �����
	}

	printf("\n");
	for (int i = strlen(str1) - 1; i != -1; i--)//����������� ����� ������� �����
	{
		str[j] = str1[i];
		printf("%c", str[j]);
		j++;
	}
	lst->size++;
	if (!pp->next) pushBack(lst, strcpy(newNode, str));//���� ����� ������� ������� ���������, ��������� � �����
	else
	{
		p = pp->next;
		strcpy(newNode->word, str);//������ ����� � ����� ���� ������
		newNode->next = p;//������������ ������ ��� ������������ ����
		newNode->prev = pp;
		pp->next = newNode;
		p->prev = newNode;
	}
	return lst;
}

void reversedisplay(List* lst) //������� ������ � �������� ������� ��� �������� �� ������ ������ ����� ����������
{
	Node* tmp = lst->tail;
	while (tmp != NULL) 
	{
		printf("%s ", tmp->word);
		tmp = tmp->prev;
	}
}

int main(void) 
{
	List* lst;
	lst = initialization();
	create(&lst);
	if (lst->size == 0)//���� ������ ����
	{
		printf("List is empty.\n");
		exit(-3);
	}
	printf("Initial list:\n");
	display(lst);
	lst = task(lst);
	printf("\n\n");
	display(lst);
	printf("\n\nReverse displaying:\n");
	reversedisplay(lst);
	printf("\n\n");
	deletelist(&lst);//������� ������
	return 0;
}