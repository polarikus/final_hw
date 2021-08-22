#include "stat_lib.h"
#include <stdio.h>
#include <stdlib.h>


void mouth_init(s_mouth *mouth, int name){
    mouth->min_temp = 1000;
    mouth->max_temp = -1000;
    if(name > 13){
        perror("Attempt to initialize an invalid month!");
        exit(-4);
    }
    mouth->name = name;
    mouth->summ_temp = 0;
    mouth->data_ctr = 0;
    mouth->is_set = false;
}

void year_init(s_year *year, int name){
    year->min_temp = 1000;
    year->max_temp = -1000;
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

s_year *year_add(s_statistic **pSStatistic, s_year data){
    s_statistic *tmp;
    tmp = malloc(sizeof(s_statistic));
    tmp->year = data;
    tmp->next = NULL;

    (*pSStatistic)->next = tmp;
    return &(*pSStatistic)->next->year;
    //*pSStatistic = tmp;

}

void print_year_stat(s_year *year, int mouth){
    printf("\x1b[34mYear: %d\x1b[0m\n", year->name);

    printf("Average annual temperature: %d\n", year->summ_temp / year->data_ctr);
    year->min_temp == 1000 ? printf("Minimum temperature: \x1b[31mNULL\x1b[0m\n") : printf("Minimum temperature: %d\n", year->min_temp);
    year->max_temp == -1000 ? printf("Maximum temperature: \x1b[31mNULL\x1b[0m\n\n") : printf("Maximum temperature: %d\n\n", year->max_temp);

    if(mouth == 0){
        printf("\x1b[35mMouth statistics:\x1b[0m\n");
        for (int i = 0; i < 12; ++i) {
            if(year->mouth[i].is_set != false){
                printf("\x1b[33mMouth %d:\x1b[0m\n", year->mouth[i].name);

                printf("Average annual temperature: %d\n", year->mouth[i].summ_temp / year->mouth[i].data_ctr);
                year->mouth[i].min_temp == 1000 ? printf("Minimum temperature: \x1b[31mNULL\x1b[0m\n") : printf("Minimum temperature: %d\n", year->mouth[i].min_temp);
                year->mouth[i].max_temp == -1000 ? printf("Maximum temperature: \x1b[31mNULL\x1b[0m\n\n") : printf("Maximum temperature: %d\n\n", year->mouth[i].max_temp);
            }
        }
    } else if(mouth <= 12){
        if(year->mouth[mouth - 1].is_set == false){
            printf("\x1b[31mThere are no statistics for month %d!\x1b[0m\n\n", mouth);
        }
        if(year->mouth[mouth - 1].name == mouth && year->mouth[mouth - 1].is_set != false){
            printf("\x1b[33mMouth %d:\x1b[0m\n", year->mouth[mouth - 1].name);

            printf("Average annual temperature: %d\n", year->mouth[mouth - 1].summ_temp / year->mouth[mouth - 1].data_ctr);
            year->mouth[mouth - 1].min_temp == 1000 ? printf("Minimum temperature: \x1b[31mNULL\x1b[0m\n") : printf("Minimum temperature: %d\n", year->mouth[mouth - 1].min_temp);
            year->mouth[mouth - 1].max_temp == -1000 ? printf("Maximum temperature: \x1b[31mNULL\x1b[0m\n\n") : printf("Maximum temperature: %d\n\n", year->mouth[mouth - 1].max_temp);
        }
    } else{
        perror("Invalid mouth number!");
    }
    printf("---------------------------------\n");
}



s_statistic *get_all_stat(const char *filename){
    FILE *fp;
    int get_line = 0;

    if ((fp = fopen(filename, "rt")) == NULL)
    {
        perror("Could not open file!\n");
        exit(19);
    }
    s_statistic *statistic = NULL;

    while (1) {
        int year = 0;
        int mouth = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        int temperature = 0;
        char line[50];
        s_statistic *tmp_stat;
        s_year year_pointer;
        s_year *stat_year_ptr = NULL;
        get_line = fscanf(fp, "%d;%d;%d;%d;%d;%d\n", &year, &mouth, &day, &hour, &minute, &temperature); // NOLINT(cert-err34-c)
        if(get_line == EOF){
            break;
        }
        if(get_line != 6){
            fscanf(fp, "%s\n", line);
            printf("\x1b[31mError read line: %s\x1b[0m\n", line);
            continue;
        }

        if(statistic == NULL){
            year_init(&year_pointer, year);
            statistic = init_list(year_pointer);
            year_pointer = statistic->year;
        }
        tmp_stat = statistic;
        while (tmp_stat != NULL){
            if(tmp_stat->year.name == year){
                stat_year_ptr = &tmp_stat->year;
                break;
            } else{
                if(tmp_stat->next == NULL){
                    year_init(&year_pointer, year);
                    stat_year_ptr = year_add(&tmp_stat, year_pointer);
                    break;
                }
            }
            tmp_stat = tmp_stat->next;
        }

        if(stat_year_ptr == NULL){
            perror("Error: stat_year_ptr in NULL");
            exit(-2);
        }
        if(stat_year_ptr->max_temp < temperature){
            stat_year_ptr->max_temp = temperature;
        } else if(stat_year_ptr->min_temp > temperature){
            stat_year_ptr->min_temp = temperature;
        }
        stat_year_ptr->data_ctr ++;
        stat_year_ptr->summ_temp += temperature;
        s_mouth *mouth_ptr = &stat_year_ptr->mouth[mouth-1];

        if(mouth == mouth_ptr->name){
            if(mouth_ptr->is_set == false){
                mouth_ptr->is_set = true;
            }
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

void help(){
    printf("\x1b[32mSYNOPSIS\x1b[0m\n");
    printf("./main -[OPTION]\n\n");
    printf("\x1b[32mDESCRIPTION\x1b[0m\n");
    printf("The application parses a .csv file with temperature statistics obtained by the sensor.\n");
    printf("CSV file format:\n\x1b[32mdd\x1b[0m;\x1b[31mMM\x1b[0m;\x1b[33mhh\x1b[0m;\x1b[34mmm\x1b[0m;\x1b[35mtemperature\x1b[0m\n\n");
    printf("-h\n");
    printf("        display this help and exit\n");
    printf("-f=<filename.csv>\n");
    printf("        input csv file for processing\n");
    printf("-m=<mouth number>\n");
    printf("        if this key is given, then the output is\n"
           "only statistics for the specified month.\n");
}
