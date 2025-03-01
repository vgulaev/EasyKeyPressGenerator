﻿// VGPiano.cpp
//
// #include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include <fstream>

BOOL WINAPI consoleHandler(DWORD signal) {

	if (signal == CTRL_C_EVENT) {
		printf("Ctrl-C handled\n"); // do cleanup
		system("pause");
		exit(1);
	}
	return TRUE;
}

void presskey(WORD sym) {
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
}

int main()
{
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		printf("\nERROR: Could not set control handler");
		return 1;
	}

	std::ifstream in("input.txt");
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	const char* text = contents.c_str();
	std::cout << strlen(text);

	srand(time(0));

	HKL currentKBL = GetKeyboardLayout(0);
	int i = 0;
	Sleep(5000);

	while (true) {
		i += 1;
		if (10 == (WORD)text[i]) continue;
		presskey(VkKeyScanEx(text[i], currentKBL));
		std::cout << (WORD)text[i] << text[i] <<"\n";
		Sleep(100 + (rand() % 800));
	};

	std::cout << "Hello World!\n";

	return 0;
}
