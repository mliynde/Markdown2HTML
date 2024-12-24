#include "..\include\m2h_judge.h"

int is_header(const char *line) {
	return line[0] == '#';
}

int is_table_row(const char *line) {
	const char *first_pipe = strchr(line, '|');
	if (first_pipe == NULL) {
		return 0;
	}
	const char *second_pipe = strchr(first_pipe + 1, '|');
	if (second_pipe == NULL) {
		return 0;
	}

	return 1;
}

int is_table_separator(const char *line) {
	const char *pipe = strchr(line, '|');
	if (pipe == NULL) {
		return 0;
	}
	const char *next_pipe = strchr(pipe + 1, '|');
	if (next_pipe == NULL) {
		return 0;
	}
	while (*pipe == '|') {
		pipe++;
	}
	while (*pipe == ' ' || *pipe == ':') {
		pipe++;
	}
	while (*pipe == '-') {
		pipe++;
	}
	while (*pipe == ' ' || *pipe == ':') {
		pipe++;
	}
	if (*pipe == '|') {
		return 1;
	}
	return 0;
}

int is_code_block(const char *line) {
	if (strlen(line) < 3) {
		return 0;
	}
	return strstr(line, "```") == line;
}