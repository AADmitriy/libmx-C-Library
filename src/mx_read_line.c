#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "libmx.h"


char *mx_buffer_to_string(char buffer[], int bytes_to_read) {
    char *new_str = mx_strnew(bytes_to_read);
    
    if (new_str == NULL) {
        return NULL;
    }

    mx_strncpy(new_str, buffer, bytes_to_read);

    return new_str;
}

int look_for_delimeter_and_process_str(char *data_chunk, char delim, char **new_str, char **last_readed_data) {
    if (data_chunk == NULL) {
        return -1;
    }
    
    int delim_index = mx_get_char_index(data_chunk, delim);

    if (delim_index == -2) {
        return -2;
    }
    else if (delim_index == -1) {
        char *old_result_str = *new_str;
        *new_str = mx_strjoin(*new_str, data_chunk);
        mx_strdel(&old_result_str);
    }
    else {
        char *old_result_str = *new_str;
        char *data = mx_strndup(data_chunk, delim_index);
        *new_str = mx_strjoin(*new_str, data);
        mx_strdel(&data);
        mx_strdel(&old_result_str);

        char *old_last_readed_data = *last_readed_data;
        *last_readed_data = mx_strdup(data_chunk + delim_index + 1);
        mx_strdel(&old_last_readed_data);
    }


    return delim_index;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if(fd == -1){
        return -2;
    }
    
    static char *last_readed_data;
    char *result_str = mx_strnew(0);
    char buffer[buf_size];
    int bytes_to_read;
    
    int delimeter_seeking_result_status = look_for_delimeter_and_process_str(last_readed_data, delim, &result_str, &last_readed_data);

    if (delimeter_seeking_result_status == -2) {
        mx_strdel(&result_str);
        return -2;
    }
    else if (delimeter_seeking_result_status > -1) {
        int res = mx_strlen(result_str);
        if (res == 0) { 
            mx_strdel(&result_str);
            return res; 
        }
        
        mx_strcat(*lineptr, result_str);
        mx_strdel(&result_str);

        return res;
    }
    
    
    while((bytes_to_read = read(fd, buffer, buf_size)) > 0) {
        char *data_chunk = mx_buffer_to_string(buffer, bytes_to_read);
        
        int delimeter_seeking_result_status = look_for_delimeter_and_process_str(data_chunk, delim, &result_str, &last_readed_data);
        
        if (delimeter_seeking_result_status == -2) {
            mx_strdel(&result_str);
            return -2;
        }
        else if (delimeter_seeking_result_status > -1) {
            mx_strdel(&data_chunk);
            int res = mx_strlen(result_str);
            if (res == 0) {
                mx_strdel(&result_str);
                return res; 
            }
            mx_strcat(*lineptr, result_str);
            mx_strdel(&result_str);
            return res;
        }

        mx_strdel(&data_chunk);
    }

    int res = mx_strlen(result_str);

    if (res == 0) {
        mx_strdel(&result_str);
        mx_strdel(&last_readed_data);
        return -1; 
    }

    mx_strcat(*lineptr, result_str);
    mx_strdel(&result_str);
    mx_strdel(&last_readed_data);
    
    return res;
}





