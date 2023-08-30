#include <Windows.h>
#include <stdio.h>
#include <iostream>

// global variables
HWND hwnd;
HWND textDisplay;
HWND buttons[19];

HWND scienceButtons[7];

// prototypes
HWND CreateButton(LPCWSTR label, int x, int y, int width, int height, HWND parent, HINSTANCE hInstance, int id);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
