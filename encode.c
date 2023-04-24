#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

// function signatures
typedef char *(*codec_func)(const char *);

void *getLibraryEncode(const char *codec_name);

void executeMethodEncode(const char *codec_name, const char *message, void *lib_handle);

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    char *codec_name = argv[1];
    char *message = argv[2];

    void *lib_handle = getLibraryEncode(codec_name);

    executeMethodEncode(codec_name, message, lib_handle);

    dlclose(lib_handle);
    return 0;
}


/**
 * open the lib the user requested to use by using dlopen
 * adds lib before the name and .so as the file extension
 * * @param codec_name the library name
*/
void *getLibraryEncode(const char *codec_name) {
    char lib_filename[1024];
    sprintf(lib_filename,
            "lib%s.so", codec_name);
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
void executeMethodEncode(const char *codec_name, const char *message, void *lib_handle) {
    char str[1024];
    sprintf(str, "%s_encode", codec_name);
    codec_func codec_encode = dlsym(lib_handle, str);
    if (!codec_encode) {
        fprintf(stderr, "Error Loading Function: %s\n", dlerror());
        dlclose(lib_handle);
        exit(2);
    }
    codec_encode(message);
}

