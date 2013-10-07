#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//
// MATH 442 : graph
//
// Graph traversal program.
//

// readGraph
//
// Reads a text file that describes the
// edge adjacency structure of a graph.
//
// The format is
//
//    (# of vertices)
//    (#neighbors of 0) n1 n2 n3 ...
//    (#neighbors of 1) ...
//    ...
//
// The vertices are named 0, 1, 2, ... n-1.
//
// For an example, consider the following
// 3x4 "grid graph"
//
//   ( 0) -- ( 3) -- ( 6) -- ( 9)
//     |       |       |       |
//   ( 1) -- ( 4) -- ( 7) -- (10)
//     |       |       |       |
//   ( 2) -- ( 5) -- ( 8) -- (11)
//
// It would be given by the file 
// 
// 12
// 2 3 1
// 3 0 4 2
// 2 1 5
// 3 0 4 6
// 4 1 3 5 7
// 3 2 4 8
// 3 3 7 9
// 4 4 6 8 10
// 3 5 7 11
// 2 6 10
// 3 7 9 11
// 2 8 10
//
// For example, in the second line we have
// "2 3 1" because vertex 0 has two neighbors
// vertex 3 and vertex 1.
//
// This function sets the contents of "np" to
// be the number of vertices, and builds an 
// array of edge lists.  Each edge list g[i] 
// an array of integers (the neighbors of i)
// terminated with -1.
//
// The edge list is returned by readGraph.
//
int **readGraph(FILE *f, int *np) {
  int **graph;
  int e,v;
  int i,j;

  // read the number of vertices
  fscanf(f,"%d\n",np);

  // create the array of edges
  graph = (int **)malloc((*np)*sizeof(int *));
  
  // read each adjacency list
  for (i = 0; i < (*np); i++) {
    // size of the list
    fscanf(f,"%d",&e);
    graph[i] = (int *)malloc((e+1)*sizeof(int));
    // endpoints of edges
    for (j = 0; j < e; j++) {
      fscanf(f,"%d",&graph[i][j]);
    }
    graph[i][j] = -1;
  }

  return graph;
}

// dfs
//
// Performs a stack-based depth-first search of the
// graph provided by the adjacency lists in G.  The
// initial seed vertex is given by s.  
//
// Returns the edges of the DFS tree as an array
// "from", where (i,from[i]) gives each edge.  These
// are only valid when from[i] is non-negative and not 
// equal to i.  from[i]=(-1) means that i is not
// reachable from s.  from[s] = s.
//
int *dfs(int s, int **G, int n) {
  int u,v,a;
  int *from;
  int *S;

  // clear "from" marks
  from = (int *)malloc(n * sizeof(int));
  for (v = 0; v < n; v++) {
    from[v] = -1;
  }

  // initialize DFS stack with seed vertex s
  S = newStack(n);
  push(s,S);
  from[s] = s;

  for (v = 0; v < n; v++) {
    printf("f[%d]:%d\n",v,from[v]);
  }

  // search until stack is empty
  while (!isEmpty(S)) {
    // grab next vertex to explore from
    u = pop(S);

    // for each of u's neighbors v
    for (a=0; G[u][a] != -1; a++) {

      v = G[u][a];
      printf("%d>%d\n",u,v);
      // if v is not on the stack, mark its "from" as u
      if (from[v] == -1) {
	printf("%d -> %d\n",u,v);
	from[v] = u;
	push(v,S);
	output(S);
      } 
    }
  }
  return from;
}

// usage
//
// Directs the user of this program.
void usage(char *cmd, char *fname) {
  if (fname) {
    fprintf(stderr,"Error! Unable to open file named '%s.'\n",fname);
  } else {
    fprintf(stderr,"Error! Missing input file argument.\n");
  }
  fprintf(stderr,"usage: %s <graph file>\n",cmd);
  fprintf(stderr,"\twhere <graph file> is the name of a text file\n");
  fprintf(stderr,"\tdescribing the adjacency structure of a graph.\n");
}

//
// graph
//
// Program reads a text file that describes a graph.  It
// then performs a depth-first search of the graph from 
// the graph's 0 vertex, and reports the edges in the 
// DFS tree.
//
int main(int argc, char **argv) {
  FILE *gf;
  int **G, n, i, *pred;
  int some = 0;

  if (argc < 2) {

    usage(argv[0],NULL);
    return -1;

  } else {

    gf = fopen(argv[1],"r");
    if (gf == NULL) {
      usage(argv[0],argv[1]);
      return -1;
    }

    // read the graph file
    G = readGraph(gf,&n);

    // perform the search
    pred = dfs(0,G,n);

    // report the DFS tree
    printf("{");
    for (i=1; i<n; i++) {
      if (pred[i] >= 0) {
	if (some) {
	  printf(",");
	} 
	printf("(%d,%d)",i,pred[i]);
	some = 1;
      }
    }
    printf("}\n");

    return 0;
  }
}
