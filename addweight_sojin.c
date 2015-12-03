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
