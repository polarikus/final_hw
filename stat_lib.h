//
// Created by i9607 on 21.08.2021.
//

#ifndef FINAL_HW_STAT_LIB_H
#define FINAL_HW_STAT_LIB_H

#include <stdbool.h>

typedef struct mouth {
    int name;
    int max_temp;
    int min_temp;
    int summ_temp;
    int data_ctr;
    bool is_set;
} s_mouth;

typedef struct year {
    int name;
    s_mouth mouth[12];
    int summ_temp;
    int max_temp;
    int min_temp;
    int data_ctr;
} s_year;

typedef struct statistic {
    s_year year;
    struct statistic *next;
} s_statistic;

void mouth_init(s_mouth *mouth, int name);
void year_init(s_year *year, int name);
void get_all_stat(char *filename, s_statistic *statistic, int *years_ctn);
s_statistic *init_list(s_year *data);
void year_add(s_statistic **pSStatistic, s_year *data);

#endif //FINAL_HW_STAT_LIB_H
