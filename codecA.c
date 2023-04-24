#include <stdio.h>

/**
 * change lower case letters to upper and upper to lower
 * @param str the string to change the letters
 */
void codecA_encode(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        //from lower case to upper case
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (char) (str[i] - 'a' + 'A');
        }
            // from upper case to lower case
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (char) (str[i] - 'A' + 'a');
        }
    }
    printf("%s\n", str);
}

void codecA_decode(char *str) {
    codecA_encode(str);
}