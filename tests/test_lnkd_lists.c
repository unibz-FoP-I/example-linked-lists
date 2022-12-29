#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lnkd_lists.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

char *WORD_LIST[] = {
    "alizer",
    "xylf",
    "ejovalip",
    "revotempution",
    "palk",
    "cultiezes",
    "troilets",
    "ejovalip",
    "firv",
    "suv",
    "extric"
};


int compare_str(const void* a, const void* b) {
    const char *a_str = (const char*)a;
    const char *b_str = (const char*)b;
    return strcmp(a_str, b_str);
}

int compare_strPtr(const void* a, const void* b) {
    const void *a_ptr = *(void * const *)a;
    const void *b_ptr = *(void * const *)b;
    return compare_str(a_ptr, b_ptr);
}

void test_lnkd_str_insert(void) {
    LinkedList list = {};
    for (size_t i = 0; i < sizeof(WORD_LIST)/sizeof(char *); i++)
    {
        lnkd_insert(&list, WORD_LIST[i], compare_str);
    }

    // Create an ordered copy of the WORD_LIST array of words
    char **sorted_words = malloc(sizeof(WORD_LIST));
    memcpy(sorted_words, WORD_LIST, sizeof(WORD_LIST));
    qsort(sorted_words, sizeof(WORD_LIST)/sizeof(char *), sizeof(char *), compare_strPtr);

    // Array to store the elements of the list
    char **list_array = malloc(sizeof(WORD_LIST));
    char *el = 0;
    size_t i = 0;
    // copy each element of the list in the new array
    lnkd_ForEach(el, &list) {
        list_array[i] = el;
        i++;
    }
    TEST_ASSERT_EQUAL_STRING_ARRAY(sorted_words, list_array, sizeof(WORD_LIST)/sizeof(char *));
    free(list_array);
    free(sorted_words);
    // clear the list to avoid memory leaks
    while (!lnkd_isEmpty(&list)) lnkd_pop(&list);
}

void test_lnkd_str_pop(void) {
    LinkedList list = {};
    for (size_t i = 0; i < sizeof(WORD_LIST)/sizeof(char *); i++)
    {
        lnkd_insert(&list, WORD_LIST[i], compare_str);
    }

    // Create an ordered copy of the WORD_LIST array of words
    char **sorted_list = malloc(sizeof(WORD_LIST));
    memcpy(sorted_list, WORD_LIST, sizeof(WORD_LIST));
    qsort(sorted_list, sizeof(WORD_LIST)/sizeof(char *), sizeof(char *), compare_strPtr);

    size_t i = 0;
    while (!lnkd_isEmpty(&list))
    {
        char const *el = lnkd_pop(&list);
        TEST_ASSERT_EQUAL_STRING(sorted_list[i], el);
        i++;
    }
    free(sorted_list);
}

void test_lnkd_str_delete(void) {
    LinkedList list = {};
    for (size_t i = 0; i < sizeof(WORD_LIST)/sizeof(char *); i++)
    {
        lnkd_insert(&list, WORD_LIST[i], compare_str);
    }

    for (size_t i = 0; i < sizeof(WORD_LIST)/sizeof(char *); i++) {
        const char *el = lnkd_delete(&list, WORD_LIST[i], compare_str);
        TEST_ASSERT_NOT_NULL_MESSAGE(el, WORD_LIST[i]);
    }

    TEST_ASSERT_TRUE(lnkd_isEmpty(&list));
}

int main(void)
{
  UNITY_BEGIN();
 
  RUN_TEST(test_lnkd_str_insert);
  RUN_TEST(test_lnkd_str_pop);
  RUN_TEST(test_lnkd_str_delete);

  return UNITY_END();
}