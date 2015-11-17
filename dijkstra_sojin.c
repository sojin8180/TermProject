#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NUM_VERTEX 5
#define NUM_EDGES  8
struct node 
{
   int v;   //vertex 번호
   int weight;
   struct node *next;
};

struct edge
{
   int from;
   int to;
   int w;
};
struct dijkstra
{
   int found;   //K,  최단거리가 알려졌는기 ? 1=yes, 0 =no
   int distance;
   int prev_vertex;
};

struct dijkstra dtable[NUM_VERTEX];

struct edge edges[NUM_EDGES];


struct node *graph[NUM_VERTEX];     //init with null

/*----------------cycle detection array -------------------*/
int cycle_detection[NUM_VERTEX] = {0,1,2,3,4};

/*------------------vertex 방문여부 표시 배열 ---------*/
// if visited[i] ==1, visited
//                 0, otherwise
int visited[NUM_VERTEX]={0};
/*-------------------Queue related-----------------*/
int head =0;
int tail =0;
int que[NUM_VERTEX];
/*------------------------Stack related ----------------*/
int stack[NUM_VERTEX];
int top = -1;
/*----------------cycle detection function -------------------*/
void putThemintoSameGroup(int v1,int v2)
{
   int g1 = cycle_detection[v1];
   int g2 = cycle_detection[v2];

   int smaller, bigger;

   if(g1 > g2)
   {
      bigger = g1;
      smaller = g2;
   }
   else 
   {
      bigger = g2;
      smaller = g1;
   }
   {
      int i;
      for(i=0;i<NUM_VERTEX;i++)
      {
         if(cycle_detection[i] == bigger)
         {
            cycle_detection[i] = smaller;
         }
      }
   }
}
/*-------------------Queue function-----------------*/
void enque(int v)
{
   if((tail+1)%NUM_VERTEX == head);
   {
      printf("queue full\n");
      return ;
   }
   que[tail] = v;
   tail = (tail+1)%NUM_VERTEX;
}

//return -1 if the queue is empty
int isQueEmpty()
{
   if(head == tail)
   {
      return 1;
   }
   else 
   {
      return 0;
   }
}

int deque()
{
   int temp = -1;
   if(isQueEmpty()==0)
   {
      temp = que[head];
      head = (head + 1) % NUM_VERTEX;
   }
   {
      return -1;
   }
   return temp;

}
//return 1 if the queue is empty
//       0  otherwise

/*------------------stack function-----------------*/

void push(int v)
{
   if(top==NUM_VERTEX-1)
   {
      printf("stack is full\n");
      return;
   }
   top++;
   stack[top] = v;
}
//
//return 1  if the stack is empty
//       0 otherwise
//

int isStackEmpty()
{
   if(top ==-1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}
int pop()
{
   int temp =0;
   if(top == -1)
   {
      printf("stack is empty\n");
      return -1;
   }
   temp = stack[top];
   top--;
   return temp;
}
//
// if doReverse ==1,   1->0
// otherwise
//
void addEdge(int v1, int v2,int w,int doReverse)     //0,  1 0->1, 1-> 0
{
   struct node *new_one = (struct node *)malloc(sizeof(struct node));
   struct node *cur = graph[v1];

   new_one->v = v2;
   new_one->next =0;
   new_one->weight =w;
   if(cur == 0)    //v1에 아무 것도 붙어 있지 않는 상태
   {
      graph[v1] = new_one;
   }
   else
   {
      while(cur->next != 0)
      {
         cur = cur->next;
      }
      cur->next = new_one;
   }

   if(doReverse == 1 )          //0->1 , 1->0
   {
      addEdge(v2,v1,w,0);
   }
   return ;
}
void showAdjacentVertex(int v)
{
   struct node *cur = graph[v];

   while(cur != 0)
   {
      printf("%d is the adjacent vertex\n",cur->v);
      cur = cur->next;
   }
}

//v와 연결된 vertex중, 아직까지 방문하지 않은  vertex를 반환
//만약, 조건만족 vertex가 없으면, -1을 반환ㅑ
int findNextVertex(int v)
{
   struct node *cur = graph[v];

   while(cur!=0)
   {
      if(visited[cur->v]==0)
      {
         return cur->v;
      }
      cur=cur->next;
   }
   return -1; //v에 연결된 vertex중에 방문하지 않은 것이 없다.
}
void doDFS(int v)
{
   printf("visited %d \n",v);
   visited[v] = 1;
   push(v);

   while(isStackEmpty()==0)
   {
      int next_vertex =-1;
      next_vertex = findNextVertex(stack[top]);

      if(next_vertex == -1)
      {
         pop();
      }
      else
      {
         printf("visited %d \n",next_vertex);
         visited[next_vertex] = -1;

      }
   }
}
void addAdjacentNonVisitedVertexToQue(int v)
{
   struct node *cur = graph[v];

   while(cur!=0)
   {
      if(visited[cur->v]==0)
      {
         enque(cur->v);
      }
      cur=cur->next;
   }
}
void doBFS(int v)
{
   enque(v);

   while(isQueEmpty() == 0)
   {
      int k = deque();

      if(visited[k] == 0)
      {
         printf("BFS visited %d \n",k);
         visited[k] = 1;
         addAdjacentNonVisitedVertexToQue(k);
      }
   }
}
void swap_edge(int e1, int e2)
{
   struct edge temp;
   temp = edges[e1];
   edges[e1] = edges[e2];
   edges[e2] = temp;
}
void sortEdges()
{
   //모든 edge를 edges배열에 추가
   //
   int i;
   int edges_index=0;
   for(i=0;i<NUM_VERTEX;i++)
   {
      struct node *cur = graph[i];

      while(cur!=0)
      {
         edges[edges_index].from = i;
         edges[edges_index].to = cur->v;
         edges[edges_index].w = cur->weight;
         edges_index++;
         cur = cur -> next;
      }
   }
   //
   //오름차순으로 정렬, by bubble sort
   //
   {
      int x,y;
      for(y=0;y<NUM_EDGES;y++)
      {
         for(x=0;x<NUM_EDGES-1-y;x++)
         {
            if(edges[x].w > edges[x+1].w)
            {
               swap_edge(x, x+1);
            }
         }
      }
   }
}
void doMST()
{
   int i;
   int mst_edges=0;
   for(i=0;i<NUM_EDGES;i++)
   {
      if(cycle_detection [edges[i].from] != cycle_detection[edges[i].to])
      {
         printf("MST edge %d --- %d (%d) \n",edges[i].from,edges[i].to,edges[i].w);
         mst_edges++;
         if(mst_edges == NUM_VERTEX-1)
         {
            return;
         }
         putThemintoSameGroup(edges[i].from,edges[i].to);
      }
   }
}
void initDTable()
{
   int i;
   for(i=0;i<NUM_VERTEX;i++)
   {
      dtable[i].found =0;
      dtable[i].distance =99999;
      dtable[i].prev_vertex =-1;
   }
}
//최단거리가 알려지지 않은 vertex중에서,
//distance가 가장 짧은 vertex를 반환
//returns -1 if 모든 vertex의 최단거리가 알려졌을 경우,
//
int findDijkstraNextVertex()
{
   int i;
   int smallest_vertex=-1;
   int smallest_distance=99999;

   for(i=0;i<NUM_VERTEX;i++)
   {
      if (dtable[i].found ==0  && dtable[i].distance < smallest_distance)
      {
         smallest_vertex = i;
         smallest_distance = dtable[i].distance;
      }
   }
   return smallest_vertex;
}
void showDTable()
{
   int i;
   for(i=0;i<NUM_VERTEX;i++)
   {
      printf("%d : %d %d %d\n",i,dtable[i].found,dtable[i].distance,dtable[i].prev_vertex);
   }
}
void updateDTable(int v)
{
   struct node *cur = graph[v];

   while(cur !=0)
   {
      //최단거리가 알려지지 않았고,
      //기존 알려진 거리보다, v를 통할 경우, 더 가까우면 dtable을 update한다
      if(dtable[cur->v].found ==0 && 
         (dtable[cur->v].distance > dtable[v].distance + cur->weight))
      {
         dtable[cur->v].distance = dtable[v].distance +cur->weight;
         dtable[cur->v].prev_vertex = v;
      }
      cur = cur->next;
   }
}
void doDijkstra(int v)
{
   int next_vertex =-1;
   dtable[v].distance =0;
   
   while((next_vertex = findDijkstraNextVertex()) != -1)
   {
      dtable[next_vertex].found =1;     //최단거리를 찾았다고 표시
      updateDTable(next_vertex);
   }
   showDTable();
}
void main()
{
   addEdge(0,1,1,0);    //0->1,  1->0
   addEdge(0,2,3,0);
   addEdge(0,4,5,0);    //0->2,  2->0
   addEdge(1,2,2,0);
   addEdge(1,4,4,0);
   addEdge(2,4,6,0);
   addEdge(2,3,7,0);
   addEdge(3,4,8,0);
   //
   // vertex 0 에서 시작하여 BFS를 시행
   //
   //doDFS(0);

   //doBFS(0);
   //sortEdges();
//   doMST();

   initDTable();
   doDijkstra(0);
   
}
