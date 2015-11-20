#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

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

Dijkstra *Dlist = NULL;

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
