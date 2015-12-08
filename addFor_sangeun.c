void addFor(char *name)
{
   ForT *fresh = (ForT *)malloc(sizeof(ForT));
   fresh->next = fresh->prev = NULL;
   strcpy(fresh->name, name);

   if (first == NULL)
   {
      first = fresh;
      return;
   }
   else
   {
      ForT *temp = first;
      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = fresh;
      fresh->prev = temp;
   }
}
