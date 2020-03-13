#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "table.txt"

#define ERROR 1

typedef struct{
    int dotsNum;
    double *xArgs;
    double *yArgs;
}tableT;

int readfromTable(FILE *tableFile, tableT *table){
    if (!tableFile)
        return ERROR;

    int check, dotsNum;
    check = fscanf(tableFile, "number of dots: %d", &dotsNum);

    if (!check || dotsNum <= 0)
        return ERROR;

    table->dotsNum = dotsNum;
#ifdef DEBUG
    printf("%d", table->dotsNum);
#endif

    table->xArgs = calloc(dotsNum, sizeof(double));
    table->yArgs = calloc(dotsNum, sizeof(double));

    for (int i = 0; i < dotsNum; i++)
        check = fscanf(tableFile, "%lf%lf", table->xArgs + i, table->yArgs + i);

    if (check != 2)
        return ERROR;

    return 0;
}

int printTableT(tableT table){
    printf("|--------------------|--------------------|\n");
    printf("|%16s    |%16s    |", "X", "Y");
    printf("\n");
    printf("|--------------------|--------------------|\n");
    for (int i = 0; i < table.dotsNum; i++){
        printf("|% 20lf|% 20lf|\n", *(table.xArgs + i), *(table.yArgs + i));
        printf("|--------------------|--------------------|\n");
    }

    return 0;
}

void freeTableT(tableT *table){
    if (!table)
        return ;
    table->dotsNum = 0;
    if (table->xArgs)
        free(table->xArgs);
    if (table->yArgs)
        free(table->yArgs);
}

int splineAlg(tableT table, float findX){
    if (table.dotsNum <= 0)
        return ERROR;

    if (findX < 0)
        printf("I need to push this code, but i have -Wall");

    return 0;
}

int main(){
    FILE *tableFile = fopen(FILE_NAME, "r");
    if (!tableFile){
        printf("Файл не найден.\n");
        return ERROR;
    }

    tableT table = { 0 };

    readfromTable(tableFile, &table);

    printTableT(table);

    fclose(tableFile);


    printf("Введите ординату для поиска абсциссы: ");
    float findX;
    int check = scanf("%f", &findX);

    if (check != 1){
        printf("Значение считать не удалось. Завершение программы...");
        return ERROR;
    }

    check = splineAlg(table, findX);



    freeTableT(&table);

    return 0;
}
