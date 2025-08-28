
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <math.h>
char *get_stats(char *path){
    struct statvfs Stats;

    if(statvfs(path, &Stats) == -1){
        printf("Failed to get stats\n");
    }

    char *message = (char *)malloc(sizeof(char) * 150);
    long gb = pow(10, 9);
    long gib = pow(1024, 3);
    long total_GB = (Stats.f_bavail * Stats.f_frsize) / gb;
    long total_GiB = (Stats.f_bavail * Stats.f_frsize) / gib;
    sprintf(message, "Avaliable Free Blocks: %ld\nTotal avaliable: %ld(GB)\nTotal avaliable: %ld(GiB)\n", Stats.f_bavail, total_GB , total_GiB);
    return message;
}
