#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MaxSize 4096
#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<WinSock2.h>
#include<algorithm>
#include "SOCKET.h"
#define information "user_information.txt"
#define WORDS "word.txt"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int SOCKET_CREATE()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	int err = WSAStartup(ver, &dat);
	cout << err << endl;
	if (SOCKET_ERROR == err)
	{
		cout << "´íÎó£¡..." << endl;
		return 0;
	}
	return 1;

}
