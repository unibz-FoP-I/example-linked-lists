#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lnkd_lists.h"

static int _compare_int(const void* a, const void* b) {
    int a_int = *(const int*)a;
    int b_int = *(const int*)b;
    return (a_int > b_int) - (a_int < b_int);
}

void intLst_toJSON(FILE *fp, LinkedList *llPtr) {
    fputs("[", fp);
    int const *el;
    size_t i = 0;
    lnkd_ForEach(el, llPtr) {
        if (i++) fputs(", ", fp);
        fprintf(fp, "%d", *el);
    }
    fputs("]", fp);
}

void intLst_insert(LinkedList *llPtr, int value) {
    int *valuePtr = malloc(sizeof(value));
    if (valuePtr) {
        *valuePtr = value;
        lnkd_insert(llPtr, valuePtr, _compare_int);
    }
}

char *intLst_delete(LinkedList *llPtr, int value) {
    return lnkd_delete(llPtr, &value, _compare_int);
}

void intLst_free(LinkedList *llPtr) {
    while (!lnkd_isEmpty(llPtr)) {
        char *el = lnkd_pop(llPtr);
        free(el);
    }
    free(llPtr);
}

LinkedList *intLst_read(FILE *fp) {
    LinkedList *listPtr = calloc(1, sizeof(LinkedList));
    if (listPtr) {
        char *line_buf = NULL;
        size_t line_buf_size = 0;

        for (ssize_t read_chars = getline(&line_buf, &line_buf_size, fp); read_chars >= 0; read_chars = getline(&line_buf, &line_buf_size, fp))
        {
            char *end;
            int value = (int)strtol(line_buf, &end, 10);
            if (end != line_buf) intLst_insert(listPtr, value);
        }
        free(line_buf);
    }
    return listPtr;
}


int main(void)
{
    LinkedList *listPtr = intLst_read(stdin);
    if (!listPtr) {
        fputs("Cannot allocate memory for the list", stderr);
        return EXIT_FAILURE;
    }

    intLst_toJSON(stdout, listPtr);
    fputc('\n', stdout);

    intLst_free(listPtr);

    return EXIT_SUCCESS;
}
