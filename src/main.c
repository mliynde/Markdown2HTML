#include <stdio.h>
#include <stdlib.h>

#include "convert.c"

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "Markdown2HTML"
#endif // PROGRAM_NAME

#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION "beta v1.0.0"
#endif // PROGRAM_VERSION

#ifndef PROGRAM_AUTHOR
#define PROGRAM_AUTHOR "Lighte"
#endif // PROGRAM_AUTHOR

int main(int argc, char *argv[]) {
	clock_t main_start_time = clock();

	fputs("This is an experimental work of USTC Programming subject, which is open source.\n", stdout);
	fputs("This program is used to convert Markdown file to HTML file, supporting most of the basic Md grammars.\n", stdout);
	fprintf(stdout, "Program Name: %s\n", PROGRAM_NAME);
	fprintf(stdout, "Program Version: %s\n", PROGRAM_VERSION);
	fprintf(stdout, "Program Author: %s\n\n", PROGRAM_AUTHOR);

	if (argc == 1) {
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		fprintf(stderr, "Example (for Windows Terminal):\n %s test.md\n", argv[0]);
		fprintf(stderr, "Also supports dragging files to the program.\n");
		fprintf(stdout, "Press any key to exit...");
		getchar();
		return 1;
	}

	for(int i=1; i<argc; ++i){
		fprintf(stdout, "Converting %s to HTML...\n", argv[i]);
		convert_markdown_to_html(argv[i]);
	}

	clock_t main_end_time = clock();
	double main_elapsed_time = (double)(main_end_time - main_start_time) / CLOCKS_PER_SEC;
	fprintf(stdout, "All tasks completed in %.3f seconds.\n", main_elapsed_time);

	fprintf(stdout, "Press any key to exit...");
	getchar();
	return 0;
}