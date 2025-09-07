#ifdef _WIN32
#include <windows.h>

static void setCursorPos(int x = 0, int y = 0)
{
	HANDLE handle;
	COORD coordinates;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(handle, coordinates);
}
static int getConsoleHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int ret;
	ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (ret)
	{
		return csbi.dwSize.Y;
	}
}
static int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int ret;
	ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (ret)
	{
		return csbi.dwSize.X;
	}

}
static void clearConsole() {
	system("cls");
}
#endif

#pragma once
class ConsoleUtils
{
	
};

