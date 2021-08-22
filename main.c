#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stat_lib.h"


int main(int argc, char **argv) {
    char name[256];
    int mouth = 0;

    if(argc <= 1){
        perror("You have not entered any arguments. Run -h ro more info.\n");
        exit(-9);
    }

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-h") == 0){
            help();
            return 0;
        }
        if(argv[i][0] == '-'){
            sscanf(argv[i] , "-m=%d", &mouth);
            sscanf(argv[i],"-f=%255s", name);
        } else{
            printf("Invalid argument %d. Run -h ro more info.\n", i - 1);
            exit(-9);
        }
    }

    if(strlen(name) > 4){
        int ctr = 0;
        char extension[5];
        for (int i = strlen(name) - 4; i < strlen(name); ++i) {
            extension[ctr] = name[i];
            ctr++;
        }
        if(strcmp(extension, ".csv") != 0){
            perror("The file must have a .csv extension\n");
            exit(14);
        }
    }

    s_statistic *statistic = get_all_stat(name);


    s_statistic *tmp = statistic;

    while (tmp != NULL){
        print_year_stat(&tmp->year, mouth);
        tmp = tmp->next;
    }


    return 0;
}
