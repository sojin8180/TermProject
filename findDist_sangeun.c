// ------------ Dijkstra -------------- // 
int findDist(char *main_name, char *sub_name, char *kind)
{
   mysubway *temp = map;
   mysubway *object = NULL;
   while (temp != NULL)
   {
      if (strcmp(temp->name, main_name) == 0)
      {
         object = temp;
         break;
      }
      temp = temp->next;
   }
   temp = object;
   //printf("-----------------------%s", temp->name);
   //getchar();
   while (temp != NULL)
   {
      if (strcmp(temp->name, sub_name) == 0 && strcmp(temp->kind, kind) == 0)
      {
         return temp->weight;
      }
      temp = temp->connect;
   }
   return 999999;
}
