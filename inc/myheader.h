#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

struct mysubway;
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

struct Dijkstra;
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

struct ForPrint;
typedef struct ForPrint
{
 char name[30];
 int real;
 struct ForPrint *next;
 struct ForPrint *prev;
}ForPrint;

struct ForT;
typedef struct ForT
{
 char name[30];
 struct ForPrint *next;
 struct ForPrint *prev;
}ForT;

void Mainmenu(void);
void Load(void); // 지하철 정보를 얻어올 함수
void addEdge(char *, char *, char *);
void addWeight(char *, char *, int);
void addDlist(char *, char *, char *);
//void showConnected(void);
int findDist(char *, char *, char *);
void startDijkstra(char *, char *);
Dijkstra *findShortestNotFound(void);
void connectTransfer(void);
void addDLL(char *, int);
void printRDLL(void);
void addTrans(mysubway*, mysubway*, int);
void addFor(char *);
void printFor();
int isInoverlap(char *);
int isInSubway(char *);

extern mysubway *map;
extern Dijkstra *Dlist;
extern ForPrint *head;
extern ForT *first;

extern char Overlap[700][35];
extern int startrans;
extern int transflag;

#endif
