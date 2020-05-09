from matplotlib.pyplot import *

tableName = "table.txt"

file = open(tableName, 'r')

def showTable():
    xCoordinates = []
    yCoordinates = []

    for line in file:
        splited = line.split()
        xCoordinates.append(float(splited[0]))
        yCoordinates.append(float(splited[1]))
    file.close()

    plot(xCoordinates, yCoordinates, c = "red", label = "Epsilon(Tau)")
    legend()
    grid()
    xlabel('Epsilon')
    ylabel('Tau')
    show()


showTable()