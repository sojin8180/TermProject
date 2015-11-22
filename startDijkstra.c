#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

typedef struct mysubway
{
	char identity[10];	
	char name[30];		
	char kind[10];
	int weight;
	int transeflag; 
	struct mysubway *next;
	struct mysubway *prev; 
	struct mysubway *connect; 

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
mysubway *map = NULL;
Dijkstra *Dlist = NULL;
void addDlist(char *name, char *identity, char *kind)
{
	Dijkstra *fresh = (Dijkstra *)malloc(sizeof(Dijkstra));
	fresh->next = 0;
	fresh->found = 0;
	fresh->dist = 0;
	fresh->real = 0;
	strcpy(fresh->kind, kind);
	strcpy(fresh->name, name);
	strcpy(fresh->identity, identity);
	if (Dlist == NULL)
	{
		Dlist = fresh;
		return;
	}
	else
	{
		Dijkstra *temp = Dlist;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = fresh;
	}
}
void addEdge(char *identity, char *name, char *kind)  
{
	mysubway *fresh = (mysubway *)malloc(sizeof(mysubway));
	strcpy(fresh->identity, identity);
	strcpy(fresh->name, name);
	strcpy(fresh->kind, kind);
	fresh->next = fresh->prev = NULL;
	fresh->connect = NULL;
	fresh->weight = 0;
	addDlist(name, identity, kind);

	if (map == NULL)
	{
		map = fresh;
	}
	else  
	{
		mysubway *cur = map;
		while (cur->next != 0) 
		{
			cur = cur->next;
		}
		cur->next = fresh;
		fresh->prev = cur;
	}
}
void Load(void)
{
	FILE *dataload = NULL;
	FILE *connectload = NULL; 
	int cnt = 0, escape;
	int dist;
	char identity[20], identity2[20], name[30], kind[10];
	dataload=fopen("seoul1.txt", "rt");
	connectload=fopen("seoul2.txt", "rt");

	while (1)
	{
		escape = fscanf(dataload, "%s%s%s", identity, name, kind);
		if (escape == EOF){ break; }
		addEdge(identity, name, kind);
	}
	while (1)
	{
		escape = fscanf(connectload, "%s%s%d", identity, identity2, &dist);
		if (escape == EOF){ break; }
		//addWeight();
	}

	fclose(dataload);
	fclose(connectload);
}
void startDijkstra(char *startStation, char *destStation) // startNode ~ destNode까지의 최단거리
{
	Dijkstra *temper = Dlist;
	Dijkstra *startNode = NULL;

	while (temper != NULL)
	{
		if (strcmp(temper->name, startStation) == 0)
		{
			startNode = temper;
			printf("\ntemper->name: %s\n", startNode->name);
			break;
		}
		temper = temper->next;
	}
}
int main(void)
{
	Load();		
	startDijkstra("작전","인천대입구");
	return 0;
}
