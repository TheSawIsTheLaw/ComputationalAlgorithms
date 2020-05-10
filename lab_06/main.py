table = [[1, 2, 3, 4, 5, 6], [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]]

tableTwo = [[1, 2, 3, 4], [1, 4.925, 12.514, 24.251]]
# Абажаю хардкод)))))


def leftSideDerivative(yValues):
    answer = ['-', ]

    for i in range(1, len(yValues)):
        answer.append(yValues[i] - yValues[i - 1])

    return answer


def centerDerivative(yValues):
    answer = ['-']

    for i in range(1, len(yValues) - 1):
        answer.append((yValues[i + 1] - yValues[i - 1]) / 2)

    answer.append('-')
    return answer


def diffSecondDerivative(yValues):
    answer = ['-']

    for i in range(1, len(yValues) - 1):
        answer.append((yValues[i - 1] - 2 * yValues[i] + yValues[i + 1]))

    answer.append('-')
    return answer


def rungeDerivativeLeft(yValues):
    answer = ['-', '-']

    for i in range(2, len(yValues)):
        fStepY = yValues[i] - yValues[i - 1]
        sStepY = (yValues[i] - yValues[i - 2]) / 2
        answer.append(fStepY + fStepY - sStepY)

    return answer


def rungeDerivativeRight(yValues):
    answer = []

    for i in range(len(yValues) - 2):
        fStepY = yValues[i + 1] - yValues[i]
        sStepY = (yValues[i + 2] - yValues[i]) / 2
        answer.append(fStepY + fStepY - sStepY)

    answer.append("-")
    answer.append("-")
    return answer


def varsDerivative(yValues, xValues):
    result = []

    for i in range(len(yValues) - 1):
        curEtha = (1 / yValues[i] - 1 / yValues[i + 1]) / (1 / xValues[i] - 1 / xValues[i + 1])
        result.append(yValues[i] * yValues[i] * curEtha / (xValues[i] * xValues[i]))

    result.append('-')
    return result


def main():
    yValues = table[1]
    xValues = table[0]

    firstColumn = leftSideDerivative(yValues)
    print("LeftSideDerivative:", firstColumn)

    secondColumn = centerDerivative(yValues)
    print("CenterDerivative:", secondColumn)

    thirdColumnRight = rungeDerivativeRight(yValues)
    print("RungeDerivativeRight:", thirdColumnRight)

    thirdColumnLeft = rungeDerivativeLeft(yValues)
    print("RungeDerivativeLeft:", thirdColumnLeft)

    fourthColumn = varsDerivative(yValues, xValues)
    print("VarsDevirative:", fourthColumn)

    fifthColumn = diffSecondDerivative(yValues)
    print("DiffSecondDerivative:", fifthColumn)


main()
