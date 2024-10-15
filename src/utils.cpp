#include "utils.h"

#include <string.h>

size_t findInString(const char* char_str, char c) {
    for (int i=0; i<strlen(char_str); i++)
        if(char_str[i] == c) return i;
    return -1;
}