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
