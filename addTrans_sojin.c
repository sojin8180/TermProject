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
 int transeflag; 
 struct mysubway *next;
 struct mysubway *prev;
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
