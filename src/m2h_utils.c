#include "../include/m2h_utils.h"

void preprocess_html(FILE *outfile, const char *file) {
    fprintf(outfile, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>%s</title>\n</head>\n<body>\n", file);
}

int is_header(const char *line) {
    return line[0] == '#';
}

void convert_header_to_html(FILE *outfile, const char *line) {
    int level = 0;
    while (line[level] == '#') {
        level++;
    }
    fprintf(outfile, "<h%d>%s</h%d>\n", level, line + level + 1, level);
}