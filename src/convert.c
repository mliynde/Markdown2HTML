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

	// fprintf(stdout, "1\n");

	if (infile == NULL) {
		fprintf(stderr, "Error opening file %s\n", input_file);
		exit(EXIT_FAILURE);
	}
	if (outfile == NULL) {
		fprintf(stderr, "Error opening file %s\n", output_file);
		exit(EXIT_FAILURE);
	}

	preprocess_html(outfile, input_file);

	// fprintf(stdout, "2\n");

	int converting_table = 0;
	int converting_codespan = 0;
	int converting_blockquote = 0;
	int converting_list = 0;
	int converting_list_item = 0;

	int md_line_cnt = 0;

	while (fgets(line, sizeof(line), infile)) {
		fprintf(stdout, "line %d read\n", ++md_line_cnt);

		line[strcspn(line, "\n")] = '\0';

		if (converting_table) {
			if (!is_table_row(line)) {
				fprintf(outfile, "</table>\n");
				converting_table = 0;
			}
		}
		if (converting_codespan) {	// 所谓line54
			if (is_code_block(line)) {
				fprintf(outfile, "</code></pre>\n");
				converting_codespan = 0;
				continue;
			}
			else {
				char *buffer = (char *)malloc(MAX_LINE_LENGTH * 2);
				strcpy(buffer, line);

				replace_special_chars(buffer); // declared in m2h_utils.c

				fprintf(outfile, "%s\n", buffer);
				free(buffer);

				continue;
			}
		}

		// fprintf(stdout, "pass\n", md_line_cnt);

		if (line[0] == '\0') {
			// fprintf(outfile, "<p>&nbsp;</p>\n");
		}
		else if (is_html_comment(line)) {	// 处理html注释
			fprintf(outfile, "%s\n", line);
		}
		else if (is_header(line)) {	// 处理标题
			convert_header_to_html(outfile, line);
		}
		else if (is_code_block(line)) { // 处理代码块
			if (!converting_codespan) {
				fprintf(outfile, "<pre><code>\n"); // 尚未指定代码块语言
				converting_codespan = 1;
			}
			// else 部分见 line54
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
			convert_para_to_html(outfile, line);
		}
	}

	fprintf(outfile, "</body>\n</html>\n");

	fprintf(stdout, "Successfully generated HTML file in %s", output_file);

	fclose(infile);
	fclose(outfile);
}