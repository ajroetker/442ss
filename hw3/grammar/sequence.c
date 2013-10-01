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
  int i=0, j=0;
  int len = length(src1)+length(src2);
  char *out = new(len);
  while (src1[i] != '\000'){
    out[i] = src1[i];
    i++;
  }
  while (src2[j] != '\000'){
    out[i] = src2[j];
    j++;
    i++;
  }
  out[len] = '\000';
  free(src1);
  free(src2);
  return out;
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


