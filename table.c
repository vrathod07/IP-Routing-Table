#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//Function to allocate memory to Node structure
struct node* createNode(int v)
{
    struct node* newNode; 
    if( (newNode= malloc(sizeof(struct node))) == NULL)
    {
        printf("\nMemory Allocation Failed!\n"); 
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->head = NULL;
    return newNode;
}

//Function to allocate memory to Graph structure
struct Graph* createGraph(int vertices)
{
    struct Graph* graph; 
    if((graph= malloc(sizeof(struct Graph))) == NULL)
    {
        printf("\nMemory Allocation Failed!\n"); 
        exit(1);
    }
    graph->numVertices = vertices;
 
    if((graph->adjLists = malloc(vertices * sizeof(struct node*)))== NULL)
    {
        printf("\nMemory Allocation Failed!\n"); 
        exit(1);
    }
    
    if((graph->visited = malloc(vertices * sizeof(int)))== NULL)
    {
        printf("\nMemory Allocation Failed!\n"); 
        exit(1);
    }
 
    int i;
    for (i = 0; i < vertices; i++) 
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

//Function to print instructions
void welcome(int V)
{
    printf("\t\t\t*************************************************************\n\n");
    printf("\t\t\t                     IP ROUTING TABLE                        \n\n");
    printf("\t\t\t*************************************************************\n\n");
    printf("Routers are marked from 0 to %d\n\n",V-1);
}


void clrscr()
{
    system("@cls||clear");
}

 //Function to add edge
int addEdge(struct Graph* graph, int src, int dest)
{   
    int i,j,V=graph->numVertices;
    int matrix[V][V];
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            matrix[i][j]=0;
        }
    }

    for(i=0;i<V;i++)
    {
        struct node* p=graph->adjLists[i];
        while(p!=NULL)
        {
            matrix[i][p->vertex]=1;
            p=p->next;
        }
    }
    //checks if edge exists
    if(matrix[src][dest]==1)
    {
        printf("Edge already exists!\n"); 
        return dest;
    }

    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
    return dest;
}

//Function to delete an edge
void delEdge(struct Graph* graph, int src, int dest) 
{ 

    struct node* p;
    struct node* q;
    int flag=1; //represent node is not deleted
    p=graph->adjLists[src];
    while(flag!=0)
    {
        if(p==NULL)
        {
            printf("Src Edge does not exist!\n");
            flag=0;
        }
        else if(graph->adjLists[src]->vertex==dest)
        {
            graph->adjLists[src]=p->next;
            free(p);
            flag=0;
        }
        else if(p->next!=NULL && p->next->vertex==dest)
        {
            q=p;
            p=p->next;
            q->next=p->next;
            free(p);
            flag=0;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
    p=graph->adjLists[dest];
    flag=1;

    while(flag!=0)
    {
        if(p==NULL)
        {
            printf("Dest Edge does not exist!\n");
            flag=0;
        }
        else if(graph->adjLists[dest]->vertex==src)
        {
            graph->adjLists[dest]=p->next;
            free(p);
            flag=0;
        }
        else if(p->next!=NULL && p->next->vertex==src)
        {
            q=p;
            p=p->next;
            q->next=p->next;
            free(p);
            flag=0;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
}

//Funtion to print  routing table
void printDevices(struct Graph* graph)
{
    int v;
    printf("\nRouter\tIPaddress\t\tSubmask\t\t\tInterface");
    for (v = 0; v < graph->numVertices; v++)
    {
        if(graph->adjLists[v]==NULL)
        {
            printf("\n%d\t", v);
            printf("No devices connected!\n");
            continue;
        }
        LL *q = graph->adjLists[v]->head;
        if(q==NULL)
        {
            printf("\n%d\t", v);
            printf("No devices connected!\n");
        }
        int i=0;

        while(q!=NULL)
        {
            printf("\n%d\t%-20s\t%-20s\t%-20s", v,q->ip_addr,q->submask,q->interface);
            q=q->next;
            i++;
        }
    }
}



//Function to compare and return minimum index 
int minDistance(int dist[],bool sptSet[],int V) 
{ 
      
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
//Function to print shortest path 
void printPath(int parent[], int j) 
{ 
      
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  
    printPath(parent, parent[j]); 
  
    printf("%d ", j); 
} 
  
//Function to print distance array 
int printSolution(int dist[], int n, int parent[],int V) 
{ 
    int src = 0; 
    printf("Vertex\t\t HopDistance\tPath"); 
    for (int i = 1; i < V; i++) 
    {
        if(dist[i]>=INT_MAX || dist[i]<=-INT_MAX+1)
        {
            
            printf("\n%d -> %d \t\t %d\t\t%d ", src, i, -1, src); 
            printf("No Path!");
            continue; 
        }
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); 
        printPath(parent, i); 
    } 
} 

//Funtion that implements Dijkstra's algorithm  
void dijkstra(int V, int graph[V][V], int src) 
{ 
    
    int dist[V];  //Stores the shortest distance from src to i 
    bool sptSet[V]; //sptSet[i] is true if shortest path found 
    int parent[V]; // Parent array to store shortest path 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
    { 
        parent[0] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < V - 1; count++) 
    { 
        // Pick the minimum distance to next node
        int u = minDistance(dist, sptSet, V); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value
        for (int v = 0; v < V; v++) 
            if (!sptSet[v] && graph[u][v] && 
                dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    } 
  
    // print the constructed distance array 
    printSolution(dist, V, parent,V); 
}

//Function to generate matrix and find shortest path using Dijkstra's algorithm
void genMat_path(struct Graph* graph,int V)
{
    int i,j;
    int matrix[V][V];
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            matrix[i][j]=0;
        }
    }

    for(i=0;i<V;i++)
    {
        struct node* p=graph->adjLists[i];
        while(p!=NULL)
        {
            matrix[i][p->vertex]=1;
            p=p->next;
        }
    }
    dijkstra(V, matrix, 0);
}

 
//Function to search for a device with given IP address
void DFS(struct Graph* graph, int vertex, char* ip) 
{
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;
    if(temp==NULL)
    {
        printf("Node(s) / Node 0 not initialized!");
        return;
    }

    graph->visited[vertex] = 1;
    printf("Router %d - ", vertex);
    LL *q=temp->head;
    int flag=0;//represent ip address not fount yet

    while(q!=NULL)
    {
        if(strcmp(q->ip_addr,ip)==0)
        {
            flag=1;
            break;
        }
        else
        {
            q=q->next;
        }
    }

    if(flag==1)
    {  
        printf("Device found!\n");
    }
    else
    {
        printf("Device NOT found!\n");
    }
    
    while(temp!=NULL) 
    {
        int connectedVertex = temp->vertex;
     
        if(graph->visited[connectedVertex] == 0) 
        {
            DFS(graph, connectedVertex, ip);
        }
        temp = temp->next;
    }      
}

//Function to reset visited flags
void resetDFS(struct Graph* graph, int vertex)
{
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;
        
    graph->visited[vertex] = 0;
    
    while(temp!=NULL) 
    {
        int connectedVertex = temp->vertex;
        
        if(graph->visited[connectedVertex] == 1) 
        {
            resetDFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

//Function to initialize and add device details
void details(struct node*p)
{   
    if(p==NULL)
    {
        printf("Add Router Node First!\n");
    }
    else if(p->head==NULL)
    {
        LL *q;
        if( (q=malloc(sizeof(LL))) == NULL)
        {
            printf("\nMemory Allocation Failed!\n"); 
            exit(1);
        }
        printf("/Device Details/\n");
        printf("Enter IP Addrress : ");
        scanf("%s",q->ip_addr);
        printf("Enter Submask : ");
        scanf("%s", q->submask);
        printf("Enter Interface : ");
        scanf("%s",q->interface);
        q->next=NULL;
        p->head=q;
    }
    else
    {
        LL *r=p->head;
        while(r->next!=NULL)
        {
            r=r->next;
        }
        LL *q;
        if( (q=malloc(sizeof(LL))) == NULL)
        {
            printf("\nMemory Allocation Failed!\n"); 
            exit(1);
        }
        printf("/Device Details/\n");
        printf("Enter IP Addrress : ");
        scanf("%s",q->ip_addr);
        printf("Enter Submask : ");
        scanf("%s",q->submask);
        printf("Enter Interface : ");
        scanf("%s",q->interface);
        q->next=NULL;
        r->next=q;
    }

}

//Function to print device details
void printDetails(struct node* p)
{
    if(p==NULL)
    {
        printf("Node does not exist!\n"); 
        return;
    }
    LL *q=p->head;
    int i=0;
    if(q==NULL)
    {
        printf("No Devices!");
    }
    while(q!=NULL)
    {
        printf("Device %d\n",i);
        printf("IP Address :  %s \n",q->ip_addr);
        printf("Submask :  %s \n",q->submask);
        printf("Interface :  %s \n",q->interface);
        q=q->next;
        i++;
        printf("\n");
    }
}
 
//Function to print adjacency list of router nodes
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\nAdjacency Router list of vertex %d => ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL");
    }
}

void delete_device(struct Graph* graph, int vertex, char* ip) 
{
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;
    if(temp==NULL)
    {
        printf("Node(s) / Node 0 not initialized!");
        return;
    }

    graph->visited[vertex] = 1;
    printf("Router %d - ", vertex);
    LL *q=temp->head;
    LL *n=NULL;
    int flag=0;

    while(q!=NULL)
    {
        if(strcmp(q->ip_addr,ip)==0)
        {
            if(n == NULL && q == temp->head){
                flag = 1;
                temp->head = q->next;
                q->next = NULL;
                free(q);
            }
            else{
                flag=1;
                n->next = q->next;
                q->next = NULL;
                free(q);
            }
            break;
        }
        else
        {
            n = q;
            q=q->next;
        }
    }

    if(flag==1)
    {  
        printf("Device found!\n");
        printf("Device Deleted\n");
    }
    else
    {
        printf("Device NOT found!\n");
    }
    
    while(temp!=NULL) 
    {
        int connectedVertex = temp->vertex;
     
        if(graph->visited[connectedVertex] == 0) 
        {
            delete_device(graph, connectedVertex, ip);
        }
        temp = temp->next;
    }      
}