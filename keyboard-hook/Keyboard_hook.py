# Copyright 2025, github.com/BIBlical33
#
# Keyboard hook to past into Aurora
#
# Aurora is a dumb program in which insertion is prohibited,
# and where object-oriented programming tasks were solved in MIREA
#
# License: GNU General Public License v3.0
# See: https://www.gnu.org/licenses/gpl-3.0.html

import time
import pyautogui

time.sleep(5)

with open("hook.cc", "r") as file:
    for char in file.read():
        time.sleep(0.03551)
        if char == "#":
            pyautogui.hotkey("shift", "3")
        elif char == "(":
            pyautogui.press("(")
        elif char == ")":
            pyautogui.press(")")
        elif char == "{":
            pyautogui.press("{")
        elif char == "}":
            pyautogui.press("}")
        elif char == " ":
            pyautogui.press("space")
        elif char == "\n":
            pyautogui.press("enter")
        elif char == "\t":
            pass
        elif char == "<":
            pyautogui.hotkey("shift", ",")
        elif char == ">":
            pyautogui.hotkey("shift", ".")
        elif char == ";":
            pyautogui.press(";")
        elif char == '"':
            pyautogui.press('"')
        elif char == "'":
            pyautogui.press("'")
        elif char == ":":
            pyautogui.hotkey("shift", ";")
        elif char == "!":
            pyautogui.hotkey("shift", "1")
        elif char == "*":
            pyautogui.hotkey("shift", "8")
        elif char == "/":
            pyautogui.press("/")
        elif char == ".":
            pyautogui.press(".")
        elif char == "%":
            pyautogui.hotkey("shift", "5")
        elif char == "=":
            pyautogui.press("=")
        elif char == "+":
            pyautogui.hotkey("shift", "=")
        elif char == "-":
            pyautogui.press("-")
        elif char == "_":
            pyautogui.hotkey("shift", "-")
        elif char == "\\":
            pyautogui.press("\\")
        elif char == "|":
            pyautogui.hotkey("shift", "\\")
        elif char == "[":
            pyautogui.press("[")
        elif char == "]":
            pyautogui.press("]")
        elif char == ",":
            pyautogui.press(",")
        else:
            pyautogui.press(char)
