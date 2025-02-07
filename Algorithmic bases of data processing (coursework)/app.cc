#include <windows.h>

#include <stdexcept>

#include "conversion_between_number_systems.h"

// Обработчик сообщений окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_CREATE: {
      // Создание элементов интерфейса
      int labelWidth = 200;
      int fieldWidth = 250;
      int height = 25;
      int padding = 5;

      CreateWindow(L"STATIC", L"Enter number:", WS_VISIBLE | WS_CHILD, padding,
                   padding, labelWidth, height, hwnd, NULL, NULL, NULL);
      CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                   padding + labelWidth, padding, fieldWidth, height, hwnd,
                   (HMENU)1, NULL, NULL);

      CreateWindow(L"STATIC", L"Old base:", WS_VISIBLE | WS_CHILD, padding,
                   padding + height + padding, labelWidth, height, hwnd, NULL,
                   NULL, NULL);
      CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                   padding + labelWidth, padding + height + padding, fieldWidth,
                   height, hwnd, (HMENU)2, NULL, NULL);

      CreateWindow(L"STATIC", L"New base:", WS_VISIBLE | WS_CHILD, padding,
                   padding + 2 * (height + padding), labelWidth, height, hwnd,
                   NULL, NULL, NULL);
      CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                   padding + labelWidth, padding + 2 * (height + padding),
                   fieldWidth, height, hwnd, (HMENU)3, NULL, NULL);

      CreateWindow(L"BUTTON", L"Convert", WS_VISIBLE | WS_CHILD,
                   padding + labelWidth, padding + 3 * (height + padding),
                   fieldWidth, height, hwnd, (HMENU)4, NULL, NULL);

      CreateWindow(L"STATIC", L"Result:", WS_VISIBLE | WS_CHILD, padding,
                   padding + 4 * (height + padding), labelWidth, height, hwnd,
                   NULL, NULL, NULL);
      CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                   padding + labelWidth, padding + 4 * (height + padding),
                   fieldWidth, height, hwnd, (HMENU)5, NULL, NULL);
      return 0;
    }
    case WM_COMMAND:
      if (LOWORD(wParam) == 4)  // Кнопка "Convert"
      {
        // Получение данных из полей
        wchar_t numberStr[100];
        GetWindowText(GetDlgItem(hwnd, 1), numberStr, 100);

        wchar_t fromBaseStr[10];
        GetWindowText(GetDlgItem(hwnd, 2), fromBaseStr, 10);
        int fromBase = _wtoi(fromBaseStr);  // Convert wchar_t to int

        wchar_t toBaseStr[10];
        GetWindowText(GetDlgItem(hwnd, 3), toBaseStr, 10);
        int toBase = _wtoi(toBaseStr);  // Convert wchar_t to int

        // Конвертация
        try {
          std::string numberString = std::string(
              numberStr,
              numberStr + wcslen(numberStr));  // Convert wchar_t to std::string
          std::string result =
              conversion_between_number_systems::ConversionBetweenNumberSystems(
                  numberString, fromBase, toBase);
          SetWindowText(GetDlgItem(hwnd, 5),
                        std::wstring(result.begin(), result.end()).c_str());
        } catch (const std::invalid_argument&) {
          MessageBox(hwnd, L"Invalid input!", L"Error", MB_OK | MB_ICONERROR);
        } catch (const std::out_of_range&) {
          MessageBox(hwnd, L"Number out of range!", L"Error",
                     MB_OK | MB_ICONERROR);
        }
      }
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Основная функция WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"ConversionApp";

  // Регистрация класса окна
  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Создание окна с фиксированным размером
  HWND hwnd = CreateWindowEx(
      0, CLASS_NAME, L"Converter",
      WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,
      CW_USEDEFAULT, 280, 500, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL) {
    return 0;
  }

  // Устанавливаем минимальный и максимальный размер окна одинаковыми
  SetWindowPos(hwnd, NULL, 0, 0, 500, 200,
               SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

  ShowWindow(hwnd, nCmdShow);

  // Цикл сообщений
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
