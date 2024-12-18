#ifndef M2H_UTILS_H
#define M2H_UTILS_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_header(const char *line);
void preprocess_html(FILE *outfile, const char *file);
void convert_header_to_html(FILE *outfile, const char *line);

#endif // M2H_UTILS_H