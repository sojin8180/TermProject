
void printFor()
{
   ForT *temp = first;

   printf(">> 환승역: ");
   while (temp->next != NULL)
   {
      temp = temp->next;
   }

   while (temp != NULL)
   {
      printf("%s ", temp->name);
      temp = temp->prev;
   }
   printf("\n");
}
