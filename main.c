#include <stdio.h>
#include <stdlib.h>
#include "stat_lib.h"


int main() {
    char name[] = "temp.csv";
    int years_ctn = 0;
    s_statistic *statistic;
    get_all_stat(name, statistic, &years_ctn);

    for (int i = 0; i < years_ctn; i++) {
        //printf("name %d\n", years[i].mouth[5].summ_temp);
    }
    return 0;
}
