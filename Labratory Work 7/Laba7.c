#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

char* LastWordDetecting(char string[]) //Получение последнего слова
{
	char* beginning;//Адрес начала
	for (beginning = string; *beginning; beginning++); //Конец строки
	while (*(--beginning) == ' ' && beginning >= string);
	if (beginning < string)
		return NULL;
	while (beginning != string && *(--beginning) != ' ');
	if (beginning == string) return string;
	return beginning + 1;//Вернуть без пробела
}

void print_words(char* sentence, char* lastword)
{
	char string[1000];
	strcpy(string, sentence);
	char* word = strtok(string, " ");
	while (word != NULL)
	{
		int p = strlen(word);
		int count = 0, letters = 0;
		char wl[10], wll[10] = { NULL };
		int j = 0;
		for (int i = 0; i < p; i++)
		{
			if ((word[i] >= '0' && word[i] <= '9') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
			{
				letters++;
				if (letters <= 10)
				{
					wl[j] = word[i];
					j++;
				}
			}
		}
		for (int i = 0; i < letters; i++)
		{
			if (wl[i] == lastword[i])
			{
				count++;
			}
		}
		if (letters != count)
		{
			printf("\n\n");
			int i = 0;
			for (int k = 0; k < j - 1; k++) 
			{
				wll[k] = wl[i];
				i++;
			}

			for (int i = 0; i < j; i++)
			{
				printf("%c", wll[i]);
			}
			printf("\n");
		}
		word = strtok(NULL, " ");
	}

}

int main(void)
{
	char text[350], sentence[350];
	char* lastword;
	puts("Print sentence:");
	gets(text);
	strcpy(sentence, strtok(text, "."));//Чтобы строка считывалась до точки
	lastword = LastWordDetecting(sentence);
	if (lastword == NULL)
	{
		printf("String is empty\n");
		return 0;
	}
	puts("\nThe last word is:");
	puts(lastword);
	print_words(sentence, lastword);
	return 0;
}