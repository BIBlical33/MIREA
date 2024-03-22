from math import exp, sqrt
from random import random
from array import array
from matplotlib import pyplot
import numpy

INCORRECT_DATA = "INCORRECT_DATA"


def float_input():
    try:
        return float(input())
    except:
        print("Incorrect data entered")
        return INCORRECT_DATA


def int_input():
    try:
        return int(input())
    except:
        print("Incorrect data entered")
        return INCORRECT_DATA


def task1_3():
    x = 5 >= 2
    A = {1, 3, 7, 8}
    B = {2, 4, 5, 10, "apple"}
    C = A & B
    df = ("Крамаренко Илья", 18, "м")
    z = "type"
    D = [1, "title", 2, "content"]
    print(x, str(type(x))[8:-2])
    print(A, str(type(A))[8:-2])
    print(B, str(type(B))[8:-2])
    print(C, str(type(C))[8:-2])
    print(df, str(type(df))[8:-2])
    print(z, str(type(z))[8:-2])
    print(D, str(type(D))[8:-2])


def task2_3():
    print("Enter x")
    x = float_input()
    if x != INCORRECT_DATA:
        print("x belongs to ", end="")
        if x < -5:
            print("(-infinity, -5)")
        elif x > 5:
            print("(5, +infinity)")
        else:
            print("[-5;5]")


def task3_3_1():
    number = 10
    while number >= 1:
        print(number)
        number -= 3


def task3_3_2():
    human_characteristics = [
        "Name",
        "Surname",
        "Age",
        "Gender",
        "Address",
        "Phone Number",
        "Email",
        "Profession",
        "Education",
        "Hobby",
        "Height",
        "Weight",
        "Blood Type",
        "Eye Color",
        "Hair Color",
        "Nationality",
        "Religious Beliefs",
        "Marital Status",
        "Languages Spoken",
    ]
    print("Human Characteristics:")
    for characteristic in human_characteristics:
        print(characteristic)


def task3_3_3():
    numbers = list()
    for number in range(2, 16):
        numbers.append(number)
    print(numbers)


def task3_3_4():
    for number in range(105, 4, -25):
        print(number, end=" ")
    print()


def array_initialization_with_keyboard(array_size):
    user_array = array("d")
    print(f"Enter {array_size} numbers in separate lines")
    for i in range(array_size):
        value = int_input()
        while value == INCORRECT_DATA:
            print("Please enter a numer")
            value = int_input()
        user_array.append(value)
    return user_array


def print_array(array):
    for element in array:
        print(element, end=" ")
    print()


def task3_3_5():
    print("Enter array size")
    x_size = int_input()
    if x_size > 0:
        x = array_initialization_with_keyboard(x_size)
        if len(x) % 2 == 0:
            x[::2] = x[-2::-2]
        else:
            x[:-1:2] = x[-2::-2]
            print_array(x)
    else:
        print("Incorrect input")


def task4_3_1():
    print("Enter array size")
    numbers_size = int_input()
    if numbers_size > 0:
        numbers = array("d")
        for i in range(numbers_size):
            rand_number = random()
            while rand_number == 0:
                rand_number = random()
            numbers.append(rand_number)
        figure = pyplot.figure(figsize=(10, 6))
        pyplot.xlabel("number")
        pyplot.ylabel("index")
        indexes_list_of_numbers = list(range(len(numbers)))
        pyplot.scatter(numbers, indexes_list_of_numbers)
        mean = numpy.mean(numbers)
        median = numpy.median(numbers)
        print("Array's mean =", mean)
        print("Array's median =", median)
        if mean > median:
            print("Array's mean is larger")
        elif mean < median:
            print("Array's median is larger")
        else:
            print("The values are equal")
        pyplot.show()
    else:
        print("Incorrect data entered")


def f(x):
    return sqrt(1 + numpy.exp(1) ** sqrt(x) + numpy.cos(x * x)) / abs(
        1 - numpy.sin(x) ** 3
    ) + numpy.log(abs(2 * x))


def task4_3_2():
    f_returning_values = numpy.zeros(
        10
    )
    indexes = []

    # Заполняем массив f_returning_values значениями, возвращаемыми функцией f(x)
    for x in range(10):
        f_returning_values[x] = f(x)

    # Вычисляем первую половину массива f_returning_values
    first_half_of_f_returning_values = f_returning_values[
        : len(f_returning_values) // 2
    ]

    # Создаем массив w для индексов
    w = numpy.arange(1, len(first_half_of_f_returning_values) + 1)

    # Строим график для всех значений f(x)
    pyplot.plot(f_returning_values)
    pyplot.xlabel("x")
    pyplot.ylabel("f(x)")
    pyplot.show()

    # Строим диаграмму рассеяния для первой половины значений f(x)
    pyplot.scatter(w, first_half_of_f_returning_values)
    pyplot.xlabel("x")
    pyplot.ylabel("f(x)")
    pyplot.show()


def task4_3_3():
    pass


def main():
    print("Greetings. The program was written by Ilya Kramarenko, IVBO-10-23.")
    command = "1"
    while command != 0:
        print("Enter task number or '0' for exit")
        command = input()
        if command == "1.3":
            task1_3()
        elif command == "2.3":
            task2_3()
        elif command == "3.3.1":
            task3_3_1()
        elif command == "3.3.2":
            task3_3_2()
        elif command == "3.3.3":
            task3_3_3()
        elif command == "3.3.4":
            task3_3_4()
        elif command == "3.3.5":
            task3_3_5()
        elif command == "4.3.1":
            task4_3_1()
        elif command == "4.3.2":
            task4_3_2()
        elif command == "4.3.3":
            task4_3_3()
        else:
            print("Incorrect task number entered")


if __name__ == "__main__":
    main()