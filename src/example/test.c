#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void convert_markdown_to_html(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    FILE *outfile = fopen(output_file, "w");
    char line[MAX_LINE_LENGTH];

    if (infile == NULL || outfile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), infile)) {
        // Convert headers
        if (strncmp(line, "# ", 2) == 0) {
            fprintf(outfile, "<h1>%s</h1>\n", line + 2);
        } else if (strncmp(line, "## ", 3) == 0) {
            fprintf(outfile, "<h2>%s</h2>\n", line + 3);
        } else if (strncmp(line, "### ", 4) == 0) {
            fprintf(outfile, "<h3>%s</h3>\n", line + 4);
        } else {
            // Convert paragraphs
            fprintf(outfile, "<p>%s</p>\n", line);
        }
    }

    fclose(infile);
    fclose(outfile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    convert_markdown_to_html(argv[1], argv[2]);

    return EXIT_SUCCESS;
}