from numpy.polynomial.legendre import *
from math import pi, cos, sin, exp

def fillTableFromFile():
    file = open("table.txt", 'r')
    xCoordinates = list()
    yCoordinates = list()
    for line in file:
        splited = line.split()
        xCoordinates.append(float(splited[0]))
        yCoordinates.append(float(splited[1]))
    file.close()
    return xCoordinates, yCoordinates


def func(x, y):
    return (1 - exp(- 2 * cos(x) / (1 - sin(x) * sin(x) * cos(y) * cos(y)))) * cos(x) * sin(x)


def main():
    nNet = int(input("Set number N in netDif: "))
    mNet = int(input("Set number M in netDif: "))

    yStep = (pi/2) / mNet

    table = fillTableFromFile()

    legArr = leggauss(mNet)
    print("Legendre roots of polynom " + str(mNet) + " degree: ", end = ' ')
    for i in legArr[0]:
        print(i, end=' ')
    print()
    print("A for Gauss: ", end = ' ')
    for i in legArr[1]:
        print(i, end = ' ')

    summary = 0
    for i in range(nNet):
        tempSum = 0
        for j in range(int(mNet / 2)):
            tempSum += func(legArr[0][2 * j], table[1][table[0].index(legArr[1][2 * j])])
            tempSum += 4 * func(legArr[0][2 * j + 1], table[1][table[0].index(legArr[1][2 * j + 1])])
            tempSum += func(legArr[0][2 * j + 2], table[1][table[0].index(legArr[1][2 * j + 2])])
        summary += tempSum * legArr[1][i] * (yStep / 3)

    print(summary)



main()