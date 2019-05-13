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
#include"BUILDER.h"
//#include "Rank_The_User.hpp"
#define information "user_information.txt"
#define WORD "WORDS.txt"
using namespace std;



void BUILDER::Create_Builder()
{
	send_(_sock,"Welcome to join us! Please input the name you want to use(less than 20 letters),or input # to choose quit:\n" );
	send_(_sock, "#");
	char name[MaxSize];
	int temp_recv_len=recv(_sock, name, MaxSize, 0);
	name[temp_recv_len] = '\0';
	vector<Basic_information> basic;//��ȡ���е���Ա��Ϣ

	basic = Read_in(basic);

	if (strcmp(name,"#")==0)
		return;//����#�˳�
	else
	{
		int Check = User_Check(name, 1);//�����Ƿ�������������
		while (Check == 1)//����ֵΪ1��ʱ���ʾ����
		{
			send_(_sock, "Sorry, this name has been in register, Please choose another one OR input # to quit:\n");
			send_(_sock, "#");

			memset(name, 0,sizeof(name));
			temp_recv_len = recv(_sock, name, MaxSize, 0);
			name[temp_recv_len] = '\0';
			cout << "�����ã�����������û�����" << name << endl;
			if (strcmp(name, "#") == 0)
				return;
			else
				Check = User_Check(name, 1);
		}

		//���˴������û�������ɹ�
		send_(_sock, "Please input the Password\nPlease be careful, because this step are not allowed to quit:\n");
		send_(_sock, "#");
		char password[MaxSize];
		int temp_recv_len = recv(_sock, password, MaxSize, 0);
		password[temp_recv_len] = '\0';

		struct Basic_information temp;
		temp.name = name;
		temp.password = password;
		temp.id = 1;
		temp.floor = 1;
		temp.experience = 0;
		temp.level = 1;
		basic.push_back(temp);

		Write_In(basic);//ע��ɹ���д����Ϣ
		send_(_sock, "Congratulation! Let's start your game!\n" );

	}
}

void BUILDER::Log_In()
{
	send_(_sock, "Please input the username:\n" );
	send_(_sock, "#");
	char name[MaxSize];
	int temp_recv_len = recv(_sock, name, MaxSize, 0);
	name[temp_recv_len] = '\0';
	char pass[MaxSize];
	while (1)
	{
		if (strcmp(name, "#") == 0)
		{
			send_(_sock, "You have quit the game!\n" );
			return;
		}
		while (strcmp(name, "#") != 0)
		{
			if (User_Check(name, 1))//��������û���
			{
				send_(_sock, "Please input the password:\n" );
				send_(_sock, "#");
				while (1)
				{
					temp_recv_len = recv(_sock, pass, MaxSize, 0);
					pass[temp_recv_len] = '\0';

					int judge = Password_Check(name, pass, id);
					if (judge == 0)
					{
						vector<Basic_information> basic;
						ifstream fin(information);
						basic = Read_in(basic);
						int people;

						for (int i = 0;i < basic.size();i++)
						{
							if ((basic[i].name == name) && (basic[i].id == 1))
							{
								people = i;
								break;
							}
						}

						int t_number = Add_new_word();
						basic[people].experience += t_number;
						while (basic[people].experience >= basic[people].level * 5)
						{
							basic[people].level++;
						}
						Write_In(basic);
						return;
					}
					else if (judge == 1)//�������
					{
						send_(_sock, "You have input a wrong password,Please try again\n" );
						return;

					}
					else if (judge == 2)
					{
						send_(_sock, "this account are not allowed to play game,Please quit and try again\n");
						return;//�������˳�������2
					}

				}
			}
			else
			{
				send_(_sock, "this name are not exsit,Please quit and Try again\n" );
				return;//�������˳�������2
			}
		}
	}
}

int BUILDER::Add_new_word()
{
	ifstream fin(WORD);
	vector<string> temp;
	string word;//���ڶ�ȡ�����ķ��ϳ���Ҫ��ĵ���
	int number;//���ʵ�����
	int t_number = 0;//���ڼ�¼��������Ҵ����˶��ٸ�����
	fin >> number;
	int i = 1;

	while (fin >> word)
	{
		if (word.size() == i)
		{
			temp.push_back(word);
		}
		else
		{
			lib.push_back(temp);
			i++;
			temp.clear();//������е�Ԫ�أ�������һ�ֳ��ȵĵ��ʴ��
			temp.push_back(word);//�Ѹո��Ǹ������ĵ��ʴ�Ž�ȥ
		}
	}
	fin.close();//�Ӵʿ��ж�ȡ���еĵ������

	while (1)
	{
		send_(_sock, "Please input the word:\n");
		send_(_sock, "#");
		char temp_in[MaxSize];
		int temp_recv_len = recv(_sock, temp_in, MaxSize, 0);
		temp_in[temp_recv_len] = '\0';
		//�û����뵥��

		if (strcmp(temp_in, "#") == 0)
			break;//����#�˳��༭
		int flag = Word_Check(temp_in);
		if (flag)
		{
			send_(_sock, "Succeed!\n");
			lib[strlen(temp_in) - 1].push_back(temp_in);
			number++;
			t_number++;//���ڼ�¼������һ�������˶��ٸ�����
		}
		else
		{
			send_(_sock, "This word has been used,Please Try another one or input # to quit\n");
		}
	}

	Write_In_Word(number);//���޸ĺ�ĵ���д��ʿ�
	return t_number;
}


int BUILDER::Word_Check(string word)//����Ƿ�����ͬ���ʣ�����еĻ�������0��û�еĻ�����1
{
	int length = word.size();//�û�����ĵ���s����
	for (int i = 0;i < lib[length - 1].size();i++)
	{
		if (word == lib[length - 1][i])//�ڳ�����ȵĵ��ʿ��г�����ͬ����
		{
			return 0;
		}
	}
	return 1;

}

void BUILDER::Write_In_Word(int number)
{
	ofstream fo;
	fo.open(WORD);
	fo << number;//�Ƚ����ʵ���������

	for (int i = 0;i < lib.size();i++)
	{
		fo << "\n";
		for (int j = 0;j < lib[i].size();j++)
		{
			fo << lib[i][j] << "\t";
		}
	}
	fo.close();//��ʱ���еĵ���д�뵽���ʿ���


}
