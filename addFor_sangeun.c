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
	struct ForT *next; //11.26 ForPrint->ForT
	struct ForT *prev; //11.26 ForPrint->ForT
}ForT;
ForT *first = NULL;
mysubway *map = NULL;
Dijkstra *Dlist = NULL;
int startrans;
int transflag;
void addDLL(char *name, int num)
{
	ForPrint *fresh;
	fresh = (ForPrint *)malloc(sizeof(ForPrint));
	fresh->next = fresh->prev = NULL;
	strcpy(fresh->name, name);
	fresh->real = num;

	ForPrint *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = fresh;
	fresh->prev = temp;
	return;
}
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

Dijkstra *findShortestNotFound(void) //by sojin
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
// ------------ Dijkstra -------------- // 
int findDist(char *main_name, char *sub_name, char *kind)
{
	mysubway *temp = map;
	mysubway *object = NULL;
	while (temp != NULL)
	{
		if (strcmp(temp->name, main_name) == 0)
		{
			object = temp;
			break;
		}
		temp = temp->next;
	}
	temp = object;
	//printf("-----------------------%s", temp->name);
	//getchar();
	while (temp != NULL)
	{
		if (strcmp(temp->name, sub_name) == 0 && strcmp(temp->kind, kind) == 0)
		{
			return temp->weight;
		}
		temp = temp->connect;
	}
	return 999999;
}
void addFor(char *name)
{
	ForT *fresh = (ForT *)malloc(sizeof(ForT));
	ForT *temp = NULL;	
	fresh->next = NULL;
	fresh->prev = NULL;
	strcpy(fresh->name, name);
	temp= first;

	if (first == NULL)
	{
		first = fresh;
		return;
	}
	else
	{
		temp= first;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = fresh;
		fresh->prev = temp;
	}
}
void startDijkstra(char *startStation, char *destStation) // startNode ~ destNode까지의 최단거리
{
	mysubway *temp;
	int shortestNode = -1;
	int prevNode = -1;
	int sum = 0;
	int cnt = 0;
	char change[10];
	char cname[30];
	//  ** 시작노드 **
	Dijkstra *temper = Dlist;
	Dijkstra *show = NULL;
	Dijkstra *startNode = NULL;


	while (temper != NULL)
	{
		if (strcmp(temper->name, startStation) == 0)
		{
			startNode = temper;
			//printf("\ntemper->name: %s\n", startNode->name);
			break;
		}
		temper = temper->next;
	}

	startNode->found = 1; // 최단 경로를 찾았다.
	startNode->dist = 0;
	startNode->prev = NULL; // 자기 이전 녀석은 없다.
	//	printf("시작역 : %s\n", startNode->name);
	// ** startNode에 직접적으로 연결되 있는 노드 탐색  **
	temper = Dlist;
	while (temper != NULL)
	{
		temper->dist = findDist(startStation, temper->name, temper->kind);
		if (temper->dist < 999999 && temper->dist > 0)
		{
			temper->prev = startNode;
		}
		temper = temper->next;
	}
	// -------------여기까지 점검 완료 ---------------//

	while (1)
	{
		temper = findShortestNotFound();
		if (temper == NULL)
		{
			return;
		}
		temper->found = 1;
		temp = map;
		// ----------- Original 을 불러옴 ------------- //
		while (temp != NULL)
		{
			if (strcmp(temper->name, temp->name) == 0 && strcmp(temper->kind, temp->kind) == 0)
			{
				//		printf("%s 환승 %s\n", temp->name, temp->kind);
				break;
			}
			temp = temp->next;
		}
		while (temp->connect != NULL)
		{
			show = Dlist;
			while (show != NULL)
			{
				if (strcmp(show->name, temp->connect->name) == 0 && strcmp(show->kind, temp->connect->kind) == 0)
				{
					//		printf("%s 환승2 %s\n", temp->name, temp->kind);
					break;
				}
				show = show->next;
			}
			if (show->dist > temper->dist + temp->connect->weight) // 더 짧은걸 발견 햇을때
			{
				show->dist = temper->dist + temp->connect->weight;
				show->prev = temper;
				show->real = temp->connect->weight;
			}
			temp = temp->connect;
		}


		if (strcmp(temper->name, destStation) == 0)
		{
			Dijkstra *find = temper;
			// startNode부터 destNode까지의 최단거리를 찾았으니 //
			// destNode부터 prev해서 startNode로 길을 찾아감      //
			do
			{
				addDLL(find->name, find->real);
				if (find->real == 5 && strcmp(find->name, find->prev->name) == 0)
				{
					addFor(find->name);
					transflag = 1;
				}
				find = find->prev;
			} while (find != NULL);
			if (transflag == 1)
			{
				printFor();
			}
			printRDLL();
			if (startrans == 1)
			{
				temper->dist = temper->dist - 5;
			}
			printf("\n");
			printf(">> 소요 거리:  %d distance \n", temper->dist);
			printf("\n");
			return;
		}
	}
}int main(void)
{
	Load();		
	startDijkstra("작전","인천대입구");
	return 0;
}
