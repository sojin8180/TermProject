#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct mysubway
{
 char identity[10]; // 역 고유번호
 char name[30];  //  역 이름
 char kind[10];
 int weight;
 int transeflag; // ㅠㅠ
 struct mysubway *next;
 struct mysubway *prev; // ㅋㅋ
 struct mysubway *connect;  // 바로 이어져 있는 호선 환승역 포함.

}mysubway;

typedef struct Dijkstra
{
 char identity[10];
 char name[30];
 int found;
 int dist;
 int real;
 char kind[10];
 struct Dijkstra *prev;
 struct Dijkstra *next;
}Dijkstra;

typedef struct ForPrint
{
 char name[30];
 int real;
 struct ForPrint *next;
 struct ForPrint *prev;
}ForPrint;

typedef struct ForT
{
 char name[30];
 struct ForPrint *next;
 struct ForPrint *prev;
}ForT;

void printRDLL(void)
{
	ForPrint *temp = head;
	int cnt = 0;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	if (strcmp(temp->name, temp->prev->name) == 0)
	{
		startrans = 1;
	}
	while (temp->prev != NULL)
	{
		if (cnt % 7 == 0)
		{
			printf("\n");
		}
		if (strcmp(temp->name, temp->prev->name) != 0)
		{
			printf("%s->", temp->name);
		}
		temp = temp->prev;
		cnt++;
	}
	printf("%s", temp->name);

}
