#ifndef GAME_h
#define GAME_h

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

#define information "user_information.txt"
#define WORDS "word.txt"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

struct Basic_information {
	string name;
	string password;
	int id;//鉴别身份
	int floor = 1;
	int experience = 0;//经验值，每次根据关卡的难度进行累加
	int level = 1;//等级默认初始值为1，每次游戏的时候，连续答对10题，升级，最高40级
};

void send_(SOCKET sockClient, const char s[MaxSize]);

class USER {
public:
	string name;
	SOCKET _sock;
	string password;
	int id;//鉴别身份
	int floor = 1;//默认从第一关开始，总计16关
	int experience = 0;//经验值，每次根据关卡的难度进行累加,在构词者的类里是作为出题的题数
	int level = 1;//等级默认初始值为1，每次游戏的时候，连续答对10题，升级，最高40级

	int User_Check(string name, int id);//检测是否有重名的问题
	int Password_Check(string name, string password, int id);//检测密码是否正确
	void Write_In(vector<Basic_information>);//注册成功的用户的信息将被写入信息库
	vector<Basic_information> Read_in(vector<Basic_information> basic);//从数据库读取所有人的信息

	void Create_new_player();//针对选项1，创建新用户

	//void Chooes_Id(int id);//根据登录者的身份选择模式：创造词语/答题
	void Cancel_exist_user(int id);//删除存在的用户
};

#endif