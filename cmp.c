#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void errorMessage();

void checkFlag(int argc, char *const *argv, int *vFlag, int *fFlag);

int copyFile(char *filename1, char *filename2, int vFlag, int fFlag);


int main(int argc, char *argv[]) {
    int vFlag;
    int iFlag;
    checkFlag(argc, argv, &vFlag, &iFlag);
    char *filename1 = argv[1];
    char *filename2 = argv[2];
    return copyFile(filename1, filename2, vFlag, iFlag);
}

void checkFlag(int argc, char *const *argv, int *vFlag, int *iFlag) {
    (*vFlag) = -1;
    (*iFlag) = -1;
    if (argc == 4) {
        int result = strcmp(argv[3], "-v");
        if (result == 0) {
            (*vFlag) = 1;
        } else {
            result = strcmp(argv[3], "-i");
            if (result == 0) {
                (*iFlag) = 1;
            } else {
                errorMessage();
            }
        }
    } else if (argc < 3) {
        errorMessage();
    } else if (argc == 5) {
        int result1 = strcmp(argv[3], "-v");
        int result2 = strcmp(argv[4], "-i");
        if (result1 == 0 && result2 == 0) {
            (*vFlag) = 1;
            (*iFlag) = 1;
        } else {
            result1 = strcmp(argv[3], "-i");
            result2 = strcmp(argv[4], "-v");
            if (result1 == 0 && result2 == 0) {
                (*vFlag) = 1;
                (*iFlag) = 1;
            } else {
                errorMessage();
            }
        }
    }
}

void errorMessage() {
    printf("Error not enough arguments\n");
    printf("Usage: ./cmp <file1> <file2> -v -i\n");
    printf("-v for  and -i are optional\n");
    printf("-v for verbose output -i ignore case\n");
    exit(1);
}

int copyFile(char *filename1, char *filename2, int vFlag, int iFlag) {
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");
    if (file2 == NULL || file1 == NULL) {
        if (vFlag == 1)printf("general failure\n");
        return 1;
    }
    int char1, char2;
    char1 = fgetc(file1);
    char2 = fgetc(file2);
    if (iFlag == 1) {
        char1 = tolower(char1);
        char2 = tolower(char2);
    }
    while (char1 == char2 && char1 != EOF && char2 != EOF) {
        char1 = fgetc(file1);
        char2 = fgetc(file2);
        if (iFlag == 1) {
            char1 = tolower(char1);
            char2 = tolower(char2);
        }
    }
    fclose(file1);
    fclose(file2);
    if (char1 == char2) {
        if (vFlag == 1)printf("equal\n");
        return 0;
    } else {
        if (vFlag == 1)printf("distinct\n");
        return 1;
    }

}


