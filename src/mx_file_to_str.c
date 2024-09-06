#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "libmx.h"


char *mx_buffer_to_string(char buffer[], int bytes_to_read) {
    char *new_str = mx_strnew(bytes_to_read);
    
    if (new_str == NULL) {
        return NULL;
    }

    mx_strncpy(new_str, buffer, bytes_to_read);

    return new_str;
}

char *mx_file_to_str(const char *filename) {
    if (filename == NULL) { return NULL; }

    int fd = open(filename, O_RDONLY);

    if(fd == -1){
        return NULL;
    }
    
    char *result_str = mx_strnew(0);
    char buffer[1024];
    int bytes_to_read;

    while((bytes_to_read = read(fd, buffer, sizeof(buffer))) > 0) {
        char *data_chunk = mx_buffer_to_string(buffer, bytes_to_read);
        char *old_result_str = result_str;

        result_str = mx_strjoin(result_str, data_chunk);

        if (old_result_str != NULL) {
            free(old_result_str);
        }

        if (data_chunk != NULL) {
            free(data_chunk);
        }
    }

    if (bytes_to_read == -1) {
        free(result_str);
        close(fd);
        return NULL;
    }

    close(fd);
    
    return result_str;
}

