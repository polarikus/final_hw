#include <stdio.h>
#include <stdlib.h>
#include "stat_lib.h"


int main() {
    char name[] = "temp.csv";
    //s_year year;
    s_statistic *statistic = get_all_stat(name);
    //year_init(&year, 2021);
    //statistic = init_list(year);
    //year_init(&year, 2022);
    //year_add(&statistic, &year);

    s_statistic *tmp = statistic;

    while (tmp != NULL){
        printf("name %d\n", tmp->year.name);
        tmp = tmp->next;
    }


    return 0;
}
