#ifndef M2H_JUDGE_H
#define M2H_JUDGE_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_header(const char *line); // 判断当前markdown行是否为标题

int is_table_row(const char *line); // 判断当前markdown行是否为表格行

int is_table_separator(const char *line); // 判断当前markdown行是否为表格分隔符

int is_code_block(const char *line); // 判断当前markdown行是否为代码块

int is_html_comment(const char *line); // 判断当前markdown行是否为html注释

#endif // M2H_JUDGE_H