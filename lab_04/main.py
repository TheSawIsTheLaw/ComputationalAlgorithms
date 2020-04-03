tableName = "table.txt"


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
        xCoordinates.append(splited[0])
        yCoordinates.append(splited[1])
        weight.append(splited[2])
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
    if choice == 2:
        changeWeight(xCoordinates, yCoordinates, weight)

    degree = -1
    while degree < 0:
        try:
            degree = int(input("Введите степень аппроксимирующего полинома: "))
        except Exception:
            print("Невозможно считать заданное значение. Пожалуйста, повторите попытку")

    

main()