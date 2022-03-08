#ifndef _UTILITIES_HEADER_
#define _UTILITIES_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printn(char *string, int n);

void fprintn(FILE *file, char *string, int n);

int PatternInString(char *string, char *pattern);

#endif
