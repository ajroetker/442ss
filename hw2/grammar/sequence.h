#ifndef _SEQUENCE_H
#define _SEQUENCE_H

char *new(int len);
char *copy(char *str);
int length(char *str);
char *append(char *src1, char *src2);
char *substring(char *src, int start, int end);

#endif
