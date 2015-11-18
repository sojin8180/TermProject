#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

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
			gets(startsubway);
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
