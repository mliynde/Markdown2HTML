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

	int converting_table = 0;
	while (fgets(line, sizeof(line), infile)) {
		line[strcspn(line, "\n")] = '\0';

		if (converting_table) {
			if (!is_table_row(line)) {
				fprintf(outfile, "</table>\n");
				converting_table = 0;
			}
		}

		if (line[0] == '\0') {
			fprintf(outfile, "<p>&nbsp;</p>\n");
		}
		else if (is_header(line)) {	// 处理标题
			convert_header_to_html(outfile, line);
		}
		else if (is_table_row(line)) {	// 处理表格
			if (!converting_table) {
				fprintf(outfile, "<table>\n");
				converting_table = 1;
				convert_bold_table_row_to_html(outfile, line);
			}
			else {
				if (!is_table_separator(line)) {
					convert_table_row_to_html(outfile, line);
				}
			}
		}
		else {
			converting_table = 0;
			fprintf(outfile, "<p>%s</p>\n", line);
		}
	}

	fprintf(outfile, "</body>\n</html>\n");

	fclose(infile);
	fclose(outfile);
}