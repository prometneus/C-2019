#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>

struct Node 
{
	double degree;
	int coefficient;
	struct Node* next;
};
typedef struct Node List;

List* create()
{
	int n = 0;
	List *head = (List*)malloc(sizeof(List));
	List *p = head;
	printf("Enter the amount of manoms in the polynomial:\t");
	if (scanf("%d", &n) != 1 || n <= 0 || isdigit(n) != 0)
	{
		printf("Input error\n");
		free(head);
		head = NULL;
	}
	for (p; n > 0; p = p->next)
	{
		printf("Enter the degree of manom:\t");
		scanf("%lf", &p->degree);
		printf("Enter the coefficient of manom:\t");
		scanf("%d", &p->coefficient);
		if (n != 1)
		{
			p->next = (List*)malloc(sizeof(List));
		}
		else p->next = NULL;
		n--;
	}
	return head;

}

void display(List* head)
{
	List* p = head;
	for (p; p != NULL; p = p->next) 
	{
		if (p->degree != 0)
		{ 
			if (p->coefficient > 0) printf("%dx^%.2lf", p->coefficient, p->degree); 
			else printf("(%dx^%.2lf)", p->coefficient, p->degree);
		}
		else printf("%d", p->coefficient);
		if (p->next != NULL) printf(" + ");
	}
}

List* reduction(List* head)
{
	List* save = NULL;
	int flag = 0;
	for (List* p = head, *buf = p; p != NULL; p = p->next, buf = p)
	{
		if (flag == 1) free(save);
		flag = 0;
		if (p == head && p->coefficient == 0 && p->next == NULL) head = NULL;
		for (List* tmp = p->next; tmp != NULL;)
		{
			if ((p->coefficient == 0) && (p == head)) // Условие при котором перемещаем голову
			{
				head = p->next; // перемещаем голову
				flag = 1;
				save = p;
				break;//Выход из цикла, чтобы не пропустить элемент
			}
			if (tmp->coefficient == 0)
			{
				buf->next = tmp->next;
				save = tmp;
				tmp = tmp->next; //Шаг цикла
				free(save);
			}
			else
			{
				if (p->degree == tmp->degree)
				{//Алгоритм очистки лишнего элемента, который был учтен в сумме
					p->coefficient += tmp->coefficient; 
					buf->next = tmp->next;
					save = tmp;
					tmp = tmp->next; // Шаг цикла
					free(save);
				}
				else
				{
					buf = tmp; 
					tmp = tmp->next; //Шаг цикла
				}
			}
		}
	}
	return head;
}

List* collecting(List* head, List* Head)
{
	List* HEAD = NULL;
	for (List* p = head; p != NULL; p = p->next)//Первый список
	{
		int found = 0;
		for (List* h = Head; h != NULL; h = h->next)//Сравнение со вторым
		{
			if (p->degree == h->degree)
			{
				found++;
				break;
			}
		}
		if (found == 0)//Создание третьего из неповторяющихся элементов
		{
			List* k = (List*)malloc(sizeof(List));
			k->coefficient = p->coefficient;
			k->degree = p->degree;
			k->next = HEAD;
			HEAD = k;
		}
	}
	return HEAD;
}

List* removehead(List* head)//Функция удаления списка через очистку головы списка
{
	List* p = NULL;
	if (head != NULL)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

int main(void)
{
	List* head = NULL, * Head = NULL, * HEAD = NULL;
	head = create();
	Head = create();
	if (head != NULL && Head != NULL)
	{
		display(head);
		printf("\n");
		display(Head);
		head = reduction(head);
		Head = reduction(Head);
		printf("\nReduced polynomials\n");
		display(head);
		printf("\n");
		display(Head);
		HEAD = collecting(head, Head);
		if (HEAD != NULL) 
		{
			printf("\nNewly formed list:\t");
			display(HEAD);
		}
		else printf("\nNew list in empty");
		while (head != NULL) 
		{
			head = removehead(head);
		}
		while (Head != NULL) 
		{
			Head = removehead(Head);
		}
		while (HEAD != NULL) 
		{
			HEAD = removehead(HEAD);
		}
	}
	printf("\n\n");
	return 0;
}