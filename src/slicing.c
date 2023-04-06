//
// Created by julie on 6/04/2023.
//

#include "../include/slicing.h"

void slice(const char *str, char *result, size_t start, size_t end) {
    strncpy(result, str + start, end - start);
}

void slice_char_array(char *array, char *result, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        memcpy(result + i - start, array + i, sizeof(char));
    }
}
