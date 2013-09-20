#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequence.h"

// MATH 442: grammar
//
// Grammar production engine.
//

// readLine
//
// Reads a line of text from a file, places characters
// into the contents of "line."
//
void readLine(FILE *f, char *line) {
  char c;
  int i=0;
  while ((c = fgetc(f)) != '\n') {
    line[i] = c;
    i++;
  }
  line[i] = '\000';
}

// readGrammar
//
// Reads an input file consisting of grammar productions.
// First line gives the number of productions, and the
// remaining lines are productions of the form 
//      A->wxyz
// where A is any uppercase letter and wxyz is a string
// of upper- and lower-case letters.
//
// Sets the contents of the pointer "lines" equal to
// the number of productions in the file.
//
// Returns an array of the production line strings.
//
char **readGrammar(FILE *f, int *lines) {
  int l;
  char line[80];
  char **grammar;

  // read the number of lines
  fscanf(f,"%d\n",lines);
  // create the array of productions
  grammar = (char **)malloc((*lines)*sizeof(char *));

  // read each production line
  for (l = 0; l < (*lines); l++) {
    readLine(f,line);
    grammar[l] = copy(line);
  }

  return grammar;
}

// production
//
// Chooses a random production from an array of productions
// given by G, those whose left-hand side is the character A.
//
char *production(char A, char **G, int lines) {
  int start, end;
  int p;
  // find the starting line of A-productions
  for (start = 0; start < lines && G[start][0] != A; start++);
  // find the line following the A-productions
  for (end=start; end<lines && G[end][0] == A; end++);
  // pick a line in that range 
  p = rand() % (end - start) + start;
  // return its right-hand side 
  return substring(G[p],3,length(G[p]));
}

// hasUpper
//
// Returns whether a string has an uppercase letter.
//
int hasUpper(char *s) {
  int i;
  int len = length(s);
  for (i = 0; i < len; i++) {
    if (isupper(s[i])) {
      return 1;
    }
  }
  return 0;
}

// replaceAll
//
// Given a string s of lower- and uppercase letters, replace
// all the uppercase letters with thr right-hand sides of 
// one of their productions in G (using "production" procedure
// above).  
//
char *replaceAll(char *s, char **G, int n) {
  //
  // *** YOUR CODE GOES HERE, use your append ***
  //
  return NULL;
}

int main(int argc, char **argv) {

  FILE *gf;
  char **G;
  char *x;
  int notDone;
  int n;

  srand(time(NULL));
  if (argc < 3) {

    return -1;

  } else {

    gf = fopen(argv[1],"r");
    G = readGrammar(gf,&n);
    x = argv[2];

    printf("%s\n",x);
    while (hasUpper(x)) {
      x = replaceAll(x,G,n);
      printf("=>%s\n",x);
    };

    return 0;
  }
}
