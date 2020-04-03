tableName = "table.txt"


def matrLeftX(xCoordinates, k, m, weight, N):
    back = 0
    for i in range(N):
        back += weight[i] * pow(xCoordinates[i], k + m)
    return back


def matrRightY(xCoordinates, yCoordinates, k, weight, N):
    back = 0
    for i in range(N):
        back += weight[i] * yCoordinates[i] * pow(xCoordinates[i], k)

    return back


def gaussMethod(matrix):
    for col in range(len(matrix[0])):
        for row in range(col + 1, len(matrix)):
            r = [(rowValue * (-(matrix[row][col] / matrix[col][col]))) for rowValue in matrix[col]]
            matrix[row] = [sum(pair) for pair in zip(matrix[row], r)]
    ans = []
    matrix.reverse()
    for sol in range(len(matrix)):
        if sol == 0:
            ans.append(matrix[sol][-1] / matrix[sol][-2])
        else:
            inner = 0
            for x in range(sol):
                inner += (ans[x] * matrix[sol][-2 - x])
            ans.append((matrix[sol][-1] - inner) / matrix[sol][-sol - 2])
    ans.reverse()
    return ans


def makeMatrixOfSLAE(matrix, xCoordinates, yCoordinates, weight, degree):
    N = len(xCoordinates)
    for k in range(degree + 1):
        matrix.append([])
        for m in range(degree + 1):
            matrix[k].append(matrLeftX(xCoordinates, k, m, weight, N))
        matrix[k].append(matrRightY(xCoordinates, yCoordinates, k, weight, N))

def changeWeight(a, b, c):
    print("В разработке")


def main():
    file = open(tableName, 'r')

    xCoordinates = []
    yCoordinates = []
    weight = []
    i = 0

    print("Принятая таблица:\n╔════════════════════╦════════════════════╦════════════════════╗")
    print("║{:^20}║{:^20}║{:^20}║".format('x', 'y', 'p'))
    for line in file:
        print("╠════════════════════╬════════════════════╬════════════════════╣")
        splited = line.split()
        xCoordinates.append(int(splited[0]))
        yCoordinates.append(int(splited[1]))
        weight.append(int(splited[2]))
        print("║{:^20}║{:^20}║{:^20}║ #{}".format(splited[0], splited[1], splited[2], i))
        i += 1
    file.close()
    print("╚════════════════════╩════════════════════╩════════════════════╝\n(Номера в таблице предоставлены для удобного форматирования по выбранному номеру веса точки)")
    print("Чего вы желаете?\n1. Изменить веса в таблице по номеру точки\n2. Получить результат работы программы")
    choice = 0
    while choice <= 0 or choice >= 3:
        try:
            choice = int(input("Ваш выбор (цифра варианта): "))
        except Exception:
            print("Невозможно считать заданное значение. Пожалуйста, повторите попытку")
    if choice == 1:
        changeWeight(xCoordinates, yCoordinates, weight)

    degree = -1
    while degree < 0:
        try:
            degree = int(input("Введите степень аппроксимирующего полинома: "))
        except Exception:
            print("Невозможно считать заданное значение. Пожалуйста, повторите попытку")

    matrix = list()
    makeMatrixOfSLAE(matrix, xCoordinates, yCoordinates, weight, degree)
    print(matrix)
    decision = gaussMethod(matrix)
    print(decision)



main()