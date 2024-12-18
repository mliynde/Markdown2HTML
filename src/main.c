#include <stdio.h>
#include <stdlib.h>

#include "convert.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    convert_markdown_to_html(argv[1]);

    return 0;
}