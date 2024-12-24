#include "../include/m2h_utils.h"

#include "m2h_judge.c"
#include "styles.c"

void preprocess_html(FILE *outfile, const char *file) {
	fprintf(outfile, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<title>%s</title>\n</head>\n<body>\n", file);
}

// para
// 统一内容输出
// 替换特殊字符，包括：&，<，>，"，'，避免与html语法冲突
// 粗斜体块，粗体块，斜体块，删除线块，行内代码块
// （TODO）判定markdown段落

int replace_all(char *str, const char *old, const char *new) {
    char *pos, temp[MAX_LINE_LENGTH * 2];
    int index = 0;
    int old_len = strlen(old);

    while ((pos = strstr(str, old)) != NULL) {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, new);
        strcat(str, temp + index + old_len);
    }
    return index != 0;
}

int replace_once(char *str, const char *old, const char *new) {
    char *pos = strstr(str, old);
    if (pos != NULL) {
        char temp[MAX_LINE_LENGTH * 2];
        strcpy(temp, str);
        int index = pos - str;
        str[index] = '\0';
        strcat(str, new);
        strcat(str, temp + index + strlen(old));
    }
    return pos != NULL;
}

void replace_special_chars(char *str) {
    replace_all(str, "&", "&amp;");
    replace_all(str, "<", "&lt;");
    replace_all(str, ">", "&gt;");
    replace_all(str, "\"", "&quot;");
    replace_all(str, "'", "&apos;");
}

void convert_para_to_html(FILE *outfile, const char *file) {
    char buffer[MAX_LINE_LENGTH * 2];
    strcpy(buffer, file);

    replace_special_chars(buffer);

    const char *replacements[][2] = {
        {"***", "<b><i>"}, {"___", "<b><i>"},
        {"**", "<b>"}, {"__", "<b>"},
        {"*", "<i>"}, {"_", "<i>"},
        {"~~", "<s>"},
        {"`", "<code>"}
    };

    const char *end_replacements[][2] = {
        {"***", "</i></b>"}, {"___", "</i></b>"},
        {"**", "</b>"}, {"__", "</b>"},
        {"*", "</i>"}, {"_", "</i>"},
        {"~~", "</s>"},
        {"`", "</code>"}
    };

    int len_replacements = sizeof(replacements) / sizeof(replacements[0]);
    int len_end_replacements = sizeof(end_replacements) / sizeof(end_replacements[0]);

	if (len_replacements != len_end_replacements) {
		fprintf(stderr, "Convert Para: Replacement arrays have different lengths\n");
	}
	else{
		for (int i = 0; i < len_replacements; i++) {
			while(1){
				if (!replace_once(buffer, replacements[i][0], replacements[i][1])) {
					break;
				}
				if (!replace_once(buffer, end_replacements[i][0], end_replacements[i][1])) {
					break;
				}
			}
		}
	}

	fprintf(outfile, "<p>%s</p>\n", buffer);
}

// end of para

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

void convert_contents_to_html(FILE *outfile, const char *line) {

}