#pragma once

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
#include"RANK.h"
#include"BUILDER.h"
#include<WinSock2.h>
#include"SOCKET.h"
#define information "user_information.txt"
#define WORD "WORDS.txt"
using namespace std;

#pragma warning(disable:4996)
int send_int(SOCKET sockClient, int data)
{
	char sendBuf[MaxSize];
	char buffer[20];
	_itoa(data, buffer, 10);
	strcpy(sendBuf, buffer);
	cout << buffer << endl;
	int flag = send(sockClient, sendBuf, strlen(sendBuf), 0);
	return flag;
}

void send_string(SOCKET sock, string name)
{
	char sendBuf[MaxSize];
	char *buffer=(char*)name.c_str();
	strcpy(sendBuf, buffer);
	cout << buffer << endl;
	send(sock, sendBuf, strlen(sendBuf), 0);
}

bool Rank_Player_Level(Basic_information a, Basic_information b)//对两种玩家的p等级均可进行排名
{
	return a.level > b.level;
}

bool Rank_Player_experience(Basic_information a, Basic_information b)//对玩家是经验值排名，对创作者是进行出题数排名
{
	return a.experience > b.experience;
}

bool Rank_Player_floor(Basic_information a, Basic_information b)
{
	return a.floor > b.floor;
}


void Rank_Player(SOCKET _sock)//对玩家的三种成绩进行排序
{
	send_(_sock,"Which rank you want to search?\n1.level\n2.experience\n3.floor\n4.quit\n" );
	send_(_sock, "#");
	char choose_temp[MaxSize];
	int temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
	int choose = atoi(choose_temp);
	vector<Basic_information> basic;//存储数据库读入的所有人员信息
	struct Basic_information temp;

	ifstream fin(information);
	while (fin >> temp.name)
	{
		fin >> temp.password;
		fin >> temp.id;
		fin >> temp.level;
		fin >> temp.experience;
		fin >> temp.floor;
		if (temp.id == 0)//表明读入的是一个玩家信息
		{
			basic.push_back(temp);
		}
	}//将所有玩家的信息全部读入到数据中
	fin.close();

	while (choose != 4)
		switch (choose)
		{
		case 1: {
			send_(_sock, "\t\t\t\t\t\t\tThis is the rank of all the buildr\n");
			sort(basic.begin(), basic.end(), Rank_Player_Level);
			for (int i = 1;i <= basic.size();i++)
			{
				send_int(_sock, i);
				send_(_sock, ".\t");
				send_string(_sock, basic[i - 1].name);
				send_(_sock, "\t");
				send_int(_sock,basic[i-1].level);
				send_(_sock, "\n");
				//system("pause");
			}
			//system("pause");
			send_(_sock, "\nWhich rank you want to search?\n1.level\n2.experience\n3.floor\n4.quit\n" );
			send_(_sock, "#");
			 temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
			 choose = atoi(choose_temp);
			break;
		}
		case 2: {
			send_(_sock, "\t\t\t\t\t\t\tThis is the rank of all the buildr\n" );
			sort(basic.begin(), basic.end(), Rank_Player_experience);
			for (int i = 1;i <= basic.size();i++)
			{
				send_int(_sock, i);
				send_(_sock, ".\t");
				send_string(_sock, basic[i - 1].name);
				send_(_sock, "\t");
				send_int(_sock, basic[i-1].experience);
				send_(_sock, "\n");
				cout << i << ".\t" << basic[i - 1].name << "\t" << basic[i - 1].experience << endl;
			}
			//system("pause");
			send_(_sock, "\nWhich rank you want to search?\n1.level\n2.experience\n3.floor\n4.quit" );
			send_(_sock, "#");
			temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
			choose = atoi(choose_temp);
			break;
		}
		case 3: {
			send_(_sock, "\t\t\t\t\t\t\tThis is the rank of all the buildr\n");
			sort(basic.begin(), basic.end(), Rank_Player_floor);
			for (int i = 1;i <= basic.size();i++)
			{
				send_int(_sock, i);
				send_(_sock, ".\t");
				send_string(_sock, basic[i - 1].name);
				send_(_sock, "\t");
				send_int(_sock, basic[i-1].floor);
				send_(_sock, "\n");
				cout << i << ".\t" << basic[i - 1].name << "\t" << basic[i - 1].floor << endl;
			}
			//system("pause");
			send_(_sock, "\nWhich rank you want to search?\n1.level\n2.experience\n3.floor\n4.quit" );
			send_(_sock, "#");
			temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
			choose = atoi(choose_temp);
			break;
		}
		default:break;
		}
}

void Rank_Builder(SOCKET _sock)//对构词者的两种成绩进行排序
{
	send_(_sock, "Which rank you want to search?\n1.level\n2.the number of the words\n3.quit\n" );
	send_(_sock, "#");
	char choose_temp[MaxSize];
	int temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
	int choose = atoi(choose_temp);
	vector<Basic_information> basic;//存储数据库读入的所有人员信息
	struct Basic_information temp;

	ifstream fin(information);
	while (fin >> temp.name)
	{
		fin >> temp.password;
		fin >> temp.id;
		fin >> temp.level;
		fin >> temp.experience;
		fin >> temp.floor;
		if (temp.id == 1)//表明读入的是一个构词者的信息
		{
			basic.push_back(temp);
		}
	}//将所有构词者的信息全部读入到数据中
	fin.close();

	while (choose != 3)
		switch (choose)
		{
		case 1: {
			send_(_sock, "\t\t\t\t\t\t\tThis is the rank of all the buildr\n" );
			sort(basic.begin(), basic.end(), Rank_Player_Level);
			for (int i = 1;i <= basic.size();i++)
			{
				send_int(_sock, i);
				send_(_sock, ".\t");
				send_string(_sock, basic[i - 1].name);
				send_(_sock, "\t");
				send_int(_sock, basic[i-1].level);
				send_(_sock, "\n");
				cout << i << ".\t" << basic[i - 1].name << "\t" << basic[i - 1].level << endl;
			}
			//system("pause");
			send_(_sock, "\nWhich rank you want to search?\n1.level\n2.the number of the words\n3.quit\n" );
			send_(_sock, "#");
			temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
			choose = atoi(choose_temp);
			break;
		}
		case 2: {
			send_(_sock, "\t\t\t\t\t\t\tThis is the rank of all the buildr\n" );
			sort(basic.begin(), basic.end(), Rank_Player_experience);
			for (int i = 1;i <= basic.size();i++)
			{
				send_int(_sock, i);
				send_(_sock, ".\t");
				send_string(_sock, basic[i - 1].name);
				send_(_sock, "\t");
				send_int(_sock, basic[i-1].experience);
				send_(_sock, "\n");
				cout << i << ".\t" << basic[i - 1].name << "\t" << basic[i - 1].experience << endl;
			}
			//system("pause");
			send_(_sock, "\nWhich rank you want to search?\n1.level\n2.the number of the words\n3.quit\n" );
			send_(_sock, "#");
			temp_recv_len = recv(_sock, choose_temp, MaxSize, 0);
			choose = atoi(choose_temp);
			break;
		}
		default:break;
		}
}
