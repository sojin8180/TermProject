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
   //   printf("시작역 : %s\n", startNode->name);
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
            //      printf("%s 환승 %s\n", temp->name, temp->kind);
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
               //      printf("%s 환승2 %s\n", temp->name, temp->kind);
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
}s
