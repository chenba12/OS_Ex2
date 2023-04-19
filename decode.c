//
// Created by chen on 4/7/23.
//
#include <stdio.h>
#include <dlfcn.h>


typedef char *(*codec_func)(const char *);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    char *codec_name = argv[1];
    char *message = argv[2];

    char lib_filename[1024];
    sprintf(lib_filename, "lib%s.so", codec_name);
    void *lib_handle = dlopen(lib_filename, RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    char symbol_name[1024];
    sprintf(symbol_name, "%s_decode", codec_name);
    codec_func codec_encode = dlsym(lib_handle, symbol_name);
    if (!codec_encode) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(lib_handle);
        return 1;
    }

    codec_encode(message);
    dlclose(lib_handle);
    return 0;
}
