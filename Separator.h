#pragma once
#include <iostream>
#include "SetConsoleColors.h"
static void Separator() {
	SetColor(Yellow);
	std::cout << "----------------------------------------------------------\n";
	Reset();
}