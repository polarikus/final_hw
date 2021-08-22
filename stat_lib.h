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

void help(); //App Info

void mouth_init(s_mouth *mouth, int name); //init the mouth data struct

void year_init(s_year *year, int name); //init the Year data struct

s_statistic *get_all_stat(const char *filename); //Parse File and return data as list of years structs

s_statistic *init_list(s_year data); //init list of years

s_year *year_add(s_statistic **pSStatistic, s_year data); //Add new year in list

void print_year_stat(s_year *year, int mouth); //Print stats in CLI

#endif //FINAL_HW_STAT_LIB_H
