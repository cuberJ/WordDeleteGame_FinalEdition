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
	int id;//�������
	int floor = 1;
	int experience = 0;//����ֵ��ÿ�θ��ݹؿ����ѶȽ����ۼ�
	int level = 1;//�ȼ�Ĭ�ϳ�ʼֵΪ1��ÿ����Ϸ��ʱ���������10�⣬���������40��
};

void send_(SOCKET sockClient, const char s[MaxSize]);

class USER {
public:
	string name;
	SOCKET _sock;
	string password;
	int id;//�������
	int floor = 1;//Ĭ�ϴӵ�һ�ؿ�ʼ���ܼ�16��
	int experience = 0;//����ֵ��ÿ�θ��ݹؿ����ѶȽ����ۼ�,�ڹ����ߵ���������Ϊ���������
	int level = 1;//�ȼ�Ĭ�ϳ�ʼֵΪ1��ÿ����Ϸ��ʱ���������10�⣬���������40��

	int User_Check(string name, int id);//����Ƿ�������������
	int Password_Check(string name, string password, int id);//��������Ƿ���ȷ
	void Write_In(vector<Basic_information>);//ע��ɹ����û�����Ϣ����д����Ϣ��
	vector<Basic_information> Read_in(vector<Basic_information> basic);//�����ݿ��ȡ�����˵���Ϣ

	void Create_new_player();//���ѡ��1���������û�

	//void Chooes_Id(int id);//���ݵ�¼�ߵ����ѡ��ģʽ���������/����
	void Cancel_exist_user(int id);//ɾ�����ڵ��û�
};

#endif