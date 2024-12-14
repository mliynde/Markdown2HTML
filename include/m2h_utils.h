#ifndef M2H_UTILS_H
#define M2H_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

void preprocess_html(FILE *file) {
	if (file == NULL) {
		fprintf(stderr, "Error opening file");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "<!DOCTYPE html>\n");
	fprintf(file, "<html>\n");
	fprintf(file, "<head>\n");
	fprintf(file, "<meta charset=\"UTF-8\">\n");
	fprintf(file, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
	fprintf(file, "<title>Markdown to HTML</title>\n");
	fprintf(file, "</head>\n");

	exit(EXIT_SUCCESS);
}

void postprocess_html(FILE *file) {
	if (file == NULL) {
		fprintf(stderr, "Error opening file");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "</html>\n");

	exit(EXIT_SUCCESS);
}

#endif // M2H_UTILS_H