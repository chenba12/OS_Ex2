#include <string.h>
#include <stdio.h>

void codecB_encode(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = str[i];
        c += 3;
        str[i] = c;
    }
    printf("%s\n", str);
}

void codecB_decode(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = str[i];
        c += 3;
        str[i] = c;
    }
    printf("%s\n", str);
}
