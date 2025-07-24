#pragma once
#include <windows.h>

enum Colors {
        Black,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Brown,
        LightGray,
        DarkGray,
        LightBlue,
        LightGreen,
        LightCyan,
        LightRed,
        LightMagenta,
        Yellow,
        White
    };
static void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
static void Reset() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::LightGray);
    }
