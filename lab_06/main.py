table = [[1, 2, 3, 4, 5, 6], [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]]
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


def main():
    yValues = table[1]
    xValues = table[0]

    firstColumn = leftSideDerivative(yValues)
    print("LeftSideDerivative:", firstColumn)

    secondColumn = centerDerivative(yValues)
    print("CenterDerivative:", secondColumn)

    print()
    print()

    fifthColumn = diffSecondDerivative(yValues)
    print("DiffSecondDerivative:", fifthColumn)


main()
