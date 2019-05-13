#pragma once
#ifndef Player_work_hpp
#define Player_work_hpp

#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MaxSize 4096

#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<WinSock2.h>
#include<algorithm>
#include"GAME.h"
#define information "user_information.txt"
#define WORDS "word.txt"
using namespace std;

#pragma comment(lib, "ws2_32.lib")                     

class PLAYER :public USER {
public:
	int id = 0;
	int floor = 1;//默认从第一关开始，总计16关

	void Log_In();//登录已有账号，进行游戏
	void Game_Contral();//控制游戏的基本流程
	struct Basic_information Game_Start(struct Basic_information);//开始游戏,最终返回一个结构体存储这个玩家的最终结束时的信息
	string Read_Word(int floor);//根据玩家的关卡数目读取单词的长度，返回这个单词
	int Show_Control(int floor);//游戏的内容本身，控制单词的出现和消失,并根据玩家的输入判断是否符合,符合的话返回1
};

#endif /* Player_work_hpp */