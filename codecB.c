#include <stdio.h>

/**
 * add 3 to the ASCII value of each letter in the string
 * @param str
 */
void codecB_encode(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = str[i];
        c += 3;
        str[i] = (char) c;
    }
    printf("%s\n", str);
}

/**
 * subtract 3 to the ASCII value of each letter in the string
 * @param str
 */
void codecB_decode(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = str[i];
        c += 3;
        str[i] = (char) c;
    }
    printf("%s\n", str);
}
