#pragma once
#ifndef Builder_work_hpp
#define Builder_work_hpp

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
#include "PLAYER.h"
#include"GAME.h"
#include"SOCKET.h"
//#include "Rank_The_User.hpp"
#define information "user_information.txt"
#define WORD "WORDS.txt"
using namespace std;

class BUILDER :public USER {
public:
	int word_number = 0;//����Ĵʵ�����
	int level;
	int id = 1;
	vector<vector<string>> lib;//�洢���е����дʿ⣬lib[i]��ʾ���ǵ��ʳ���Ϊi-1�����д�
	struct Basic_information build;

	void Create_Builder();
	int Add_new_word();
	void Write_In_Word(int number);
	int Word_Check(string word);//d�ж��Ƿ����ظ�����
	void Log_In();
};




#endif /* Builder_work_hpp */
