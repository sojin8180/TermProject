#ifndef _HEADER_H
#define _HEADER_H

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

extern Transferdist = 5;
extern char Overlap[700][35];
extern Dijkstra *Dlist = NULL;
extern mysubway *map = NULL;
extern ForPrint *head = NULL;
extern ForT *first = NULL;
extern int startrans;
extern int transflag;

#endif
