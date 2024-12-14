#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/m2h_utils.h"

#define MAX_LINE_LENGTH 2048

void convert_markdown_to_html(const char *input_file, const char *output_file) {
	FILE *infile = fopen(input_file, "r");
	FILE *outfile = fopen(output_file, "w");
	char line[MAX_LINE_LENGTH];

	if (infile == NULL) {
		fprintf(stderr, "Error opening file %s\n", input_file);
		exit(EXIT_FAILURE);
	}
	if (outfile == NULL) {
		fprintf(stderr, "Error opening file %s\n", output_file);
		exit(EXIT_FAILURE);
	}

	preprocess_html(outfile);
	
	postprocess_html(outfile);
	
	fclose(infile);
	fclose(outfile);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
		return 1;
	}

	convert_markdown_to_html(argv[1], argv[2]);

	return 0;
}