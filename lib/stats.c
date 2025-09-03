
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <math.h>
char *get_stats(char *path){
    struct statvfs Stats;

    if(statvfs(path, &Stats) == -1){
        printf("Failed to get stats\n");
    }
    char *message = (char *)malloc(sizeof(char) * 200);
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
        char *test = "Not Found";
        return test;
    }
    fscanf(temperature, "%f", &mili);
    fclose(temperature);
    sys_temp = mili/1000;
    sprintf(message, "The CPU temperature is: %.2f", sys_temp);
    return message;
}

