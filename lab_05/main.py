from numpy.polynomial.legendre import *
from math import pi

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


def main():
    mNet = int(input("Set number M in netDif: "))
    nNet = int(input("Set number N in netDif: "))

    table = fillTableFromFile()

    legArr = leggauss(mNet)
    print("Legendre roots of polynom " + str(mNet) + " degree: ", end = ' ')
    for i in legArr[0]: print(i, end=' ')
    print()
    print("A for Gauss: ", end = ' ')
    for i in legArr[1]: print(i, end = ' ')




main()