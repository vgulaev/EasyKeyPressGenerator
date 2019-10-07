// VGPiano.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// #include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h> 
#include <stdlib.h>

BOOL WINAPI consoleHandler(DWORD signal) {

	if (signal == CTRL_C_EVENT)
		printf("Ctrl-C handled\n"); // do cleanup
	exit(1);
	return TRUE;
}

bool presskey(WORD sym) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	ip.ki.wVk = sym; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return true;
}

int main()
{
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		printf("\nERROR: Could not set control handler");
		return 1;
	}

	const char* text =
		"This text is pretty long, but will be "
		"concatenated into just a single string. "
		"The disadvantage is that you have to quote "
		"each part, and newlines must be literal as "
		"usual.";

	srand(time(0));

	HKL currentKBL = GetKeyboardLayout(0);
	int i = 0;
	Sleep(5000);

	while (true == presskey(VkKeyScanEx(text[i], currentKBL))) {
		std::cout << (WORD)text[i] << text[i] <<"\n";
		i += 1;
		Sleep(100 + (rand() % 400));
	};

	std::cout << "Hello World!\n";

	return 0;
}
