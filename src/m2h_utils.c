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

int find_once(char *str, const char *tofind) {
	char *pos = strstr(str, tofind);
	if (pos != NULL) {
		return pos - str; // 返回找到的子字符串的位置
	}
	return -1; // 如果未找到，返回 -1
}

int replace_all(char *str, const char *old, const char *newstr) {
	char *pos;
	char *temp = (char *)malloc(MAX_LINE_LENGTH * 2);
	int index = 0;
	int old_len = strlen(old);
	int new_len = strlen(newstr);
	int replaced = 0;

	while ((pos = strstr(str + index, old)) != NULL) {
		strcpy(temp, pos + old_len);
		index = pos - str;
		str[index] = '\0';
		strcat(str, newstr);
		strcat(str, temp);
		index += new_len; // fixed
		replaced++;
	}

	free(temp);
	return replaced;
}

int replace_once(char *str, const char *old, const char *newstr) {
	char *pos = strstr(str, old);
	if (pos != NULL) {
		char *temp = (char *)malloc(MAX_LINE_LENGTH * 2);
		strcpy(temp, str);
		int index = pos - str;
		str[index] = '\0';
		strcat(str, newstr);
		strcat(str, temp + index + strlen(old));
		free(temp);
	}
	return pos != NULL;
}

int insert_all(char *str, const char *old, const char *instr) {
	char *buffer = (char *)malloc(MAX_LINE_LENGTH * 2);
	char *pos = str;
	int old_len = strlen(old);
	int instr_len = strlen(instr);
	int inserted = 0;

	while ((pos = strstr(pos, old)) != NULL) {
		strcpy(buffer, pos + old_len);
		strcpy(pos + old_len, instr);
		strcat(pos + old_len + instr_len, buffer);
		pos += old_len + instr_len;
		inserted++;
	}

	free(buffer);
	return inserted;
}

void replace_special_chars(char *str) {
	insert_all(str, "&", "amp;");
	replace_all(str, "<", "&lt;");
	replace_all(str, ">", "&gt;");
	replace_all(str, "\"", "&quot;");
	replace_all(str, "'", "&apos;");
}

void convert_markdown_links(char *str){ // 使用前需先调用replace_special_chars
	char *pos = str;
	while ((pos = strstr(pos, "[")) != NULL) {
		char *end_text = strstr(pos, "]");
		if (end_text && *(end_text + 1) == '(') {
			char *end_link = strstr(end_text + 2, ")");
			if (end_link) {
				// 提取链接文本和链接地址
				int text_len = end_text - pos - 1;
				int link_len = end_link - end_text - 2;
				char *text = (char *)malloc(text_len + 1);
				char *link = (char *)malloc(link_len + 1);
				strncpy(text, pos + 1, text_len);
				text[text_len] = '\0';
				strncpy(link, end_text + 2, link_len);
				link[link_len] = '\0';

				int html_len = text_len + link_len + 15;
				char *html_link = (char *)malloc(html_len + 1);
				snprintf(html_link, html_len + 1, "<a href=\"%s\">%s</a>", link, text);

				int remaining_len = strlen(end_link + 1);
				memmove(pos + strlen(html_link), end_link + 1, remaining_len + 1);
				strncpy(pos, html_link, strlen(html_link));

				pos += strlen(html_link);

				free(text);
				free(link);
				free(html_link);
			} else {
				pos++;
			}
		} else {
			pos++;
		}
	}
	// 处理另一种写法的链接
	pos = str;
	while ((pos = strstr(pos, "&lt;http")) != NULL) {
		char *end_link = strstr(pos, "&gt;");
		if (end_link) {
			int link_len = end_link - pos - 4; // 4 is the length of "&lt;"
			char *link = (char *)malloc(link_len + 1);
			strncpy(link, pos + 4, link_len);
			link[link_len] = '\0';

			// Create HTML link
			int html_len = link_len + 15;
			char *html_link = (char *)malloc(html_len + 1);
			snprintf(html_link, html_len + 1, "<a href=\"%s\">%s</a>", link, link);

			int remaining_len = strlen(end_link + 4); // 4 is the length of "&gt;"
			memmove(pos + strlen(html_link), end_link + 4, remaining_len + 1);
			strncpy(pos, html_link, strlen(html_link));

			pos += strlen(html_link);

			free(link);
			free(html_link);
		} else {
			pos++;
		}
	}
}

void convert_markdown_images(char *str){
	char *pos = str;
	while ((pos = strstr(pos, "![")) != NULL) {
		char *end_text = strstr(pos, "]");
		if (end_text && *(end_text + 1) == '(') {
			char *end_link = strstr(end_text + 2, ")");
			if (end_link) {
				// 提取图片文本和图片地址
				int text_len = end_text - pos - 2;
				int link_len = end_link - end_text - 2;
				char *text = (char *)malloc(text_len + 1);
				char *link = (char *)malloc(link_len + 1);
				strncpy(text, pos + 2, text_len);
				text[text_len] = '\0';
				strncpy(link, end_text + 2, link_len);
				link[link_len] = '\0';

				int html_len = text_len + link_len + 30;
				char *html_link = (char *)malloc(html_len + 1);
				snprintf(html_link, html_len + 1, "<img src=\"%s\" alt=\"%s\">", link, text);

				int remaining_len = strlen(end_link + 1);
				memmove(pos + strlen(html_link), end_link + 1, remaining_len + 1);
				strncpy(pos, html_link, strlen(html_link));

				pos += strlen(html_link);

				free(text);
				free(link);
				free(html_link);
			} else {
				pos++;
			}
		} else {
			pos++;
		}
	}
}

void convert_formats(char *str){
	char *head = str;

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
	const int INLINE_CODE_PLACE = 7;

	int len_replacements = sizeof(replacements) / sizeof(replacements[0]);
	int len_end_replacements = sizeof(end_replacements) / sizeof(end_replacements[0]);
	if (len_replacements != len_end_replacements) {
		fprintf(stderr, "Convert Para: Replacement arrays have different lengths\n");
		exit(EXIT_FAILURE);
	}

	int match_start[REPLACEMENT_COUNT] = {0};

	int in_inline_code = 0;

	while (*str) {
		int replaced = 0;

		for (int i = 0; i < len_replacements; i++) {
			int rep_len = strlen(replacements[i][0]);
			int end_rep_len = strlen(end_replacements[i][0]);

			if (!in_inline_code && !match_start[i] && strncmp(str, replacements[i][0], rep_len) == 0) {
				// 查找匹配
				const char *end_pos = strstr(str + rep_len, end_replacements[i][0]);
				if (end_pos) {
					if (replace_once(str, replacements[i][0], replacements[i][1])) {
						str += rep_len;
						match_start[i] = 1;
						replaced = 1;

						if(i == INLINE_CODE_PLACE){
							in_inline_code = 1;
						}

						break;
					}
					else {
						fprintf(stderr, "Convert Formats: Found %s but failed to replace it to %s .\n", replacements[i][0], replacements[i][1]);
						exit(EXIT_FAILURE);
					}
				}
			
			} else if (match_start[i] && strncmp(str, end_replacements[i][0], end_rep_len) == 0) {
				if (replace_once(str, end_replacements[i][0], end_replacements[i][1])) {
					str += end_rep_len;
					match_start[i] = 0;
					replaced = 1;

					if(i == INLINE_CODE_PLACE){
						in_inline_code = 0;
					}

					break;
				}
				else {
					fprintf(stderr, "Convert Formats: Found %s but failed to replace it to %s .\n", end_replacements[i][0], end_replacements[i][1]);
					exit(EXIT_FAILURE);
				}
			}
		}

		if (!replaced) {
			str++;
		}
	}
	str = head;
}

void convert_content_to_html(FILE *outfile, const char *file) {
	char *file_copy = (char *)malloc(MAX_LINE_LENGTH * 2);
	strcpy(file_copy, file);
	replace_special_chars(file_copy);

	convert_markdown_images(file_copy);
	convert_markdown_links(file_copy);

	convert_formats(file_copy);

	fprintf(outfile, "%s", file_copy);
	free(file_copy);
}

void convert_para_to_html(FILE *outfile, const char *file) {
	fprintf(outfile, "<p>");
	convert_content_to_html(outfile, file);
	fprintf(outfile, "</p>\n");
}


// end of para

// 标题

void convert_header_to_html(FILE *outfile, const char *line) {
	int level = 0;
	while (line[level] == '#') {
		level++;
	}
	fprintf(outfile, "<h%d>", level);
	convert_content_to_html(outfile, line + level + 1);
	fprintf(outfile, "</h%d>\n", level);
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
		fprintf(outfile, "	<td>");
		convert_content_to_html(outfile, token);
		fprintf(outfile, "</td>\n");
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
		fprintf(outfile, "	<th>");
		convert_content_to_html(outfile, token);
		fprintf(outfile, "</th>\n");
		token = strtok(NULL, "|");
	}
	fprintf(outfile, "  </tr>\n");

	free(line_copy);
}
