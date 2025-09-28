#include <windows.h>
#include <string>

HWND hEdit;
std::string expression;

void AppendToExpression(const std::string& value) {
    expression += value;
    SetWindowText(hEdit, expression.c_str());
}

void ClearExpression() {
    expression.clear();
    SetWindowText(hEdit, "");
}

void EvaluateExpression() {
    double result = 0;
    char op;
    double a, b;
    if (sscanf(expression.c_str(), "%lf%c%lf", &a, &op, &b) == 3) {
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = b != 0 ? a / b : 0; break;
        }
        expression = std::to_string(result);
        SetWindowText(hEdit, expression.c_str());
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                                 10, 10, 260, 30, hwnd, nullptr, nullptr, nullptr);

            const char* buttons[] = { "7", "8", "9", "/", "4", "5", "6", "*",
                                      "1", "2", "3", "-", "0", "C", "=", "+" };
            for (int i = 0; i < 16; ++i) {
                CreateWindow("BUTTON", buttons[i], WS_CHILD | WS_VISIBLE,
                             10 + (i % 4) * 65, 50 + (i / 4) * 40, 60, 35,
                             hwnd, (HMENU)(100 + i), nullptr, nullptr);
            }
            break;
        }
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id >= 100 && id < 116) {
                const char* btn = reinterpret_cast<const char*>(SendMessage((HWND)lParam, WM_GETTEXT, 0, 0));
                std::string value = btn ? btn : "";

                if (value == "=") EvaluateExpression();
                else if (value == "C") ClearExpression();
                else AppendToExpression(value);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalcClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CalcClass", "Win32 Calculator",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             300, 250, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
