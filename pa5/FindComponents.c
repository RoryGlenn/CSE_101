//-----------------------------------------------------------------------------
// FindComponents.c
// Test client file for Graph ADT
//-----------------------------------------------------------------------------


	// The client of your Graph module will be called FindComponents. It will take two command line arguments
	// giving the names of the input and output files respectively:

	// 		% FindComponents infile outfile

	// The main program FindComponents will do the following:

		// • Read the input file.
		// • Assemble a graph object G using newGraph() and addArc().
		// • Print the adjacency list representation of G to the output file.
		// • Run DFS on G and 𝐺𝑇, processing the vertices in the second call by decreasing finish times from the first call.
		// • Determine the strong components of G.
		// • Print the strong components of G to the output file in topologically sorted order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;
	//int n      		= 0;
	int lengthG 	= 0;
	int componentNum;
	int sccG;
	int sccGT = 0;
	char line[MAX_LEN];


	if(argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");

	if(in == NULL)
	{
		printf("Unable to read from input file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");

	if(out == NULL)
	{
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	// fgets( where to write to, max number of characters, where it should be writing from )	
	fgets(line, MAX_LEN, in);
	List list = newList();
	
	sscanf(line, "%d", &lengthG);


	Graph G = newGraph(lengthG);

	while( fgets( line, MAX_LEN, in ) != NULL )
	{
		int a = 0;
		int b = 0;
		sscanf(line, "%d %d", &a, &b);
		if(a == 0 && b == 0)
		{
			break;
		}
		//addEdge(G, a, b); 	 // OLD
		addArc(G, a, b); 		 // NEW
	}

	// puts all the vertices into a list
	for(int i = 1; i <= getOrder(G); i++)
	{
		append(list, i);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	DFS(G, list);
	Graph GT = transpose(G);	// GT is G transposed
	DFS(GT, list);	

	for(int i = 1; i <= getOrder(GT); i++)
	{
		if(getParent(GT, i) == NIL)
		{
			sccGT++;
		}

	}

	fprintf(out, "G contains %d strongly connected components:\n", sccGT);

	List *ListSCC = malloc( sizeof(List) * (sccGT + 1) );

	for(int i = 1; i <= sccGT; i++)
	{
		ListSCC[i] = newList();
	}

	sccG = 1;
	int listLength = length(list);
	int frontVal = front(list);

	for(int i = 1; i <= listLength -1; i++)
	{
		int temp = back(list);
		deleteBack(list);
		prepend(ListSCC[sccG], temp);
		if( getParent( GT, temp ) == NIL )
		{
			sccG++;
		}
	}

	prepend(ListSCC[sccG], frontVal);

	componentNum = 1;
	while( componentNum <= sccGT )
	{
		fprintf(out, "Component %d: ", componentNum);
		printList(out, ListSCC[componentNum]);
		fprintf(out, "\n");
		componentNum++;
	}

	freeGraph(&G);
	freeGraph(&GT);

	for(int i = 0; i <= sccGT; i++)
	{
		freeList(&ListSCC[i]);
	}

	freeList(&list);
	free(ListSCC);

    fclose(out);
	fclose(in);



	// // should i get rid if this stuff below?
	// while( fgets(line, MAX_LEN, in) != NULL)
	// {
	// 	int source = 0;		
	// 	int destination = 0;

	// 	sscanf(line, "%d %d", &source, &destination);

	// 	if(source == 0 && destination == 0)
	// 	{
	// 		break;
	// 	}

	// 	fprintf(out, "\n");

	// 	//BFS(G, source);
	// 	List L = newList();
	// 	getPath(L, G, destination);
	// 	int distance = getDist(G, destination);

	// 	fprintf( out, "The distance from %d to %d is ", source, destination ); // is it filling these values with random numbers???

	// 	if(distance == INF)
	// 	{
	// 		fprintf( out, "infinity\n" );
	// 	}
	// 	else
	// 	{
	// 		fprintf( out, "%d\n", distance );
	// 	}

	// 	if( front(L) == NIL )
	// 	{
	// 		fprintf( out, "No %d-%d path exists", source, destination );
	// 	}
	// 	else
	// 	{
	// 		fprintf( out, "A shortest %d-%d path is: ", source, destination );
	// 		printList(out, L);
	// 		fprintf(out, "\n");
	// 	}

	// 	freeList(&L);
	// }

	// fprintf(out, "\n");
	// freeGraph(&G);

	// fclose(out);
	// fclose(in);
	
	return 0;
}