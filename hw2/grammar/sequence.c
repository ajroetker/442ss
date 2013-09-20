#include "sequence.h"
#include <stdlib.h>

char *new(int len) {
  int i;
  char *str;
  str = (char *)malloc((len+1)*sizeof(char));
  for (i = 0; i <= len; i++) {
    str[i] = '\000';
  }
  return str;
}

char *copy(char *str) {
  int i;
  int len = length(str);
  char *cpy = new(len);
  for (i=0; i<len; i++) {
    cpy[i] = str[i];
  }
  cpy[i] = '\000';
  return cpy;
}

int length(char *str) {
  int i=0;
  while (str[i] != '\000') {
    i++;
  }
  return i;
}

char *append(char *src1, char *src2) {
  // *** YOUR CODE GOES HERE ***
  return NULL;
}

char *substring(char *src, int start, int end) {
  int i;
  int len = end-start+1;
  char *dst = new(len);

  for (i=start; i<=end; i++) {
    dst[i-start] = src[i];    
  }
  dst[len] = '\000';

  return dst;
}


