
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <math.h>
#include <dirent.h>

char *get_stats(char *path){
    struct statvfs Stats;
    char *message = (char *)malloc(sizeof(char) * 200);

    if(statvfs(path, &Stats) == -1){
        strcpy(message, "Path does not exsist");
        return message;
    }
    long gib = pow(1024, 3);
    long total_GiB = (Stats.f_bavail * Stats.f_frsize) / gib;
    sprintf(message, "Path: %s\nAvaliable Free Blocks: %ld\nTotal avaliable: %ld(GiB)\n", path, Stats.f_bavail, total_GiB);
    return message;
}

char *get_temp(){
    float sys_temp;
    float mili;
    char *message = (char *)malloc(sizeof(char) * 100);

    FILE *temperature = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temperature == NULL){
        strcpy(message, "CPU TEMP NOT FOUND");
        return message;
    }
    fscanf(temperature, "%f", &mili);
    fclose(temperature);
    sys_temp = mili/1000;
    sprintf(message, "The CPU temperature is: %.2f", sys_temp);
    return message;
}

/*
 * BUG: Sometimes get_files does not return the whole list. Look at how 
 * the realloc is behaving. 
 */
char *get_files(char *path){
    int bufsize = 300;
    int used = 0;
    char *files = (char *)malloc(sizeof(char) * bufsize);
    files[0] = '\0';
    struct dirent *de;
    DIR *d = opendir(path);
    if (d == NULL){
        perror("Dir not found");
        return NULL;
    }

    while((de = readdir(d)) != NULL){
        if(de->d_name[0] != '.'){
            strcat(files, de->d_name);
            strcat(files, "\n");
            used = used + strlen(de->d_name) + 2;
        }
        if(used >= 100){
            char *newptr = (char *)realloc(files, sizeof(char) * (used + bufsize));
            if (newptr == NULL){
                printf("Ran out of MEM\n");
                closedir(d);
                return files;
            }
            files = newptr;
        }
    }
    closedir(d);
    return files;
}
