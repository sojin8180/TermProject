Dijkstra *findShortestNotFound(void)
{
 int shortest = 999999;
 Dijkstra *temp = Dlist;
 Dijkstra *shortestNode = 0;
 while (temp != NULL)
 {
  if (temp->found == 0 && temp->dist < shortest)
  {
   shortest = temp->dist;
   shortestNode = temp;
  }
  temp = temp->next;
 }
 return shortestNode;
}
