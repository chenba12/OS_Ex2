#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

typedef char *(*codec_func)(const char *);


int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    char *codec_name = argv[1];
    char *message = argv[2];

    /**
     * open the lib the user requested to use by using dlopen
     * adds lib before the name and .so as the file extension
     */
    char lib_filename[1024];
    sprintf(lib_filename,
            "lib%s.so", codec_name);
    void *lib_handle = dlopen(lib_filename, RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Error Loading Library: %s\n", dlerror());
        exit(1);
    }

    /**
   * use the function the user requested to use by using dlsym
   */
    char str[1024];
    sprintf(str, "%s_encode", codec_name);
    codec_func codec_encode = dlsym(lib_handle, str);
    if (!codec_encode) {
        fprintf(stderr, "Error Loading Function: %s\n", dlerror());
        dlclose(lib_handle);
        exit(2);
    }


    codec_encode(message);
    dlclose(lib_handle);
    return 0;
}
