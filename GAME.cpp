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

void send_(SOCKET sockClient, const char s[MaxSize])
{
	char sendBuf[MaxSize];
	strcpy_s(sendBuf, s);
	int byte = send(sockClient, sendBuf, strlen(sendBuf), 0);
	Sleep(100);//����ʱ����̻ᵼ�������������͵����ݱ��ϲ���ȡ
}

void USER::Create_new_player()
{
	send_(_sock, "Welcome to this amazing game! Please input the name you want to use(less than 20 letters),or input # to choose quit:\n");
	Sleep(200);
	send_(_sock, "#");
	char name[MaxSize];//��¼�û���������Ϣ
	
	int temp_recv_len = recv(_sock, name, MaxSize, 0);
	name[temp_recv_len] = '\0';
	cout << "�����ã������������ǣ�" << name << endl;

	vector<Basic_information> basic;//��ȡ���е���Ա��Ϣ

	basic = Read_in(basic);

	if (strcmp(name, "#") == 0)
	{
		send_(_sock, "You choosed to quit the ganme!\n");
		return;//����#�˳�
	}
	else
	{
		int Check = User_Check(name, 0);//�����Ƿ�������������
		while (Check == 1)//����ֵΪ1��ʱ���ʾ����
		{
			cout << "�����ã��û�������ʧ��" << endl;
			send_(_sock, "Sorry, this name has been in register, Please choose another one OR input # to quit:\n");
			send_(_sock, "#");
			memset(name, 0, sizeof(name));
			recv(_sock, name, MaxSize, 0);
			name[temp_recv_len] = '\0';
			cout << "�����ã������������ǣ�" << name << endl;
			if (strcmp(name, "#") == 0)
			{
				send_(_sock, "You choosed to quit the ganme!\n");
				return;//����#�˳�
			}
			else
				Check = User_Check(name, 0);
		}
		cout << "�û���������ɹ���" << endl;
		//���˴������û�������ɹ�
		send_(_sock, "Please input the Password\nPlease be careful, because this step are not allowed to quit:\n");
		send_(_sock, "#");
		char password[MaxSize];
		temp_recv_len=recv(_sock, password, MaxSize, 0);
		password[temp_recv_len] = '\0';
		cout << "�����ã������������ǣ�" << password << endl;

		struct Basic_information temp;
		temp.name = name;
		temp.password = password;
		temp.id = 0;
		temp.floor = 1;
		temp.experience = 0;
		temp.level = 1;
		basic.push_back(temp);

		Write_In(basic);//ע��ɹ���д����Ϣ
		send_(_sock, "Congratulation! Let's start your game!\n");
		//send_(_sock, "#");
	}
}

void USER::Write_In(vector<Basic_information> basic)//���޸Ĺ�����Ϣд���û���Ϣ�ĵ�
{
	ofstream fo;
	fo.open(information);

	for (int i = 0;i < basic.size();i++)
	{
		fo << "\n" << basic[i].name << "\t" << basic[i].password << "\t" << basic[i].id << "\t" << basic[i].level << "\t" << basic[i].experience << "\t" << basic[i].floor << "\t";//�����û���-����-���-�ȼ�-����-�ؿ���˳��д��
	}
	fo.close();
}

vector<Basic_information> USER::Read_in(vector<Basic_information> basic)//���û���Ϣ�ĵ�������Ϣ
{
	ifstream fin(information);
	struct Basic_information temp;

	while (fin >> temp.name)
	{
		fin >> temp.password;
		fin >> temp.id;
		fin >> temp.level;
		fin >> temp.experience;
		fin >> temp.floor;
		basic.push_back(temp);
	}
	fin.close();
	return basic;
}

int USER::User_Check(string name, int id)//���ڼ���Ƿ�����,����У�����1�����򷵻�0
{
	ifstream fin(information);
	struct Basic_information temp;

	while (fin >> temp.name)
	{
		fin >> temp.password;
		fin >> temp.id;
		if (temp.name == name && temp.id == id)
		{
			fin.close();
			return 1;
		}
		else
		{
			fin >> temp.level;
			fin >> temp.experience;
			fin >> temp.floor;
		}
	}

	return 0;
}

int USER::Password_Check(string name, string password, int id)//������룬��ȷ����0�����󷵻�1����ȷ�����û���ݴ��󷵻�2,�û������ڷ���3
{
	ifstream fin(information);
	struct Basic_information temp;
	while (fin >> temp.name)
	{
		fin >> temp.password;
		fin >> temp.id;
		fin >> temp.level;
		fin >> temp.experience;
		fin >> temp.floor;
		if (temp.name == name)
		{
			if (temp.id != id)
				return 2;
			else if (temp.password == password && temp.id == id)
				return 0;
			else if (temp.password != password)
				return 1;
		}
	}
	return 3;//������������ָ�������ﵽ
}

void USER::Cancel_exist_user(int id)
{
	send_(_sock, "Please input the name you want to cancel:\n");
	send_(_sock, "#");
	char name[MaxSize];
	int temp_recv_len=0;//��ȡҪɾ��������
	temp_recv_len = recv(_sock, name, MaxSize, 0);
	name[temp_recv_len] = '\0';
	struct Basic_information temp;
	vector<Basic_information> basic;
	int flag = 0;//��¼Ҫɾ�����˺��Ƿ����

	ifstream fin(information);
	while (fin >> temp.name)
	{
		if (temp.name != name)//�����ݿ��в���������Ϣ����
		{
			fin >> temp.password;
			fin >> temp.id;
			fin >> temp.level;
			fin >> temp.experience;
			fin >> temp.floor;
			basic.push_back(temp);
		}
		else if (temp.name == name)
		{
			fin >> temp.password;
			fin >> temp.id;
			if (temp.id != id)//������ͬ�����ǲ��������ݵ��˺Ų���Ҫɾ��
			{
				fin >> temp.level;
				fin >> temp.experience;
				fin >> temp.floor;
			}
			else
				flag = 1;
		}
		else
			flag = 1;
	}
	fin.close();

	Write_In(basic);
	if (flag == 1)
	{
		send_(_sock, "The information has been canceled, and welcome for your next participation!\n");
		//send_(_sock, "#");
	}
	else
	{
		send_(_sock, "The name you want to cancel doesn't exist, Please check and try again.\n" );
		//send_(_sock, "#");
	}
}