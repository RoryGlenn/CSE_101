//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


#define WHITE 1
#define GRAY  2
#define BLACK 3

typedef struct GraphObj
{
	// 1. An array of Lists whose i'th element contains the neighbors of vertex i
	List *adjList;

	// 2. An array of ints (or chars, or strings) whose i'th element is the color (white, gray, black) of vertex i
	int *colors;

	// 3. An array of ints whose i'th element is the parent of vertex i
	int *parents;

	// 4. An array of ints whose i'th element is the distance from the (most recent) source to vertex i
	int *distance;

	// 5. Number of vertices called the "order" of the graph
	int order;

	// 6. Number of edges called the "size" of the graph
	int size;

	// 7. Label of the vertex that was most recently used as a source for BFS
	int source;

	// 8.
	int *discover;

	// 9. When DFS is complete the stack stores the vertices ordered by decreasing finish times. 
	int *finish;

} GraphObj;

									/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
	Graph G 		 = NULL;
	G 		 		 = malloc(sizeof(GraphObj));
	G->order 		 = n;
	G->source 		 = NIL;	
	G->size 		 = 0;	// number of edges
	G->adjList       = malloc(sizeof(List) * ( n + 1 ));
	G->colors        = malloc(sizeof(int)  * ( n + 1 ));
	G->parents       = malloc(sizeof(int)  * ( n + 1 ));
	G->distance      = malloc(sizeof(int)  * ( n + 1 ));
	G->discover      = malloc(sizeof(int)  * ( n + 1 ));
	G->finish        = malloc(sizeof(int)  * ( n + 1 ));

	for (int i = 1; i <= n; i++)
	{
		G->colors[i]      = WHITE;
		G->distance[i]    = UNDEF;
		G->parents[i]     = NIL;
		G->discover[i]    = UNDEF;
		G->finish[i]      = UNDEF;
		G->adjList[i]     = newList();
	}

	return G;
}

void freeGraph(Graph* pG)
{
	if(pG!= NULL && *pG != NULL)
	{
		for (int i = 0; i < getOrder(*pG); i++)
		{	
			// valgrind says this is a problem/mem leak
			freeList(&(*pG)->adjList[i]);
		}

		free((*pG)->adjList);
		free((*pG)->distance);
		free((*pG)->colors);
		free((*pG)->parents);
		free((*pG)->discover);
		free((*pG)->finish);	
		free(*pG);
		*pG = NULL;
	}
}

											/*** Access functions ***/
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getOrder() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return G->order;
}

int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getSize() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}	

	return G->size;
}

int getSource(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getSouce() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return G->source;
}

/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getParent() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getParent() on invalid u\n");
		exit(EXIT_FAILURE);
	}

	return G->parents[u];
}

 /* Pre: 1 <= u <= n = getOrder(G) */
int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getDiscover() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getDiscover on invalid u\n");
		exit(EXIT_FAILURE);
	}


	return G->discover[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getFinish() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getFinish() on invalid u\n");
		exit(EXIT_FAILURE);
	}

	return G->finish[u];
}


// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getDist() on invalid u\n");
		exit(EXIT_FAILURE);
	}

	if(getSource(G) == NIL)
	{
		//printf("Graph Error: calling getDist(), must run BFS first\n");
		return UNDEF;
	}

	return G->distance[u];
}

// appends to the List L the vertices of a shortest path in G from
// source to u, or appends to L the value NIL if no such path exists.
// getPath() has the precondition getSource(G) != NIL, so BFS() must
// be called before getPath()
void getPath(List L, Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(getSource(G) == NIL)
	{
		printf("Graph Error: calling getPath() on NIL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getPath() on invalid u bounds\n");
		exit(EXIT_FAILURE);
	}
					// Tuan Tran helped me figure this part out because I couldn't do it on my own

	if(u == getSource(G))
	{
		append(L, u);
	}
	else if(G->parents[u] == NIL)
	{
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->parents[u]);
		append(L, u);
	}
}
										/*** Manipulation procedures ***/

// deletes all edges of G restoring it to its original (no edge) state.
void makeNull(Graph G)
{
	for(int i = 1; i <= G->order; i++)
	{
		clear(G->adjList[i]);
		G->colors[i] 	 = WHITE;
		G->distance[i]   = NIL;
		G->parents[i]    = UNDEF;
	}

	G->size   = 0;
	G->source = NIL;
}

// inserts a new edge joining u to v, i.e u is added to the adjacency List
// of v, and v to the adjacency List of u.
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on invalid arguments\n");
		exit(EXIT_FAILURE);
	}

	addArc(G, u, v);
	addArc(G, v, u); 

	// I decrement here because I call addArc() twice which
	// increments twice when it should only increment once
	G->size--; 
}

// inserts a new directed edge from u to v, i.e v is
// added to the adjacency List of u (but not u to the adjacency List of v)
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}	

	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on invalid arguments\n");
		exit(EXIT_FAILURE);
	}

	moveFront(G->adjList[u]);

	// move to the end of the list
	while(index(G->adjList[u]) > -1 && v > get(G->adjList[u]))
	{
		moveNext(G->adjList[u]);
	}

	if(index(G->adjList[u]) == -1)
	{
		append(G->adjList[u], v);
		G->size++;
	}
	else
	{
		insertBefore(G->adjList[u], v);
		G->size++;
	}
}

// tried to make this as close as possible to the psuedocode that was given
void BFS(Graph G, int s)
{
	G->source = s;
	int x = 0;
	int y = 0;

	// set all values to defaults
	for(int i = 1; i <= getOrder(G); i++) 					// 1. for 𝑥 ∈ V(G) − {s}
	{
		G->colors[i] = WHITE; 								// 2. color[𝑥] = white
		G->distance[i] = UNDEF; 							// 3. 𝑑[𝑥] = ∞
		G->parents[i] = NIL; 								// 4. 𝑝[𝑥] = nil
	}

	G->colors[s] = GRAY; 									// 5. color[𝑠] = gray // discover the source 𝑠
	G->distance[s] =  0; 									// 6. 𝑑[𝑠] = 0
	G->parents[s] = NIL;		    						// 7. 𝑝[𝑠] = nil
	
	List Q = newList(); 									// 8. 𝑄 = ∅ // construct a new empty queue
	append(Q, s); 											// 9. Enqueue(𝑄, 𝑠)

	while(length(Q) > 0) 									// 10. while 𝑄 ≠ ∅
	{
		moveFront(Q);
		x = get(Q); 
		deleteFront(Q);										// 11. 𝑥 = Dequeue(𝑄)
		moveFront(G->adjList[x]);
			
		while(index(G->adjList[x]) != -1) 					// 12. for 𝑦 ∈ adj[𝑥]		
		{
			y = get(G->adjList[x]);

			if(G->colors[y] == WHITE) 			  	    	// 13. if color[𝑦] == white // 𝑦 is undiscovered
			{
				G->colors[y] = GRAY; 				   		// 14. color[𝑦] = gray // discover 𝑦
				G->distance[y] = G->distance[x] + 1; 		// 15. 𝑑[𝑦] = 𝑑[𝑥] + 1
				G->parents[y] = x; 				   			// 16. 𝑝[𝑦] = 𝑥
				append(Q, y); 						   		// 17. Enqueue(𝑄, 𝑦)
			}
			moveNext(G->adjList[x]); 
		}
		G->colors[x] = BLACK;						   		// 18. color[𝑥] = black // finish 𝑥
	}

	freeList(&Q);
	Q = NULL;
}

// tried to make this as close as possible to the psuedocode that was given
void Visit(Graph G, List S, int x, int *time)
{
	G->discover[x] = ++(*time);								// 1. 𝑑[𝑥] = (+ + time) // discover 𝑥
	G->colors[x]   = GRAY; 									// 2. color[𝑥] = gray

	moveFront(G->adjList[x]);

	while(index( G->adjList[x]) >= 0 )	        			// 3. for all 𝑦 ∈ adj[𝑥]
	{					
		if( G->colors[ get( G->adjList[x] ) ] == WHITE)		// 4. if color[𝑦] == white
		{
			G->parents[ get( G->adjList[x] ) ] = x; 		// 5. 𝑝[𝑦] = 𝑥
			Visit(G, S, get( G->adjList[x] ), time);		// 6. Visit(𝑦)
		}
		moveNext(G->adjList[x]);
	}

	G->colors[x] = BLACK;									// 7. color[𝑥] = black
	G->finish[x] = ++(*time);								// 8. 𝑓[𝑥] = (+ + time) // finish 𝑥
	prepend(S, x);
}

// tried to make this as close as possible to the psuedocode that was given
void DFS(Graph G, List S)
{
	int time;
	//int size;
	//int hasVisited = 0;

	// if(length(S) != getOrder(G))
	// {
	// 	printf("DFS Error: calling DFS() on invalid graph\n");
	// 	exit(EXIT_FAILURE);
	// }


	for(int i = 1; i <= getOrder(G); i++)	    // 1. for all 𝑥 ∈ 𝑉(𝐺)
	{
		G->colors[i]   = WHITE;				    // 2. color[𝑥] = white
		G->parents[i]  = NIL;					// 3. 𝑝[𝑥] = nil
		G->discover[i] = UNDEF;
		G->finish[i]   = UNDEF;
	}

	List copyS = copyList(S);
	clear(S);

	time = 0;								    // 4. time = 0
	moveFront(copyS);
	while ( index(copyS) >= 0 ) 		        	    // 5. for all 𝑥 ∈ 𝑉(𝐺)
	{
		if(G->colors[get(copyS)] == WHITE)			// 6. if color[𝑥] == white
		{   
			Visit(G, S, get(copyS), &time); 		// 7. Visit(𝑥)
		}

		moveNext(copyS);
	}

	// size = length(S) / 2;
	// while( size > 0 )
	// {
	// 	deleteBack(S);
	// 	size--;
	// }
	freeList(&copyS);

}
											/*** Other operations ***/

// The digraph 𝐺^𝑇 is obtained by reversing the directions on all edges of 𝐺
// Function transpose() returns a reference to a new graph object representing the transpose of G.
// Both transpose() and copyGraph() could be considered constructors since they create new graph objects
Graph transpose(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling transpose() on an NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	Graph T = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++)
	{
		moveFront(G->adjList[i]);

		while( index( G->adjList[i] ) >= 0 )
		{
			addArc(T, get(G->adjList[i]), i);
			moveNext(G->adjList[i]);
		}
	}

	return T;
}

// 
// copyGraph() returns a reference to a new graph which is a copy of G. 
// Both transpose() and copyGraph() could be considered constructors since they create new graph objects
Graph copyGraph(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling copyGraph() on a NULL grapgh reference\n");
		exit(EXIT_FAILURE);
	}

	int i = 1;
	Graph C = newGraph(getOrder(G));

	while(i <= getOrder(G))
	{
		moveFront(G->adjList[i]);
		while( index( G->adjList[i] ) >= 0)
		{
			addArc(C, i, get(G->adjList[i]));
			moveNext(G->adjList[i]);
		}

		i++;
	}


	return C;
}

// prints the adjacency list representation of G to the file pointed to by out.
// The format of this representation should match the aboce examples,
//  so all that is required by the client is a single call to printGraph()
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling printGraph() on an empty Graph reference\n");
		exit(EXIT_FAILURE);
	}

	// Do I really need this if() check?
	if(out == NULL) 
	{
		printf("out Error: calling printGraph() on an empty out reference\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out, "%d: ", i); 
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}
}