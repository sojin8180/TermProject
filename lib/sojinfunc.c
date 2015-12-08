#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <myheader.h>

mysubway *map;
Dijkstra *Dlist;
ForPrint *head;
ForT *first;

char Overlap[700][35];
int startrans;
int transflag;

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
  return;
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
void addTrans(mysubway *chain, mysubway *chain2, int doReverse)
{
 mysubway *fresh1, *fresh2;
 fresh1 = (mysubway *)malloc(sizeof(mysubway));
 fresh2 = (mysubway *)malloc(sizeof(mysubway));

 strcpy(fresh1->identity, chain->identity);
 strcpy(fresh2->identity, chain2->identity);
 strcpy(fresh1->kind, chain->kind);
 strcpy(fresh2->kind, chain2->kind);
 strcpy(fresh1->name, chain->name);
 strcpy(fresh2->name, chain2->name);
 fresh1->prev = fresh2->prev = NULL;
 fresh1->next = fresh2->next = NULL;
 fresh1->connect = fresh2->connect = NULL;
 fresh1->weight = fresh2->weight = 5;

 if (chain == NULL)
 {
  chain = fresh2;
 }
 else
 {
  mysubway *temp = chain;
  while (temp->connect != NULL)
  {
   temp = temp->connect;
  }
  temp->connect = fresh2;
  // printf("%s %s %s %s\n", chain->name, chain->kind, fresh2->name, fresh2->kind);
 }

 if (doReverse == 1)
 {
  addTrans(chain2, chain, 0);
 }
}
void addWeight(char *identity1, char *identity2, int dist) // 소요거리를 업데이트
{
 // step1. map에서 identity1을 찾고
 // step2. identity2를 찾은 후
 // stemp3. 두개를 연결.
 mysubway *man1 = map, *man2 = 0;
 mysubway *temp = map;
 while (temp != NULL)
 {
  if (strcmp(identity1, temp->identity) == 0)
  {
   man1 = temp;
   break;
  }
  temp = temp->next;
 }
 temp = map;
 while (temp != NULL)
 {
  if (strcmp(identity2, temp->identity) == 0)
  {
   man2 = (mysubway *)malloc(sizeof(mysubway));
   man2->connect = 0;
   strcpy(man2->identity, temp->identity);
   strcpy(man2->kind, temp->kind);
   strcpy(man2->name, temp->name);
   break;
  }
  temp = temp->next;
 }
 // 이제 연결..
 if (man1->connect == NULL)
 {
  man1->connect = man2;
  man1->connect->weight = dist;
 }
 else
 {
  temp = man1->connect;
  while (temp->connect != NULL)
  {
   temp = temp->connect;
  }
  temp->connect = man2;
  temp->connect->weight = dist;
 }
}
void connectTransfer(void) // 환승역을 연결
{
	// 환승역 끼리 연결해야 한다는 사실
	// 중복된 이름을 찾아 그 둘을 연결.
	mysubway *chain = map;
	mysubway *chain2 = map;
	while (chain->next != NULL)
	{
		chain2 = chain->next;
		while (chain2 != NULL)
		{
			if (strcmp(chain->name, chain2->name) == 0)
			{
				if (strcmp(chain->kind, chain2->kind) != 0)
				{
					addTrans(chain, chain2, 1);
					//			printf("%s %s %s %s\n", chain->name, chain->kind, chain2->name, chain2->kind);
				}
			}
			chain2 = chain2->next;
		}
		chain = chain->next;
	}

}
Dijkstra *findShortestNotFound(void)
{
 int shortest = 999999;
 Dijkstra *temp = Dlist;
 Dijkstra *shortestNode = 0;
 while (temp != NULL)
 {
  if (temp->found == 0 && temp->dist < shortest)
  {
   shortest = temp->dist;
   shortestNode = temp;
  }
  temp = temp->next;
 }
 return shortestNode;
}
int isInSubway(char *subway)
{
	// subway가 지하철역에 해당하나?
	Dijkstra *search = Dlist;
	while (search != NULL)
	{
		if (strcmp(search->name, subway) == 0)
		{
			return 1;
		}
		search = search->next;
	}
	return -999;
}
void printRDLL(void)
{
	first = NULL;
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

void Mainmenu()
{
 char *startsubway; // 출발역과 도착역을 선택
 char *destsubway;
 printf("\t\t\tDijkstra Subway Program\n");

 while (1)
 {
  startsubway = (char *)malloc(100);
  printf(" 출발역을 입력해주세요 : ");
  gets(startsubway);
  fflush(stdin);
  // 사용자가 Enter만 연속해서 누를 때의 예외처리
  if (startsubway[0] == NULL)
  {
   system("cls");
   printf("\t\t\tDijkstra Subway Program\n");
   continue;
  }
  // 사용자가 정확히 입력했는지 확인
  while (isInSubway(startsubway) == -999)
  {
   free(startsubway);
   startsubway = (char *)malloc(100);
   printf(" 해당하는 역 이름이 없습니다. 다시 입력해주세요 : ");
   scanf("%s",startsubway);
  }
  destsubway = (char *)malloc(100);
  printf(" 도착역을 입력해주세요 : ");
  gets(destsubway);
  fflush(stdin);
  if (destsubway[0] == NULL)
  {
   system("cls");
   printf("\t\t\tDijkstra Subway Program\n");
   continue;
  }
  while (isInSubway(destsubway) == -999)
  {
   free(destsubway);
   destsubway = (char *)malloc(100);
   printf(" 해당하는 역 이름이 없습니다. 다시 입력해주세요 : ");
   gets(destsubway);
  }
  printf(" 결과는 다음과 같습니다\n");
  startDijkstra(startsubway, destsubway);
  free(startsubway);
  free(destsubway);
  return;
 }

}
