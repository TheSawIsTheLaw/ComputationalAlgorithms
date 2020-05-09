from numpy.polynomial.legendre import *
from math import pi

def main():
    mNet = int(input("Set number M in netDif: "))
    nNet = int(input("Set number N in netDif: "))

    legArr = leggauss(mNet)
    print("Legendre roots of polynom " + str(mNet) + " degree: ", end = ' ')
    for i in legArr[0]: print(i, end=' ')
    print()
    print("A for Gauss: ", end = ' ')
    for i in legArr[1]: print(i, end = ' ')



main()