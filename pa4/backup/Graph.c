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

/*
2. Use the results of BFS to print out the distance from source vertex to the destination vertex
	then use the parent pointers to print out a shortest path from source to destination.
	(see algorithm print path in section 22.2 of the text)


ex: The distance from 1 to 5 is 2
	A shortest 1-5 path is: 1 2 5

	PROGRAMS OPERATION

	1. Read and store the graph and print out its adjacency list representation

	2. Enter a loop that processes the second parth of the input.
			a) Each iteration of the loop should read in one pair of vertices (source, destination),
			b) run BFS on the source vertex,
			c) print the distance to the destination vextex, 
			d) find and print the resulting shortest path, if it exists, or print a message if no path from source to destination exists
*/



typedef struct GraphObj
{
	// 1. An array of Lists whose i'th element contains the neighbors of vertex i
	List *adjacencyList;

	// 2. An array of ints (or chars, or strings) whose i'th element is the color (white, gray, black) of vertex i
	int *arColors;

	// 3. An array of ints whose i'th element is the parent of vertex i
	int *arParents;

	// 4. An array of ints whose i'th element is the distance from the (most recent) source to vertex i
	int *arDistance;

	// 5. Number of vertices called the "order" of the graph
	int order;

	// 6. Number of edges called the "size" of the graph
	int size;

	// 7. Label of the vertex that was most recently used as a source for BFS
	int source;
}GraphObj;

									/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
	Graph G 		 = NULL;
	G 		 		 = malloc(sizeof(GraphObj));
	G->order 		 = n;
	G->source 		 = NIL;	
	G->size 		 = 0;	// number of edges
	G->adjacencyList = malloc(sizeof(List) * ( n + 1 ));
	G->arColors      = malloc(sizeof(int)  * ( n + 1 ));
	G->arParents     = malloc(sizeof(int)  * ( n + 1 ));
	G->arDistance    = malloc(sizeof(int)  * ( n + 1 ));

	for (int i = 1; i <= n; i++)
	{
		G->arColors[i] = WHITE;
		G->arDistance[i] = INF;
		G->arParents[i] = NIL;
		G->adjacencyList[i] = newList();
	}

	return G;
}

void freeGraph(Graph* pG)
{
	if(pG!= NULL && *pG != NULL)
	{
		for (int i = 0; i < getOrder(*pG); i++)
		{
			freeList(&(*pG)->adjacencyList[i]);
		}

		free((*pG)->adjacencyList);
		free((*pG)->arDistance);
		free((*pG)->arColors);
		free((*pG)->arParents);
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

int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getParent() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return G->arParents[u];
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
		printf("Graph Error: calling getDist() on invalid integer u\n");
		exit(EXIT_FAILURE);
	}

	if(getSource(G) == NIL)
	{
		//printf("Graph Error: calling getDist(), must run BFS first\n");
		return INF;
	}

	return G->arDistance[u];
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

	// This is my old algorithm that did not work

	// // if u is less than the source
	// if(u < G->source)
	// {
		
	// 	// append(L, u);
	// 	prepend(L, u);
	// 	printf("u < G->source\n");
	// 	printList(stdout, L);
	// 	printf("\n");
	// }

					// Tuan Tran helped me figure this part out because I couldn't do it on my own

	// if u is the source of BFS()
	if(u == getSource(G))
	{
		append(L, u);
	    //append(L, u);
	}

	// appends to L the value NIL if no such path exists.
	else if(G->arParents[u] == NIL)
	{
		// printf("G->arParents[u] == NIL\n");
		// printf("G->arParents[%d] \n", u);
		//prepend(L, NIL);
		append(L, NIL);
		// printList(stdout, L);
		// printf("\n");
	}

	else
	{
		// printf("G->arParents[%d] %d\n", u, G->arParents[u]);
		getPath(L, G, G->arParents[u]);
		append(L, u);
		// append(L, u);
	}
}
										/*** Manipulation procedures ***/

// deletes all edges of G restoring it to its original (no edge) state.
void makeNull(Graph G)
{
	for(int i = 1; i <= G->order; i++)
	{
		clear(G->adjacencyList[i]);
		G->arColors[i] 	 = WHITE;
		G->arDistance[i] = NIL;
		G->arParents[i]  = INF;
	}

	G->size   = 0;
	G->source = NIL;
}

// inserts a new edge joining u to v, i.e u is added to the adjacency List
//  of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	// precondition: int arguments must lie in the range 1 to getOrder(G)
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on invalid arguments\n");
		exit(EXIT_FAILURE);
	}

	addArc(G, u, v);
	addArc(G, v, u); 
	G->size--; // I decrement here because I call addArc() twice which increments twice when it should only increment once
}

// inserts a new directed edge from u to v, i.e v is
// added to the adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}	

	// precondition: int arguments must lie in the range 1 to getOrder(G)
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on invalid arguments\n");
		exit(EXIT_FAILURE);
	}

	moveFront(G->adjacencyList[u]);

	// move to the end of the list
	while(index(G->adjacencyList[u]) > -1 && v > get(G->adjacencyList[u]))
	{
		moveNext(G->adjacencyList[u]);
	}

	if(index(G->adjacencyList[u]) == -1)
	{
		append(G->adjacencyList[u], v);
		G->size++;
	}
	else
	{
		insertBefore(G->adjacencyList[u], v);
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
		G->arColors[i] = WHITE; 							// 2. color[𝑥] = white
		G->arDistance[i] = INF; 							// 3. 𝑑[𝑥] = ∞
		G->arParents[i] = NIL; 								// 4. 𝑝[𝑥] = nil
	}

	G->arColors[s] = GRAY; 									// 5. color[𝑠] = gray // discover the source 𝑠
	G->arDistance[s] =  0; 									// 6. 𝑑[𝑠] = 0
	G->arParents[s] = NIL;		    						// 7. 𝑝[𝑠] = nil
	
	List Q = newList(); 									// 8. 𝑄 = ∅ // construct a new empty queue
	append(Q, s); 											// 9. Enqueue(𝑄, 𝑠)

	while(length(Q) > 0) 									// 10. while 𝑄 ≠ ∅
	{
		moveFront(Q);
		x = get(Q); 
		deleteFront(Q);										// 11. 𝑥 = Dequeue(𝑄)
		moveFront(G->adjacencyList[x]);
			
		while(index(G->adjacencyList[x]) != -1) 			// 12. for 𝑦 ∈ adj[𝑥]		
		{
			y = get(G->adjacencyList[x]);

			if(G->arColors[y] == WHITE) 			  	    // 13. if color[𝑦] == white // 𝑦 is undiscovered
			{
				G->arColors[y] = GRAY; 				   		// 14. color[𝑦] = gray // discover 𝑦
				G->arDistance[y] = G->arDistance[x] + 1; 	// 15. 𝑑[𝑦] = 𝑑[𝑥] + 1
				G->arParents[y] = x; 				   		// 16. 𝑝[𝑦] = 𝑥
				append(Q, y); 						   		// 17. Enqueue(𝑄, 𝑦)
			}
			moveNext(G->adjacencyList[x]); 
		}
		G->arColors[x] = BLACK;						   		// 18. color[𝑥] = black // finish 𝑥
	}

	freeList(&Q);
	Q = NULL;
}

							/*** Other operations ***/

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

	if(out == NULL) // Do I really need this if() check?
	{
		printf("out Error: calling printGraph() on an empty out reference\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out, "%d: ", i); 
		printList(out, G->adjacencyList[i]);
		fprintf(out, "\n");
	}
}