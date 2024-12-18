#include "../include/convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "m2h_utils.c"
#include "gettime.c"

void convert_markdown_to_html(const char *input_file) {
    char output_file[MAX_LINE_LENGTH];
    char datetime[20];
    get_current_datetime(datetime, sizeof(datetime));
    snprintf(output_file, sizeof(output_file), "Output_%s.html", datetime);

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

    preprocess_html(outfile, input_file);
    
    while (fgets(line, sizeof(line), infile)) {
        line[strcspn(line, "\n")] = '\0';

        if (is_header(line)) {
            convert_header_to_html(outfile, line);
        } else {
            fprintf(outfile, "<p>%s</p>\n", line);
        }
    }

    fprintf(outfile, "</body>\n</html>\n");

    fclose(infile);
    fclose(outfile);
}