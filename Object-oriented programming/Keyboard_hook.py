import time
import pyautogui

# Задержка перед началом симуляции (время для фокусировки на нужном окне)
time.sleep(4)

with open("hook.cc", "r") as file:
    for char in file.read():
        time.sleep(0.08)
        if char == "#":
            pyautogui.hotkey('shift', '3')
        elif char == "(":
            pyautogui.press('(')
        elif char == ")":
            pyautogui.press(')')
        elif char == "{":
            pyautogui.press('{')
        elif char == "}":
            pyautogui.press('}')
        elif char == " ":
            pyautogui.press('space')
        elif char == "\n":
            pyautogui.press('enter')
        elif char == "\t":
            pass
        elif char == "<":
            pyautogui.hotkey('shift', ',')
        elif char == ">":
            pyautogui.hotkey('shift', '.')
        elif char == ";":
            pyautogui.press(';')
        elif char == '"':
            pyautogui.press("\"")
        elif char == "'":
            pyautogui.press("'")
        elif char == ":":
            pyautogui.hotkey('shift', ';')
        elif char == "!":
            pyautogui.hotkey('shift', '1')
        elif char == "*":
            pyautogui.hotkey('shift', '8')
        elif char == "/":
            pyautogui.press('/')
        elif char == ".":
            pyautogui.press('.')
        elif char == "%":
            pyautogui.hotkey('shift', '5')
        elif char == "=":
            pyautogui.press('=')
        elif char == "+":
            pyautogui.hotkey('shift', '=')
        elif char == "-":
            pyautogui.press('-')
        elif char == "_":
            pyautogui.hotkey('shift', '-')
        elif char == "\\":
            pyautogui.press('\\')
        elif char == "|":
            pyautogui.hotkey('shift', '\\')
        elif char == "[":
            pyautogui.press('[')
        elif char == "]":
            pyautogui.press(']')
        elif char == ",":
            pyautogui.press(',')
        else:
            pyautogui.press(char)