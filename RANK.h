#pragma once
#ifndef Rank_The_User_hpp
#define Rank_The_User_hpp

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MaxSize 4096

#include <stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include"GAME.h"
#include "PLAYER.h"
#include"SOCKET.h"
#include"BUILDER.h"
#define information "user_information.txt"
#define WORD "WORDS.txt"
using namespace std;

void Rank_Player(SOCKET _sock);
void Rank_Builder(SOCKET _sock);


#endif /* Rank_The_User_hpp */