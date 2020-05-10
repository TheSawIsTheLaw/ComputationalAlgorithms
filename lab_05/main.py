import numpy as np
from numpy.polynomial.legendre import *
from numpy.linalg import eigvalsh
from math import cos, sin, exp, pi


def legendre(deg):
    c = np.array([0]*deg + [1])
    m = legcompanion(c)
    x = eigvalsh(m)
    dy = legval(x, c)
    df = legval(x, legder(c))
    x -= dy/df
    fm = legval(x, c[1:])
    fm /= np.abs(fm).max()
    df /= np.abs(df).max()
    w = 1/(fm * df)
    w = (w + w[::-1])/2
    x = (x - x[::-1])/2
    w *= 2. / w.sum()
    return x, w


def toResolvation(parameter):
    subcurFunction = lambda x, y: 2 * cos(x) / (1 - (sin(x) ** 2) * (cos(y) ** 2))
    curFunction = lambda x, y: (4 / pi) * (1 - exp(-parameter * subcurFunction(x, y))) * cos(x) * sin(x)
    return curFunction


def Simpson(curFunction, start, end, num):
    h = (end - start) / (num - 1)
    x = start
    output = 0
    for i in range((num - 1) // 2):
        output += curFunction(x) + 4 * curFunction(x + h) + curFunction(x + 2 * h)
        x += 2 * h
    output *= h / 3
    return output


def toSingleTemp(twoParSolvation, imput):
    return lambda x: twoParSolvation(imput, x)


def TempToX(parT, start, end):
    return (end + start) / 2 + (end - start) * parT / 2


def Gauss(curFunction, end, start, num):
    legArr = legendre(num)
    output = 0
    for i in range(num):
        output += (start - end) / 2 * legArr[1][i] * curFunction(TempToX(legArr[0][i], start, end))
    return output


def twoParTag(curFunction, limits, num, integrators):
    interior = lambda x: integrators[1](toSingleTemp(curFunction, x), limits[1][0], limits[1][1], num[1])
    return integrators[0](interior, limits[0][0], limits[0][1], num[0])


def main():
    parameter = int(input("Par: "))
    NSimpson = int(input("n(Simpson): "))
    MGauss = int(input("m(Gauss): "))
    output = twoParTag(toResolvation(parameter), ((0, pi / 2), (0, pi / 2)), (NSimpson, MGauss), (Gauss, Gauss))
    print(output)


main()