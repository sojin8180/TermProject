#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

void Mainmenu()
{
 char *startsubway; // 출발역과 도착역을 선택
 char *destsubway;

 printf("\t\t\tDijkstra Subway Program\n");

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

  return;
}
