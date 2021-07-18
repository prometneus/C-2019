#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define N 200

typedef struct Tree
{
	char word[20];
	int occurence;//������� ������������� �����
	struct Tree* left, * right, * parent;//��������� ��� ������
	struct Tree* next, * prev;//��������� ��� ����������� ������
}Tree;

typedef struct List 
{
	int size;
	Tree* head, * tail;
}List;

Tree* makeNode(char* word, Tree* parent)//���� ������
{
	Tree* tmp = (Tree*)malloc(sizeof(Tree));
	tmp->left = NULL;
	tmp->right = NULL;
	strcpy(tmp->word, word);
	tmp->parent = parent;
	tmp->occurence = 1;
	return tmp;
}

void AddTreeNode(Tree** root, char* word)
{
	Tree* tmp = NULL;
	if (*root == NULL)//���� ������ ������, ����� ������� ����� � ��������� ������ ����� � ������
	{
		*root = makeNode(word, NULL);
		return;
	}
	tmp = *root;
	while (tmp) 
	{
		if (strcmp(word, tmp->word) > 0)//���� ����� �������, ���� ������
		{
			if (tmp->right) 
			{
				tmp = tmp->right;//���� ��� ���� ���� ������, ���� ������
				continue;
			}
			else //����� �� ������� �����, ��������� ����� ���� 
			{
				tmp->right = makeNode(word, tmp);
				return;
			}
		}
		else if (strcmp(word, tmp->word) < 0) //���� ����� ������, ���� �����
		{
			if (tmp->left) 
			{
				tmp = tmp->left;
				continue;
			}
			else 
			{
				tmp->left = makeNode(word, tmp);
				return;
			}
		}
		else if(strcmp(word, tmp->word) == 0) 
		{
			tmp->occurence++;
			return;
		}
	}
}

void StraightDeep(Tree* root)//������ ����� ������ � �������
{
	if (root) 
	{
		printf("%s(%d)\n", root->word, root->occurence);//����� �������� ����� �� �����
		StraightDeep(root->left);//����������� ����� ��� ������ ���������
		StraightDeep(root->right);//����������� ����� ��� ������� ���������
	}
}

void SymmetricDeep(Tree* root)//������������ ����� ������ � �������
{
	if (root) 
	{
		SymmetricDeep(root->left);
		printf("%s(%d)\n", root->word, root->occurence);
		SymmetricDeep(root->right);
	}
}

void ReverseDeep(Tree* root)//�������� ����� ������ � �������
{
	if (root) 
	{
		ReverseDeep(root->left);
		ReverseDeep(root->right);
		printf("%s(%d)\n", root->word, root->occurence);
	}
}

List* makeStack() 
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	return tmp;
}

List* pushBack(List* list, Tree* thing) 
{
	Tree* tmp = (Tree*)malloc(sizeof(Tree));
	tmp->parent = thing->parent;
	tmp->left = thing->left;
	tmp->right = thing->right;
	tmp->occurence = thing->occurence;
	strcpy(tmp->word, thing->word);
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) 
	{
		list->tail->next = tmp;
	}
	list->tail = tmp;
	if (!list->head) 
	{
		list->head = tmp;
	}
	list->size++;
}

Tree* Stack(List* list) 
{
	Tree *elem;
	if (list->head == NULL) return NULL;
	elem = list->head;//���������� ������
	list->head = list->head->next;//������� ����� ������
	if (list->head) list->head->prev = NULL;//�������� ����� ����� ������ � ����� ��������
	if (elem == list->tail) list->tail = NULL;//���� ������� ��� ��������� - ���������� �� ������
	list->size--;
	return elem;
}

void deleteStack(List** list) 
{
	Tree* tmp = (*list)->head, * next;
	while (tmp) 
	{
		next = tmp->next;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = next;
	}
	(*list)->head = NULL;
	(*list)->tail = NULL;
	free(*list);
	(*list) = NULL;
}

void Width(Tree *root) 
{
	List *list = makeStack();//������� ���������� ������ ��� �����
	pushBack(list, root);
	while (list->size != 0) 
	{
		Tree *tmp = (Tree*)Stack(list);//�������� 1 ������� �� ������
		if (tmp) 
		{
			printf("%s(%d)\n", tmp->word, tmp->occurence);
			if (tmp->left) pushBack(list, tmp->left);
			if (tmp->right) pushBack(list, tmp->right);
		}
	}
	deleteStack(&list);
}

int check(char* word)
{
	if (word && strlen(word) > 20)
	{
		printf("Error in word \"%s\".\n", word);
		return 1;
	}
	return 0;
}

int DeepDeep(Tree* root) 
{
	if (!root) return -5;
	if (!root->left && !root->right) return 0;
	int links, rechts;
	links = DeepDeep(root->left);
	rechts = DeepDeep(root->right);
	return (links > rechts) ? links + 1 : rechts + 1;
}

void DesTree(Tree** root) 
{
	if (*root) 
	{
		DesTree(&((*root)->left));
		DesTree(&((*root)->right));
		free(*root);
	}
}

int main(void) 
{
	Tree* root = NULL;
	FILE* f = fopen("tree.txt", "r+");
	char str[N], *words;
	int deep = 0;
	if (!f) 
	{
		printf("Error in opening file.\n");
		return -1;
	}
	if (!fgets(str, N, f)) 
	{
		printf("File is empty.\n");
		return -2;
	}
	words = strtok(str, " ");
	fclose(f);
	if (check(words) == 1) return -3;
	while (words) 
	{
		AddTreeNode(&root, words);
		words = strtok(NULL, " ");
		if (check(words) == 1) return -4;
	}
	printf("Straight Deep\n");
	StraightDeep(root);

	printf("\n\nSymmetric Deep\n");
	SymmetricDeep(root);

	printf("\n\nReverse Deep\n");
	ReverseDeep(root);

	printf("\n\nWidth\n");
	Width(root);

	deep = DeepDeep(root);
	printf("\nDeep = %d", deep);

	printf("\n\n\n\n");
	DesTree(&root);
	return 0;
}