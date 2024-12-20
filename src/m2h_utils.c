#include "../include/m2h_utils.h"

#include "m2h_judge.c"
#include "styles.c"

void preprocess_html(FILE *outfile, const char *file) {
	fprintf(outfile, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<title>%s</title>\n</head>\n<body>\n", file);
}

// 标题

void convert_header_to_html(FILE *outfile, const char *line) {
	int level = 0;
	while (line[level] == '#') {
		level++;
	}
	fprintf(outfile, "<h%d>%s</h%d>\n", level, line + level + 1, level);
}

// 表格（TODO：添加表格样式，普通边框，表头背景色）

void convert_table_row_to_html(FILE *outfile, const char *line) {
    fprintf(outfile, "  <tr>\n");

    char *line_copy = strdup(line);
    if (line_copy == NULL) {
        fprintf(stderr, "Convert Table: Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line_copy, "|");
    while (token) {
        fprintf(outfile, "    <td>%s</td>\n", token);
        token = strtok(NULL, "|");
    }
    fprintf(outfile, "  </tr>\n");

    free(line_copy);
}

void convert_bold_table_row_to_html(FILE *outfile, const char *line) {
    fprintf(outfile, "  <tr>\n");
    
    char *line_copy = strdup(line);
    if (line_copy == NULL) {
        fprintf(stderr, "Convert Table: Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line_copy, "|");
    while (token) {
        fprintf(outfile, "    <th>%s</th>\n", token);
        token = strtok(NULL, "|");
    }
    fprintf(outfile, "  </tr>\n");

    free(line_copy);
}