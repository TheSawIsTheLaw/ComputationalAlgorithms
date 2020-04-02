#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x, double y){
    return x * x + y * y;
}

int main(){
    FILE *file = fopen("table.txt", "w");

    double start, stop, step;
    scanf("%lf%lf%lf", &start, &stop, &step);

    fprintf(file, "number of dots: %d\n\n", (int)(((stop - start + 1) / step)*((stop - start + 1) / step) + 1));

    for (double curX = start; curX <= stop; curX += step){
        for (double curY = start; curY <= stop; curY += step){
            fprintf(file, "%lf %lf %lf\n", curX, curY, func(curX, curY));
        }
    }
    fclose(file);
}

