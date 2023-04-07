//
// Created by chen on 4/7/23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void codecA(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        //from lower case to upper case
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
            // from upper case to lower case
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
    printf("%s\n", str);
}

void codecB(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] - 3;
    }
    printf("%s\n", str);
}

void errorMessage() {
    printf("Error not enough arguments\n");
    printf("Usage: ./encode <codec> <message>\n");
    printf("<codec> codecA or codecB\n");
    printf("<message> a string to pass to the function if you want to add space"
           "put your string in " " \n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        errorMessage();
    } else if (argc > 3) {
        errorMessage();
    } else {
        char *func = argv[1];
        char *stringToPass = argv[2];
        int result = strcmp(func, "codecA");
        if (result == 0) {
            codecA(stringToPass);
        } else {
            result = strcmp(func, "codecB");
            if (result == 0) {
                codecB(stringToPass);
            } else {
                errorMessage();
            }
        }
    }
    return 0;
}