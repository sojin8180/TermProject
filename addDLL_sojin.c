#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

typedef struct mysubway
{
	char identity[10];	// 역 고유번호
	char name[30];		//  역 이름
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

void addDLL(char *name, int num)
{
 ForPrint *fresh;
 fresh = (ForPrint *)malloc(sizeof(ForPrint));
 fresh->next = fresh->prev = NULL;
 strcpy(fresh->name, name);
 fresh->real = num;
 if (head == NULL)
 {
  head = fresh;
 }
 else
 {
  ForPrint *temp = head;
  while (temp->next != NULL)
  {
   temp = temp->next;
  }
  temp->next = fresh;
  fresh->prev = temp;
  return;
 }
}
