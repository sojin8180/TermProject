#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

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

mysubway *map = NULL;
ForT *first = NULL;
Dijkstra *Dlist = NULL;


void Load(void); // 지하철 정보를 얻어올 함수

int main(void)
{
  Load();
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
void addEdge(char *identity, char *name, char *kind)  // 구분은 호선이랑.. 연결관계를 추가.
{
	mysubway *fresh = (mysubway *)malloc(sizeof(mysubway));
	strcpy(fresh->identity, identity);
	strcpy(fresh->name, name);
	strcpy(fresh->kind, kind);
	fresh->next = fresh->prev = NULL;
	fresh->connect = NULL;
	fresh->weight = 0;
	// 판단은 kind로 결정.
	addDlist(name, identity, kind);

	if (map == NULL)  // 맨 처음붙는 경우
	{
		map = fresh;
	}
	else  // 이미 붙어있는 것이 있는 경우,
	{
		mysubway *cur = map;
		while (cur->next != 0) // 맨 끝을 찾아서 
		{
			cur = cur->next;
		}
		cur->next = fresh;
		fresh->prev = cur;
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
void Load(void)
{
 // 최초 한 번만 읽어오므로 전역변수일 필요 없음
 FILE *dataload = NULL; // subway.txt를 읽어올 파일 포인터
 FILE *connectload = NULL; // subwayroad.txt를 읽어올 파일 포인터
 int cnt = 0, escape;
 int dist;
 char identity[20], identity2[20], name[30], kind[10];
 // ----- identity : 역 고유번호 ------ name : 역 이름 ------ kind : 지하철 호선 --------
 dataload=fopen("seoul1.txt", "rt");
 // ----- 출발역 ------ 도착역 ------ 소요거리(weight)
 connectload=fopen("seoul2.txt", "rt");

 /*  메모장 파일이 손상되었는지 아닌지 확인
 if (dataload != NULL)
 printf("불러오기 성공.\n");
 else
 printf("파일이 손상되었음.\n");*/

 while(1)
 {
  escape = fscanf(dataload,"%s%s%s",identity,name,kind);
  if(escape == EOF){break;}
  addEdge(identity, name, kind);
 }
 while(1)
 {
  escape = fscanf(connectload,"%s%s%d",identity,identity2,&dist);
  if(escape == EOF){break;}
  addWeight(identity, identity2, dist);
 }
 fclose(dataload);
 fclose(connectload);
}
