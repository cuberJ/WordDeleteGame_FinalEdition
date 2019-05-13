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
	int word_number = 0;//创造的词的数量
	int level;
	int id = 1;
	vector<vector<string>> lib;//存储所有的已有词库，lib[i]表示的是单词长度为i-1的所有词
	struct Basic_information build;

	void Create_Builder();
	int Add_new_word();
	void Write_In_Word(int number);
	int Word_Check(string word);//d判断是否有重复词语
	void Log_In();
};




#endif /* Builder_work_hpp */
