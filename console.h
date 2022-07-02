#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

// Hàm thay đổi kích cỡ của khung cmd với tham số truyền vào là chiều cao, chiều rộng.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//Hàm xóa màn hình.
//void XoaManHinh()
//{
//	HANDLE hOut;
//	COORD Position;
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	Position.X = 0;
//	Position.Y = 0;
//	SetConsoleCursorPosition(hOut, Position);
//}

// Hàm lấy Key từ bàn phím
/* GetAsyncKeyState(VK_ESCAPE) => bắt sự kiện phím Esc */

// Hàm tự viết
void ToMau(int x, int y, char* a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}

void SetColor(WORD color)  // tô màu chữ
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

 void XoaManHinh()
 {
     HANDLE hStdOut;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     DWORD count;
     DWORD cellCount;
     COORD homeCoords = { 0, 0 };

     hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     if (hStdOut == INVALID_HANDLE_VALUE) return;

     /* Get the number of cells in the current buffer */
     if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
     cellCount = csbi.dwSize.X * csbi.dwSize.Y;

     /* Fill the entire buffer with spaces */
     if (!FillConsoleOutputCharacter(
         hStdOut,
         (TCHAR)' ',
         cellCount,
         homeCoords,
         &count
     )) return;

     /* Fill the entire buffer with the current colors and attributes */
     if (!FillConsoleOutputAttribute(
         hStdOut,
         csbi.wAttributes,
         cellCount,
         homeCoords,
         &count
     )) return;

     /* Move the cursor home */
     SetConsoleCursorPosition(hStdOut, homeCoords);
 }
 
 
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}
// hình như hàm này cũng tường tự
/*void Nocursortype()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}*/

void AnConTroChuot()
{
    ShowCur(0);
}

void HienConTroChuot()
{
    ShowCur(1);
}
