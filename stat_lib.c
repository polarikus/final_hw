#include "stat_lib.h"
#include <stdio.h>
#include <stdlib.h>
void mouth_init(s_mouth *mouth, int name){
    mouth->min_temp = 0;
    mouth->max_temp = 0;
    if(name > 13){
        //TODO Add error
    }
    mouth->name = name;
    mouth->summ_temp = 0;
    mouth->data_ctr = 0;
    mouth->is_set = false;
}

void year_init(s_year *year, int name){
    year->min_temp = 0;
    year->max_temp = 0;
    year->name = name;
    year->summ_temp = 0;
    year->data_ctr = 0;
    for (int i = 0; i <= 11; i++) {
        mouth_init(&year->mouth[i], i + 1);
    }
}

s_statistic *init_list(s_year data){
    s_statistic *new;

    new = malloc(sizeof(s_statistic));
    new->next = NULL;
    new->year = data;

    return new;
}

void year_add(s_statistic **pSStatistic, s_year *data){
    s_statistic *tmp;
    tmp = malloc(sizeof(s_statistic));
    tmp->year = *data;
    tmp->next = NULL;

    (*pSStatistic)->next = tmp;
    //*pSStatistic = tmp;

}



s_statistic *get_all_stat(char *filename){
    FILE *fp;
    int get_line = 0;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Не удалось открыть файл");
    }
    s_statistic *statistic = NULL;

    while (get_line != EOF) {
        int year;
        int mouth;
        int day;
        int hour;
        int minute;
        int temperature;
        s_statistic *tmp_stat;
        s_year year_pointer;
        get_line = fscanf(fp, "%d;%d;%d;%d;%d;%d", &year, &mouth, &day, &hour, &minute, &temperature); // NOLINT(cert-err34-c)
        if(statistic == NULL){
            year_init(&year_pointer, year);
            statistic = init_list(year_pointer);
        }
        tmp_stat = statistic;
        while (tmp_stat->next != NULL){
            if(tmp_stat->year.name == year){
                year_pointer = tmp_stat->year;
                break;
            } else{
                if(tmp_stat->next == NULL){
                    year_init(&tmp_stat->year, year);
                    year_pointer = tmp_stat->year;
                    break;
                }
            }
            tmp_stat = tmp_stat->next;
        }
        year_pointer.data_ctr ++;
        year_pointer.summ_temp += temperature;
        s_mouth *mouth_ptr = &year_pointer.mouth[5];

        if(mouth == 6){
            //printf("Year %d Mouth %d day %d Hour %d Minute %d Temp %d\n", year, mouth, day, hour, minute, temperature);
            if(mouth_ptr->max_temp < temperature){
                mouth_ptr->max_temp = temperature;
            } else if(mouth_ptr->min_temp > temperature){
                mouth_ptr->min_temp = temperature;
            }
            mouth_ptr->summ_temp += temperature;
            mouth_ptr->data_ctr ++;
        }
    }
    fclose(fp);
    return statistic;
}

