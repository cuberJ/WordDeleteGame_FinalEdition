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
	int floor = 1;//Ĭ�ϴӵ�һ�ؿ�ʼ���ܼ�16��

	void Log_In();//��¼�����˺ţ�������Ϸ
	void Game_Contral();//������Ϸ�Ļ�������
	struct Basic_information Game_Start(struct Basic_information);//��ʼ��Ϸ,���շ���һ���ṹ��洢�����ҵ����ս���ʱ����Ϣ
	string Read_Word(int floor);//������ҵĹؿ���Ŀ��ȡ���ʵĳ��ȣ������������
	int Show_Control(int floor);//��Ϸ�����ݱ������Ƶ��ʵĳ��ֺ���ʧ,��������ҵ������ж��Ƿ����,���ϵĻ�����1
};

#endif /* Player_work_hpp */