#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int main()
{
    clrscr();
    printf("\t\t\t*************************************************************\n\n");
    printf("\t\t\t                     IP ROUTING TABLE                        \n\n");
    printf("\t\t\t*************************************************************\n\n");

    printf("Enter  number of router in network you want:");
    int V; 
    scanf(" %d",&V);
    if(V==0)
    {
        printf("No Graph Created! Exit Successful!\n"); 
        exit(0);
    }

    printf("Routers are marked from 0 to %d\n",V-1);
    printf("Root node is marked with 0");

    struct Graph* graph = createGraph(V);

    char ch='\0';
    printf("\n");

    int root=0; 

    while(ch!='9') 
    {
        printf("\n\n Choices:\n\n");
        printf("1.Add Edge between Router nodes\n2.Delete Edge between Router nodes\n3.Find Quick Path from Root Router node 0 \n4.Print Routing Table for all Routers\n5.Connect Device to Router\n6.Print Devices connected to particular Router\n7.Search Device\n8.Remove Device \n9.Exit\n");
        printf("$>");
        scanf(" %c",&ch);

        int s,d; //Source, Destination Edges
        int y; //Stores Router Node Vertex
        char ip[15]; //Stores Device IP Address
        switch(ch) 
        {
            case '1':
                clrscr();
                welcome(V);
                printf("/ Add Edge /\n\n");
                printf("Enter Nodes seperated by a space:");
                scanf("%d %d",&s,&d);
                if(s<V && d<V)
                {

                    if(s==d)
                    {
                        printf("Self referential edges not allowed!\n");
                    }
                    else
                    {
                        root = addEdge(graph, s, d);
                    }
                }
                else
                {
                    printf("Node out of bound!\n");
                }

            break;
            case '2':
                clrscr();
                welcome(V);
                printf("/ Delete Edge /\n\n");
                printf("Enter Nodes seperated by a space:");
                scanf("%d %d",&s,&d);
                if(s<V && d<V)
                    {

                        if(s==d)
                        {
                            printf("Self referential edges do not exist!\n");
                        }
                        else
                        {
                            delEdge(graph, s, d);
                            if(s==root || d==root) 
                            {   
                                root=0;
                            }
                        }
                    }
                    else
                    {
                        printf("Node out of bound!\n");
                    }
            break;
            case '3':
                clrscr();
                welcome(V);
                printf("/ Shortest Path from Root Node marked by 0 /\n\n");
                genMat_path(graph,V);
            break;
            case '4':
                clrscr();
                welcome(V);
                printf("/ Router Representation using Adjacency List /\n\n");
                printGraph(graph);
                printf("\n\n/ Routing Table /\n");
                printDevices(graph);
            break;
            case '5':
                clrscr();
                welcome(V);
                printf("/ Add Device /\n\n");
                printf("Enter Router Node:");
                scanf("%d",&y);
                if(y>=V)
                {
                    printf("Invalid Node!\n");
                    break;
                }
                details(graph->adjLists[y]);
            break;
            case '6':
                clrscr();
                welcome(V);
                printf("/ Print Devices /\n\n");
                printf("Enter Router Node:");
                scanf("%d",&y);
                if(y>=V)
                {
                    printf("Invalid Node!\n");
                    break;
                }
                printDetails(graph->adjLists[y]);
            break;
            case '7':
                clrscr();
                welcome(V);
                printf("/ Search Device /\n\n");
                printf("Enter IP Address of Device:");
                scanf("%s",&ip);
                DFS(graph,root,ip); 
                resetDFS(graph,root);
            break;
            case '8':
                clrscr();
                welcome(V);
                printf("/ Delete Device /\n\n");
                printf("Enter IP Address of Device:");
                scanf("%s",&ip);
                delete_device(graph,root,ip); 
                resetDFS(graph,root); 
            break;
            case '9':
                clrscr();
                welcome(V);
                printf("Exit successful!\n");
            break;
            default:
                clrscr();
                printf("Invalid Option!\n");
            break;
        
        }

    } 

    return 0;
}
