#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 2048

void replace_all(char *str, const char *old, const char *new) {
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
}

void convert_para_to_html(FILE *outfile, const char *file) {
    char buffer[4096];
    strcpy(buffer, file);

    // 替换粗体标记
    replace_all(buffer, "**", "<b>");
    replace_all(buffer, "__", "<b>");
    replace_all(buffer, "</b>", "</b>");

    // 替换斜体标记
    replace_all(buffer, "*", "<i>");
    replace_all(buffer, "_", "<i>");
    replace_all(buffer, "</i>", "</i>");

    // 替换删除线标记
    replace_all(buffer, "~~", "<s>");
    replace_all(buffer, "</s>", "</s>");

	// 替换行内代码标记
	replace_all(buffer, "`", "<code>");
	replace_all(buffer, "</code>", "</code>");

    fprintf(outfile, "<p>%s</p>\n", buffer);
}

int main(){
	FILE *infile = fopen("test.md", "r");
	char line[4096];
	while (fgets(line, sizeof(line), infile)) {
		line[strcspn(line, "\n")] = '\0';
		convert_para_to_html(stdout, line);
	}
}