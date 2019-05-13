#ifndef SOCKET_h
#define SOCKET_h

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
#include "GAME.h"
#define information "user_information.txt"
#define WORDS "word.txt"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int SOCKET_CREATE();





#endif // !SOCKET_h
