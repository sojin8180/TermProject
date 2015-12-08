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
