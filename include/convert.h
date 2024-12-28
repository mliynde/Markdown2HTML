#ifndef CONVERT_H
#define CONVERT_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

#ifndef MAX_LIST_LEVEL
#define MAX_LIST_LEVEL 10
#endif // MAX_LIST_LEVEL

#ifndef ORDERED
#define ORDERED 1
#endif // ORDERED

#ifndef UNORDERED
#define UNORDERED 2
#endif // UNORDERED

void repeat_text(int cnt, char *text, FILE *outfile);

int max_num(int a, int b);

int get_list_level(int type, int pos, int a[]);

void convert_markdown_to_html(const char *input_file);

#endif // CONVERT_H