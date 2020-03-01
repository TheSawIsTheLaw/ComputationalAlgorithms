/*
 * Алгоритмитм и программа построения интерполяционного полинома Ньютона
 * Функциональность
 *
 * Входные данные:
 * Таблица значений y(x)
 * Значение x
 * Степень полинома
 *
 * Выходные данные:
 * Интерполяционный полином
 * Корень табличной функции, найденный методом половинного деления
 * Корень, найденный обратной интерполяцией
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_NAME "table.txt"
#define ERROR 666
#define EPS 1e-4

//#define DEBUG

typedef struct{
    int dotsNum;
    double *xArgs;
    double *yArgs;
    double *zArgs;
}tableT;

// Функция чтения таблицы заданного формата
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
    table->zArgs = calloc(dotsNum, sizeof(double));

    for (int i = 0; i < dotsNum; i++)
        check = fscanf(tableFile, "%lf%lf%lf", table->xArgs + i, table->yArgs + i, table->zArgs + i);

    if (check != 3)
        return ERROR;

    return 0;
}

int printTableT(tableT table)
{
#ifdef DEBUG
    printf("%d", table.dotsNum);
#endif
    printf("|---------|---------|---------|\n");
    printf("|%5s    |%5s    |%5s    |", "X", "Y", "Z");
    printf("\n");
    printf("|---------|---------|---------|\n");
    for (int i = 0; i < table.dotsNum; i++){
        printf("|%+5lf|%+5lf|%+5lf|\n", *(table.xArgs + i), *(table.yArgs + i), *(table.zArgs + i));
        printf("|---------|---------|---------|\n");
    }

    return 0;
}

void freeTableT(tableT *table)
{
    if (!table)
        return ;
    table->dotsNum = 0;
    if (table->xArgs)
        free(table->xArgs);
    if (table->yArgs)
        free(table->yArgs);
    if (table->zArgs)
        free(table->zArgs);
}

double splitDiff(double yi, double yj, double xi, double xj){
#ifdef DEBUG
    printf("\nyi=%lf yj=%lf xi=%lf xj=%lf\n", yi, yj,
            xi, xj);
#endif
    return (yi - yj)/(xi - xj);
}

void slowSortTable(tableT *table)
{
    double memoryVar;
    for (int i = 0; i < table->dotsNum; i++){
        for (int j = 0; j < table->dotsNum - 1; j++){
            if (table->xArgs[j] > table->xArgs[j + 1]){
                memoryVar = table->xArgs[j];
                table->xArgs[j] = table->xArgs[j + 1];
                table->xArgs[j + 1] = memoryVar;

                memoryVar = table->yArgs[j];
                table->yArgs[j] = table->yArgs[j + 1];
                table->yArgs[j + 1] = memoryVar;
            }
        }
    }
}

int interpolationAlg(tableT *table, double findX, int polynomDegree){
    if (polynomDegree <= 0)
        return ERROR;
    slowSortTable(table);

    printf("\nОтсортированная таблица значений будет иметь следующий вид:\n");
    printf("|%5s    |%5s    |\n", "x", "y");
    printf("|---------|---------|\n");
    printTableT(*table);
    printf("\n\n");

    // Нахождение позиции значения х в исходной таблице
    int position = -1;
    for (int i = 0; i < table->dotsNum; i++){
        if (table->xArgs[i] - findX <= 0 && table->xArgs[i + 1] - findX >= 0){
            position = i;
            break;
        }
    }

    if (position == -1){
        printf("К сожалению, экстраполяция запрещена.\n");
        return ERROR;
    }

#ifdef DEBUG
    printf("pos is %d\n", position);
#endif

    // Выделение узлов
    if (table->dotsNum < polynomDegree + 1)
        return ERROR;

    int disDegree = polynomDegree, leftMove = 0, rightMove = 0;
    double *nodesXMas = calloc(polynomDegree + 1, sizeof(double));
    double *nodesYMas = calloc(polynomDegree + 1, sizeof(double));
    position++;
    while (disDegree > 0){
        if (position - leftMove > 0){
            leftMove++;
            disDegree--;
        }
        if (position + rightMove < table->dotsNum - 1){
            rightMove++;
            disDegree--;
        }
    }
    for (int i = position - leftMove, curNode = 0; i <= position + rightMove; i++, curNode++){
        nodesYMas[curNode] = table->yArgs[i];
        nodesXMas[curNode] = table->xArgs[i];
    }
    printf("Работа будет производиться со следующими узлами:\n");
    for (int i = 0; i < polynomDegree + 1; i++){
        printf("x%d = %+lf; y%d = %+lf\n", i, nodesXMas[i], i, nodesYMas[i]);
    }

    double **difMas = calloc(polynomDegree + 2, sizeof(double *));
    difMas[0] = nodesXMas;
    difMas[1] = nodesYMas;
    nodesXMas = NULL;
    nodesYMas = NULL;
    // Расчёт таблицы с разделёнными разностями
    for (int i = polynomDegree, curPos = 2; i > 0; i--, curPos++){
        difMas[curPos] = calloc(i, sizeof(double));
        for (int j = 0; j < i; j++)
            difMas[curPos][j] = splitDiff(difMas[curPos - 1][j], difMas[curPos - 1][j + 1],
                                          difMas[0][j], difMas[0][j - 1 + curPos]);
    }

    printf("\nПолученная таблица:\n");
    for (int i = 0; i < polynomDegree + 1; i++){
        for (int j = 0; j < polynomDegree + 2 - i; j++)
            printf("%+3.3f ", difMas[j][i]);
        printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < polynomDegree + 1; i++){
        for (int j = 0; j < polynomDegree + 2 - i; j++)
            if (difMas[j][i] == INFINITY || difMas[j][i] == -INFINITY){
                printf("К несчастью, возникло деление на ноль. Завершение программы...\n\n");
                for (int i = 0; i < polynomDegree + 2; i++)
                    free(difMas[i]);
                free(difMas);
                return ERROR;
            }
    }

    // Расчёт полинома
    double finalPolynom = difMas[1][0], compGap = 1;
    printf("Слагаемые полинома:\n%.5f\n", difMas[1][0]);
    for (int i = 0; i < polynomDegree; i++)
    {
        for (int j = 0; j <= i; j++){
            printf("(x - %lf)*", difMas[0][j]);
            compGap *= findX - difMas[0][j];
        }
        printf("(%lf)\n", difMas[i + 2][0]);
        compGap *= difMas[i + 2][0];
        finalPolynom += compGap;
        compGap = 1;
    }

    // Удивительно... Но оно работает...

    printf("\n\nPn(x) = %lf\n\n", finalPolynom);

    for (int i = 0; i < polynomDegree + 2; i++)
        free(difMas[i]);
    free(difMas);

    return 0;
}

// Алгоритм чистой воды, без предоставления всего и всея пользователю
int interpNuPolAlg(tableT *table, double findX, int polynomDegree, double *foundY){
    if (!table)
        return ERROR;
    slowSortTable(table);

    if (!foundY)
        return ERROR;

    int position = -1;
    for (int i = 0; i < table->dotsNum - 1; i++){
        if (table->xArgs[i] - findX <= EPS && table->xArgs[i + 1] - findX >= EPS){
            position = i;
            break;
        }
    }

    if (position == -1){
        return ERROR;
    }
    // Выделение узлов
    if (table->dotsNum < polynomDegree + 1)
        return ERROR;

    int disDegree = polynomDegree, leftMove = 0, rightMove = 0;
    double *nodesXMas = calloc(polynomDegree + 1, sizeof(double));
    double *nodesYMas = calloc(polynomDegree + 1, sizeof(double));
    while (disDegree > 0){
        if (position - leftMove > 0){
            leftMove++;
            disDegree--;
        }
        if (position + rightMove < table->dotsNum - 1){
            rightMove++;
            disDegree--;
        }
    }
    for (int i = position - leftMove, curNode = 0; i <= position + rightMove; i++, curNode++){
        nodesYMas[curNode] = table->yArgs[i];
        nodesXMas[curNode] = table->xArgs[i];
    }

    double **difMas = calloc(polynomDegree + 2, sizeof(double *));
    difMas[0] = nodesXMas;
    difMas[1] = nodesYMas;
    nodesXMas = NULL;
    nodesYMas = NULL;
    // Расчёт таблицы с разделёнными разностями
    for (int i = polynomDegree, curPos = 2; i > 0; i--, curPos++){
        difMas[curPos] = calloc(i, sizeof(double));
        for (int j = 0; j < i; j++)
            difMas[curPos][j] = splitDiff(difMas[curPos - 1][j], difMas[curPos - 1][j + 1],
                                          difMas[0][j], difMas[0][j - 1 + curPos]);
    }

    for (int i = 0; i < polynomDegree + 1; i++){
        for (int j = 0; j < polynomDegree + 2 - i; j++)
            if (difMas[j][i] == INFINITY || difMas[j][i] == -INFINITY){
                for (int i = 0; i < polynomDegree + 2; i++)
                    free(difMas[i]);
                free(difMas);
                return ERROR;
            }
    }

    // Расчёт полинома
    double finalPolynom = difMas[1][0], compGap = 1;
    for (int i = 0; i < polynomDegree; i++)
    {
        for (int j = 0; j <= i; j++){
            compGap *= findX - difMas[0][j];
        }
        compGap *= difMas[i + 2][0];
        finalPolynom += compGap;
        compGap = 1;
    }

    for (int i = 0; i < polynomDegree + 2; i++)
        free(difMas[i]);
    free(difMas);

    *foundY = finalPolynom;

    return 0;
}

int halfAlg(tableT *table){
    int position = -1;
    for (int i = 0; i < table->dotsNum - 1; i++){
        if ((table->yArgs[i] <= 0 && table->yArgs[i + 1] >= 0) || (table->yArgs[i] >= 0 && table->yArgs[i + 1] <= 0)){
            position = i;
            break;
        }
    }
    if (position == -1){
        printf("К несчастью, функция не имеет корней на заданном отрезке. Завершение программы...");
        return ERROR;
    }

    printf("Обнаружен корень на отрезке: x = %.3lf; y = %.3lf -> x = %.3lf; y = %.3lf\n\n", table->xArgs[position],
           table->yArgs[position], table->xArgs[position + 1], table->yArgs[position + 1]);

    if (!table->yArgs[position] || !table->yArgs[position + 1]){
        printf("Решение тривиально, ответ уже дан в таблице :(\n\n");
        return 0;
    }

    double leftSide = table->xArgs[position], rightSide = table->xArgs[position + 1];
    double newX, newY, rightY = table->yArgs[position + 1],
            leftY = table->yArgs[position];
    newX = (leftSide + rightSide) / 2;
    interpNuPolAlg(table, newX, 2, &newY);
    int helpErr = 0;
    //while (fabs(leftY) > EPS && fabs(rightY) > EPS && helpErr < 1000){
    while (fabs((leftSide - rightSide)/newX) > EPS){
        newX = (leftSide + rightSide) / 2;
        interpNuPolAlg(table, newX, 2, &newY);
        if (newY * leftY < 0){
            rightY = newY;
            rightSide = newX;
        }
        else if (newY * rightY < 0){
            leftY = newY;
            leftSide = newX;
        }
        helpErr++;
    }

    if (helpErr == 100000){
        printf("Задача не разрешилась за 100000 итераций.\n");
        return 0;
    }

    if (fabs(leftY) < EPS)
        newX = leftSide;
    else if (fabs(rightY) < EPS)
        newX = rightSide;

    printf("Корень, определённый методом половинного деления на отрезке, равен: %lf", newX);

    return 0;
}

int reverseInterpolationAlg(tableT *table, int polynomDegree){
    printf("\n\nНайдём корень обратной интерполяцией.");

    double *saveargs = table->xArgs;
    table->xArgs = table->yArgs;
    table->yArgs = saveargs;
    saveargs = NULL;

    printf("Поменяем местами значения ординат и абсцисс...\n");

    printf("И зададим искомой величиной для поиска в алгоритме, предоставленном выше, нуль:\n\n");

    int check = interpolationAlg(table, 0, polynomDegree);
    if (check)
        return ERROR;

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

    printf("Принятая таблица:\n");
    printTableT(table);

    fclose(tableFile);
    printf("Будьте добры, введите x и y: ");
    double findX, findY;
    int check = scanf("%lf %lf", &findX, &findY);

    if (check != 2){
        return ERROR;
    }
    printf("Будьте добры, введите степени полиномов(nx и ny): ");
    int polynomDegreeX, polynomDegreeY;
    check = scanf("%d %d", &polynomDegreeX, &polynomDegreeY);

    if (check != 1 || polynomDegreeX <= 0 || polynomDegreeY <= 0){
        return ERROR;
    }
    /*
    check = 0;

    check = interpolationAlg(&table, findX, polynomDegree);
    if (check)
        return ERROR;
*/
    freeTableT(&table);
    return 0;
}

