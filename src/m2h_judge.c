#include "..\include\m2h_judge.h"

char * find_quote_content(const char *line, const int cur_quote_level) {
	const char *pos = line;
	int cnt = 0;
	while (*pos && (*pos == '>' || *pos == ' ')) {
		if (*pos == '>'){
			cnt++;
		}
		if (cnt == cur_quote_level){
			break;
		}
		pos++;
	}
	if (cnt){
		return (char *)(*(pos+1)==' '?(pos+2):(pos+1));
	}
	pos = line;
	return (char *)pos;
}

int is_header(const char *line) {
	const char *pos = line;
	while(*pos == ' '){
		pos++;
	}
	return *pos == '#';
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

int is_quote(const char *line) {
	int count = 0;
	const char *pos = line;
	while (*pos && (*pos==' ' || *pos == '>')) {
		if (*pos == '>') {
			count++;
		}
		pos++;
	}
	return count;
}

int is_code_block(const char *line) {
	const char *pos = line;
	while(*pos == ' '){
		pos++;
	}
	return strstr(pos, "```") == pos;
}

int is_html_comment(const char *line) {
	const char *start = strstr(line, "<!--");
	const char *end = strstr(line, "-->");
	return start != NULL && end != NULL && start < end;
}

int is_ordered_list(const char *line) {
	const char *pos = line;
	int level = 0;

	// 计算列表层次
	while (*pos == ' ') {
		pos++;
		level++;
	}

	if (*pos >= '0' && *pos <= '9') {
		pos++;
		while (*pos >= '0' && *pos <= '9') {
			pos++;
		}
		if (*pos == '.') {
			pos++;
			if (*pos == ' ') {
				return level / 2 + 1; // 返回列表层次
			}
		}
	}
	return 0;
}

int is_unordered_list(const char *line) {
	const char *pos = line;
	int level = 0;

	// 计算列表层次
	while (*pos == ' ') {
		pos++;
		level++;
	}

	if ((*pos == '*' || *pos == '-' || *pos == '+') && *(pos + 1) == ' ') {
		return level / 2 + 1; // 返回列表层次
	}
	return 0;
}

int is_horizontal_rule(const char *line) {
	const char *pos = line;
	int dash_count = 0;
	int star_count = 0;
	int underscore_count = 0;
	while (*pos == ' ') {
		pos++;
	}
	while (*pos) {
		if (*pos == '-') {
			dash_count++;
		} else if (*pos == '*') {
			star_count++;
		} else if (*pos == '_') {
			underscore_count++;
		} else if (*pos != ' ') {
			return 0;
		}
		pos++;
	}
	// 水平线至少需要三个连续的 -、* 或 _
	if ((dash_count >= 3 && star_count == 0 && underscore_count == 0) ||
		(star_count >= 3 && dash_count == 0 && underscore_count == 0) ||
		(underscore_count >= 3 && dash_count == 0 && star_count == 0)) {
		return 1;
	}
	return 0;
}