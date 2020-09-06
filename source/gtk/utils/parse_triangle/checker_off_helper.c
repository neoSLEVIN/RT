//
//  checker_off_helper.c
//  RT
//
//  Created by Babette Alvyn on 9/6/20.
//  Copyright © 2020 Babette Alvyn. All rights reserved.
//

#include "gtk_module.h"

int check_file_off(const char *filename, char **err) {
    int fd;
    
    fd = open(filename, O_RDONLY);
//    if (common_check_off(fd, err)) {
//        close(fd);
//        return (1);
//    }
    common_check_off(fd, err);
    close(fd);
    return (0);
}

int check_element_count(char *line, int count, int max, char **err) {
    char **splits;
    
    splits = ft_strsplit(line, 32);
    if (check_params_count(splits, count, max, err))
        return (1);
    free_splits(splits, count);
    return (0);
}

int check_params_count(char **splits, int count, int max, char **err) {
    int i;
    int val;
    int bad_val;
    
    i = 0;
    bad_val = 0;
    if (splits == NULL)
        return error_safe(err, "empty line from gnl");
    while (splits[i] != NULL) {
        if (max != 0) {
            val = ft_atoi(splits[i]);
            if (val > max) {
                bad_val = 1;
            }
        }
        i++;
    }
    if (i != count || bad_val) {
        free_splits(splits, i);
        return error_safe(err, "check_params_count");
    }
    return (0);
}

int    error_safe(char **err, const char *text)
{
    if (!(*err = ft_strdup(text)))
        ft_error("Can't allocate memory");
    return (1);
}

void free_splits(char **splits, int count) {

    while (count != 0) {
        count--;
        free(splits[count]);
    }
    free(splits);
}
