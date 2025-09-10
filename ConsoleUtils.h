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

static void remove_scrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

#endif

#pragma once
class ConsoleUtils
{
#ifdef _WIN32

	char getCharAtPosition(int x, int y) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		char ch;
		DWORD charsRead;

		// Wczytaj znak z okreœlonej pozycji
		COORD coord = { (SHORT)x, (SHORT)y };
		ReadConsoleOutputCharacterA(hConsole, &ch, 1, coord, &charsRead);

		return ch;  // Zwróæ odczytany znak
	}
#endif
};

