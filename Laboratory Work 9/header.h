#pragma once
/*Header - файл*/

typedef struct
{
	char name[50];
	char colour[50];
	char smell[40];
	char placement[100];
}flower;

void input(); //Первичный ввод для создания базы данных
void add();
void delete();
void search();
void edit();
void sort();
void display();
