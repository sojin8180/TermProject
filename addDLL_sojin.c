void addDLL(char *name, int num)
{
 ForPrint *fresh;
 fresh = (ForPrint *)malloc(sizeof(ForPrint));
 fresh->next = fresh->prev = NULL;
 strcpy(fresh->name, name);
 fresh->real = num;
 if (head == NULL)
 {
  head = fresh;
  return;
 }
 else
 {
  ForPrint *temp = head;
  while (temp->next != NULL)
  {
   temp = temp->next;
  }
  temp->next = fresh;
  fresh->prev = temp;
  return;
 }
}
