#ifndef CONVERT_H
#define CONVERT_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 2048
#endif // MAX_LINE_LENGTH

void convert_markdown_to_html(const char *input_file);

#endif // CONVERT_H