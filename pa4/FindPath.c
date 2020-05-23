//-----------------------------------------------------------------------------
// FindPath.c
// Test client file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char* argv[])
{
	int a = 4;
	for (int i = 0; i <= 2534; i++)
	{
		printf("The value of a is: %d\n", a);

		a++;
	}





	// FILE *in;
	// FILE *out;
	// char line[MAX_LEN];

	// if(argc != 3)
	// {
	// 	printf("Usage: %s <input file> <output file>\n", argv[0]);
	// 	exit(EXIT_FAILURE);
	// }

	// in = fopen(argv[1], "r");

	// if(in == NULL)
	// {
	// 	printf("Unable to read from input file %s\n", argv[1]);
	// 	exit(EXIT_FAILURE);
	// }

	// out = fopen(argv[2], "w");

	// if(out == NULL)
	// {
	// 	printf("Unable to write to file %s\n", argv[2]);
	// 	exit(EXIT_FAILURE);
	// }

	// // fgets( where to write to, max number of characters, where it should be writing from )	
	// fgets(line, MAX_LEN, in);

	// int length = 0;
	// sscanf(line, "%d", &length);

	// Graph G = newGraph(length);

	// while(fgets(line, MAX_LEN, in) != NULL)
	// {
	// 	int a = 0;
	// 	int b = 0;
	// 	sscanf(line, "%d %d", &a, &b);
	// 	if(a == 0 && b == 0)
	// 	{
	// 		break;
	// 	}
	// 	addEdge(G, a, b);
	// }

	// printGraph(out, G);

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

	// 	BFS(G, source);
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