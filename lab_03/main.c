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

float funHn(float xn, float xnPrev){
    return xn - xnPrev;
}

int splineAlg(tableT table, float findX){
    if (table.dotsNum <= 0)
        return ERROR;

    float *coefArrC = calloc(sizeof(float), table.dotsNum);
    float *coefArrZetta = calloc(sizeof(float), table.dotsNum);
    float *coefArrEtta = calloc(sizeof(float), table.dotsNum);
    float *coefArrA = calloc(sizeof(float), table.dotsNum);
    float *coefArrB = calloc(sizeof(float), table.dotsNum);
    float *coefArrD = calloc(sizeof(float), table.dotsNum);
    float *coefArrF = calloc(sizeof(float), table.dotsNum);
    float *coefArra = calloc(sizeof(float), table.dotsNum);
    float *coefArrb = calloc(sizeof(float), table.dotsNum);
    float *coefArrd = calloc(sizeof(float), table.dotsNum);

    float *coefArrHn = calloc(sizeof(float), table.dotsNum);
    for (int i = 1; i < table.dotsNum; i++){
        coefArrHn[i] = funHn(table.xArgs[i], table.xArgs[i - 1]);
    }

    // Прямой ход

    printf("Коэффициенты при прямом проходе:\n\n");

    for (int i = 2; i < table.dotsNum; i++){
        coefArrA[i] = coefArrHn[i - 1];
        coefArrB[i] = - 2 * (coefArrHn[i - 1] + coefArrHn[i]);
        coefArrD[i] = coefArrHn[i];
        coefArrF[i] = - 3 * ((table.yArgs[i] - table.yArgs[i - 1]) / coefArrHn[i] - (table.yArgs[i - 1] - table.yArgs[i - 2]) / coefArrHn[i - 1]);

        coefArrZetta[i + 1] = coefArrD[i]/ (coefArrB[i] - coefArrA[i] * coefArrZetta[i]);
        coefArrEtta[i + 1] = (coefArrA[i] * coefArrEtta[i] + coefArrF[i]) / (coefArrB[i] - coefArrA[i] * coefArrZetta[i]);
        printf("A[%d] = %f; B[%d] = %f; D[%d] = %f; F[%d] = %f; ζ[%d] = %f; η[%d] = %f;\n\n",
               i, coefArrA[i], i, coefArrB[i], i, coefArrD[i], i, coefArrF[i], i, coefArrZetta[i], i, coefArrEtta[i]);
    }
    printf("ζ[%d] = %f; η[%d] = %f;\n\n",
           table.dotsNum, coefArrZetta[table.dotsNum], table.dotsNum, coefArrEtta[table.dotsNum]);

    // Обратный ход, нахождение коэффициентов C
    printf("Определённые коэффициенты C:\n");

    printf("C[%d] = 0\n\n", table.dotsNum);
    printf("C[%d] = η[%d] = %f\n\n", table.dotsNum - 1, table.dotsNum, coefArrEtta[table.dotsNum]);
    coefArrC[table.dotsNum] = coefArrEtta[table.dotsNum];

    for (int i = table.dotsNum - 2; i >= 2; i--){
        coefArrC[i] = coefArrZetta[i + 1] * coefArrC[i + 1] + coefArrEtta[i + 1];
        printf("C[%d] = %f\n\n", i, coefArrC[i]);
    }

    printf("C[1] = 0\n\n");

    //table.yArgs[table.dotsNum - 1] = coefArrEtta[table.dotsNum - 1] / (1 - coefArrZetta[table.dotsNum - 1]);
    printf("Найдём y:\n\n");

    for (int i = table.dotsNum - 1; i >= 1; i--){
        table.yArgs[i - 1] = coefArrZetta[i] * table.yArgs[i] + coefArrEtta[i];
        printf("y[%d] = %f\n\n", i, table.yArgs[i]);
    }

    printf("Находим коэффициенты an, bn, dn:\n");
    for (int i = 1; i < table.dotsNum; i++){
        coefArra[i] = table.yArgs[i - 1];
        coefArrd[i] = (coefArrC[i + 1] - coefArrC[i]) / (3 * coefArrHn[i]);
        coefArrb[i] = (table.yArgs[i] - table.yArgs[i - 1]) / coefArrHn[i] - (1 / 3) * coefArrHn[i] * (coefArrC[i + 1] + 2 * coefArrC[i]);
        printf("a[%d] = %f; b[%d] = %f; d[%d] = %f\n\n",
               i, coefArra[i], i, coefArrb[i], i, coefArrd[i]);
    }

    int found = 0;
    // Ищем x
    for (int i = 0; i < table.dotsNum - 1; i++){
        if (findX > table.xArgs[i])
            found = i;
    }
    found++;

    printf("Интервал от точки x[%d] = %f до точки x[%d] = %f\n\n", found - 1, table.xArgs[found - 1], found, table.xArgs[found]);

    printf("В данной точке a = %f; b = %f; d = %f y[n] = %f, y[n - 1] = %f\n\n",
           coefArra[found], coefArrb[found], coefArrd[found], table.yArgs[found], table.yArgs[found - 1]);

    float diffSqr = (findX - table.xArgs[found]) * (findX - table.xArgs[found]);
    float diffTriple = diffSqr * (findX - table.xArgs[found]);
    float foundY = coefArra[found] + coefArrb[found + 1] * (findX - table.xArgs[found]) + coefArrC[found + 1] * diffSqr +
            coefArrd[found + 1] * diffTriple;

    printf("Заданному значению x соответсвует y = %f", foundY);

    free(coefArrA);
    free(coefArrB);
    free(coefArrC);
    free(coefArrD);
    free(coefArrF);
    free(coefArrEtta);
    free(coefArrZetta);
    free(coefArra);
    free(coefArrb);
    free(coefArrd);
    free(coefArrHn);

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
