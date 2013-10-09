#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequence.h"

// MATH 442: grammar
//
// Grammar production engine.
//

typedef struct _grammar {
  char ** productions;
  int lines;
} grammar;

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
grammar * readGrammar(FILE *f) {
  int l;
  char line[80];
  grammar * G = (grammar *)malloc(sizeof(grammar));

  // read the number of lines
  fscanf(f,"%d\n",&(G->lines));
  // create the array of productions

  G->productions = (char **)malloc((G->lines)*sizeof(char *));
  // read each production line
  for (l = 0; l < G->lines; l++) {
    readLine(f,line);
    G->productions[l] = copy(line);
  }

  return G;
}

// production
//
// Chooses a random production from an array of productions
// given by G, those whose left-hand side is the character A.
//
char *production(char A, grammar *G) {
  int start, end;
  int p;
  // find the starting line of A-productions
  for (start = 0; start < G->lines && G->productions[start][0] != A; start++);
  // find the line following the A-productions
  for (end=start; end< G->lines && G->productions[end][0] == A; end++);
  // pick a line in that range
  p = rand() % (end - start) + start;
  // return its right-hand side
  return substring(G->productions[p],3,length(G->productions[p]));
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
char *replaceAll(char *s, grammar *G) {
  int i;
  char *front, *middle, *back;
  int len = length(s);
  for(i = 0; i < len; i++){
    if (isupper(s[i])) {
      front = substring(s, 0, i - 1);
      middle = production(s[i], G);
      back = replaceAll(substring(s, i + 1, len-1), G);
      s = append(append(front, middle), back);
      break;
    }
  }
  return s;
}

int main(int argc, char **argv) {

  FILE *gf;
  grammar *G;
  char *x;
  int notDone;
  int n;

  srand(time(NULL));
  if (argc < 3) {

    printf("Too few arguments!\n");
    return -1;

  } else {

    gf = fopen(argv[1],"r");
    G = readGrammar(gf);
    x = argv[2];

    printf("%s\n",x);
    while (hasUpper(x)) {
      x = replaceAll(x,G);
      printf("=>%s\n",x);
    };

    return 0;
  }
}
