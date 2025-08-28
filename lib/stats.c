
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
    long gib = pow(1024, 3);
    long total_GiB = (Stats.f_bavail * Stats.f_frsize) / gib;
    sprintf(message, "Path: %s\nAvaliable Free Blocks: %ld\nTotal avaliable: %ld(GiB)\n", path, Stats.f_bavail, total_GiB);
    return message;
}
