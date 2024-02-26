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


def list_initialization_with_keyboard(list_size):
    user_list = list()
    print(f"Enter {list_size} values in separate lines")
    for value in range(list_size):
        user_list.append(input())
    return user_list


def task3_3_5():
    print("Enter list size")
    x_size = int_input()
    if x_size != INCORRECT_DATA:
        x = list_initialization_with_keyboard(x_size)
        print(x)
        x = x[1::2]
        print(x)

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
        else:
            print("Incorrect task number entered")


if __name__ == "__main__":
    main()