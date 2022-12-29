#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lnkd_lists.h"
#include "utf8.h"

static int _compare_str(const void* a, const void* b) {
    const char *a_str = (const char*)a;
    const char *b_str = (const char*)b;
    return utf8cmp(a_str, b_str);
}

void strLst_toJSON(FILE *fp, LinkedList *llPtr) {
    fputs("[", fp);
    char *el;
    size_t i = 0;
    lnkd_ForEach(el, llPtr) {
        if (i++) fputs(", ", fp);
        fprintf(fp, "\"%s\"", el);
    }
    fputs("]", fp);
}

void strLst_insert(LinkedList *llPtr, char *value) {
    lnkd_insert(llPtr, value, _compare_str);
}

char *strLst_delete(LinkedList *llPtr, const char *value) {
    return lnkd_delete(llPtr, value, _compare_str);
}

void strLst_free(LinkedList *llPtr) {
    while (!lnkd_isEmpty(llPtr)) {
        char *el = lnkd_pop(llPtr);
        free(el);
    }
    free(llPtr);
}

LinkedList *strLst_read(FILE *fp) {
    LinkedList *listPtr = calloc(1, sizeof(LinkedList));
    if (listPtr) {
        char *line_buf = NULL;
        size_t line_buf_size = 0;

        for (ssize_t read_chars = getline(&line_buf, &line_buf_size, fp); read_chars >= 0; read_chars = getline(&line_buf, &line_buf_size, fp))
        {
            char *line = malloc(read_chars + 1);
            // stop reading if memory cannot be allocated
            if (!line) break;
            memcpy(line, line_buf, read_chars + 1);
            // look for the newline char and remove it
            char *nlPtr = utf8pbrk(line, "\n");
            if (nlPtr) *nlPtr = 0;
            strLst_insert(listPtr, line);
        }
    }
    return listPtr;
}


int main(void)
{
    LinkedList *listPtr = strLst_read(stdin);
    if (!listPtr) {
        fputs("Cannot allocate memory for the list", stderr);
        return EXIT_FAILURE;
    }

    strLst_toJSON(stdout, listPtr);
    fputc('\n', stdout);

    strLst_free(listPtr);

    return EXIT_SUCCESS;
}
