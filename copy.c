#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void errorMessage();

void checkFlag(int argc, char *const *argv, int *vFlag, int *fFlag);

int copyFile(char *filename1, char *filename2, int vFlag, int fFlag);


int main(int argc, char *argv[]) {
    int vFlag;
    int fFlag;
    checkFlag(argc, argv, &vFlag, &fFlag);
    char *filename1 = argv[1];
    char *filename2 = argv[2];
    return copyFile(filename1, filename2, vFlag, fFlag);
}

void checkFlag(int argc, char *const *argv, int *vFlag, int *fFlag) {
    (*vFlag) = -1;
    (*fFlag) = -1;
    if (argc == 4) {
        int result = strcmp(argv[3], "-v");
        if (result == 0) {
            (*vFlag) = 1;
        } else {
            result = strcmp(argv[3], "-f");
            if (result == 0) {
                (*fFlag) = 1;
            } else {
                errorMessage();
            }
        }
    } else if (argc < 3) {
        errorMessage();
    } else if (argc == 5) {
        int result1 = strcmp(argv[3], "-v");
        int result2 = strcmp(argv[4], "-f");
        if (result1 == 0 && result2 == 0) {
            (*vFlag) = 1;
            (*fFlag) = 1;
        } else {
            result1 = strcmp(argv[3], "-i");
            result2 = strcmp(argv[4], "-f");
            if (result1 == 0 && result2 == 0) {
                (*vFlag) = 1;
                (*fFlag) = 1;
            } else {
                errorMessage();
            }
        }
    }
}

void errorMessage() {
    printf("Error not enough arguments\n");
    printf("Usage: ./cmp <file1> <file2> -v -f\n");
    printf("-v for  and -f are optional\n");
    printf("-v for verbose output -f for force overwrite\n");
    exit(1);
}

int copyFile(char *filename1, char *filename2, int vFlag, int fFlag) {
    int file_exists = access(filename2, F_OK);
    if (file_exists == 0) {
        if (fFlag != 1) {
            if (vFlag == 1)printf("target file exist\n");
            exit(1);
        }
    }
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "w");
    if (file2 == NULL || file1 == NULL) {
        if (vFlag == 1)printf("general failure\n");
        return 1;
    }
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file1)) > 0) {
        fwrite(buffer, 1, bytes_read, file2);
    }
    fclose(file1);
    fclose(file2);
    if (vFlag == 1)printf("success\n");
    return 0;
}

