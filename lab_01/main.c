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

#define FILE_NAME "table.txt"
#define ERROR 666


int readToTable(){
    return 0;
}

int interpolationAlg(){
    return 0;
}

int halfAlg(){
    return 0;
}

int reverseInterpolationAlg(){
    return 0;
}

int main(){
    FILE *tableFile = fopen(FILE_NAME, "r");
    if (!tableFile){
        printf("Файл не найден.\n");
        return ERROR;
    }

    readToTable();

    interpolationAlg();

    halfAlg();

    reverseInterpolationAlg();

    return 0;
}
