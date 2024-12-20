#ifndef M2H_UTILS_H
#define M2H_UTILS_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void preprocess_html(FILE *outfile, const char *file); // 为html文件添加头部信息

void convert_header_to_html(FILE *outfile, const char *line); // 将markdown标题转换为html标题

void convert_table_row_to_html(FILE *outfile, const char *line); // 将markdown表格行转换为html表格行

void convert_bold_table_row_to_html(FILE *outfile, const char *line); // 将markdown加粗行转换为html加粗行

#endif // M2H_UTILS_H