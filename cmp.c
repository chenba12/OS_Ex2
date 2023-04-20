#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void errorMessage();

void checkFlag(int argc, char *const *argv, int *vFlag, int *iFlag);

int compareFile(char *filename1, char *filename2, int vFlag, int iFlag);


int main(int argc, char *argv[]) {
    int vFlag;
    int iFlag;
    checkFlag(argc, argv, &vFlag, &iFlag);
    char *filename1 = argv[1];
    char *filename2 = argv[2];
    return compareFile(filename1, filename2, vFlag, iFlag);
}

/**
 * check which flags the user entered
 * -i or -v or both order doesn't matter
 * @param argc the amount of arguments the program got
 * @param argv an array that stores the arguments
 * @param vFlag verbose output entered as -v
 * @param iFlag ignore case flag entered as -i
 */
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

/**
 * if the user entered wrong args when running this tool
 * print out a error message and how to use it properly
 * exit(1)
 */
void errorMessage() {
    printf("Error not enough arguments\n");
    printf("Usage: ./cmp <file1> <file2> -v -i\n");
    printf("-v for  and -i are optional\n");
    printf("-v for verbose output -i ignore case\n");
    exit(1);
}

/**
 * compare 2 files if they are the same
 * @param filename1 string
 * @param filename2 string
 * @param vFlag verbose output: 1 if the user used -v 0 otherwise
 * @param iFlag ignore case: 1 if the user used -i 0 otherwise
 * @return 0 if equal 1 if the files are distinct
 */
int compareFile(char *filename1, char *filename2, int vFlag, int iFlag) {
    FILE *file1 = fopen(filename1, "rb");
    FILE *file2 = fopen(filename2, "rb");
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


