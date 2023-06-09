//
// Created by chen on 4/7/23.
//
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

// function signatures
void *getLibraryDecode(const char *codec_name);

void executeMethodDecode(const char *codec_name, const char *message, void *lib_handle);

// function signatures
typedef char *(*codec_func)(const char *);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    char *codec_name = argv[1];
    char *message = argv[2];

    void *lib_handle = getLibraryDecode(codec_name);

    executeMethodDecode(codec_name, message, lib_handle);

    dlclose(lib_handle);
    return 0;
}


/**
 * open the lib the user requested to use by using dlopen
 * adds lib before the name and .so as the file extension
 * @param codec_name the library name
*/
void *getLibraryDecode(const char *codec_name) {
    char lib_filename[1024];
    sprintf(lib_filename, "lib%s.so", codec_name);
    void *lib_handle = dlopen(lib_filename, RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Error Loading Library: %s\n", dlerror());
        exit(1);
    }
    return lib_handle;
}

/**
 * use the function the user requested to use by using dlsym
 * @param codec_name codecA / codecB
 * @param message to send to the method
 * @param lib_handle the library
*/
void executeMethodDecode(const char *codec_name, const char *message, void *lib_handle) {
    char function[1024];
    sprintf(function, "%s_decode", codec_name);
    codec_func codec_decode = dlsym(lib_handle, function);
    if (!codec_decode) {
        fprintf(stderr, "Error Loading Function: %s\n", dlerror());
        dlclose(lib_handle);
        exit(2);
    }

    codec_decode(message);
}
