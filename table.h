#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//Structure of devices
typedef struct LL
{
    char ip_addr[20];
    char submask[20];
    char interface[10];
    struct LL *next;
}LL;

//Structure for router node
struct node
{
    int vertex;
    struct node* next;
    LL *head;
};

//Structure for Network of routers
struct Graph
{
    int numVertices;
    int* visited;
    struct node** adjLists; //To store an array of Linked lists
};

//Function Headers
struct Graph* createGraph(int); //Function to allocate memory to Graph 
struct node* createNode(int); //Function to allocate memory to Node
int addEdge(struct Graph*, int, int); //Function to add edge
void delEdge(struct Graph*, int, int); //Function to delete an edge
void printGraph(struct Graph*); //Function to print adjacency list
void DFS(struct Graph*, int, char*); //Function to search for a device with given IP address
void delete_device(struct Graph*, int, char*);//Function to delete a device 
void resetDFS(struct Graph*, int); //Function to reset visited flags

void genMat_path(struct Graph*,int); //Function to generate matrx containing info of edge cost
void dijkstra(int V, int[][V], int); //Funtion that implements Dijkstra's algorithm  
int minDistance(int [],bool [],int); //Function to compare and return minimum index 
void printPath(int [], int); //Function to print shortest path 
int printSolution(int [], int, int [],int); //Function to print distance array 

void details(struct node*); //Function to initialize and add device details
void printDetails(struct node*); //Function to print device details

void clrscr(); //Function to clear console on dos/unix/mac/windowsCMD Terminals
void welcome(int); //Function to print instructions

void printDevices(); //Funtion to print devices in each router