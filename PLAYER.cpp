#include "PLAYER.h"
#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include"GAME.h"
#define information "user_information.txt"
#define WORD "WORDS.txt"
using namespace std;

struct Basic_information PLAYER::Game_Start(struct Basic_information basic)
{
	send_(_sock,"Welcome to the Game!\n" );
	send_(_sock, "Remember to input # to quit as you want!\n" );

	int flag;
	int number = 0;//��¼��ǰ�ؿ��Ѿ�����˶�����

	while (1)
	{
		flag = Show_Control(basic.floor);//��¼����Ƿ�����Ŀ
		if (flag == 0)//���
		{
			send_(_sock,"Sorry,You've just input a wrong word,You Failed!\n" );
			break;
		}
		else if (flag == 2)//�������#
		{
			send_(_sock, "You choosed to quit!\n" );
			break;
		}
		else//�����Ŀ
		{
			basic.experience += (basic.floor / 2 + 1);//����ֵ�Ĵ�С=��ǰ�ؿ��ļ���/2+1
			if (basic.experience >= basic.level * 10 && basic.level < 40)//�����ķ�ʽ������ֵ�ﵽ��ǰ�ȼ���ʮ����ֵ
			{
				basic.level++;//����
				send_(_sock,"Congruatulation for your level up!\n" );
			}
			number++;
			if (number == basic.floor&&basic.floor < 16)//��Ե�d��Ŀ�͵�ǰk�ؿ���һ��
			{
				send_(_sock,"\t\t\t\t\tLet's Try Next Floor!\n" );
				basic.floor++;
				number = 0;
			}
		}
	}
	return basic;
}

void PLAYER::Log_In()
{
	send_(_sock, "Please input the username:\n");
	send_(_sock, "#");
	char name[MaxSize];
	int temp_recv_len = 0;
	temp_recv_len = recv(_sock, name, MaxSize, 0);
	name[temp_recv_len] = '\0';
	cout << "�����ã������������ǣ�" << name << endl;

	char pass[MaxSize];

	while (1)
	{
		if (strcmp(name,"#")==0)
		{
			send_(_sock, "You have quit the game!\n" );
			return;
		}
		while (strcmp(name,"#")!=0)
		{
			if (User_Check(name, 0))//��������û���
			{
				send_(_sock,"Please input the password:\n");
				send_(_sock, "#");

				while (1)
				{
					temp_recv_len = recv(_sock, pass, MaxSize, 0);
					pass[temp_recv_len] = '\0';
					cout << "�����ã������������ǣ�" << pass << endl;

					int judge = Password_Check(name, pass, id);
					if (judge == 0)
					{
						vector<Basic_information> basic;
						ifstream fin(information);
						basic = Read_in(basic);
						int people;

						for (int i = 0;i < basic.size();i++)
						{
							if (basic[i].name == name && basic[i].id == 0)
							{
								people = i;
								break;
							}
						}

						basic[people] = Game_Start(basic[people]);
						Write_In(basic);
						return;
					}
					else if (judge == 1)//�������
					{
						send_(_sock,"You have input a wrong password,Please try again\n" );
						//send_(_sock, "#");
						return;

					}
					else if (judge == 2)
					{
						send_(_sock, "this account are not allowed to play game,Please quit and try again\n" );
						//send_(_sock, "#");
						return;//�������˳�������2
					}

				}
			}
			else
			{
				send_(_sock,"this name are not exsit,Please quit and Try again\n" );
				//send_(_sock, "#");
				return;//�������˳�������2
			}
		}
	}
}

string PLAYER::Read_Word(int floor)
{
	ifstream fin(WORD);
	string word;//��ȡÿһ������
	int number;
	vector<string> lib;//������з��ϳ��ȵĵ���

	fin >> number;//��ȡ���ʵ���Ŀ
	while (fin >> word)
	{
		if (word.size() == floor)
		{
			lib.push_back(word);
			//cout <<"���ǵ���:"<< word << endl;
		}
	}
	//cout << "�ʿ�������" << lib.size() << endl;
	srand(time(NULL));
	int i = rand() % lib.size();

	return lib[i];
}

int PLAYER::Show_Control(int floor)//��Է���1�������0���˳�#����2
{
	string word_show_temp = Read_Word(floor);
	char *word_show = (char*)word_show_temp.c_str();
	//strcat(word_show, "\r");
	cout << "�����ǣ�" << word_show << endl;
	send_(_sock, word_show);//��ӡ����
	Sleep(6000);
	send_(_sock ,"\r                                      \r");
	send_(_sock, "#");

	int temp_recv_len=0;
	char word_in[MaxSize];
	temp_recv_len = recv(_sock, word_in, MaxSize, 0);
	word_in[temp_recv_len] = '\0';
	
	if (strcmp(word_in,word_show)==0)
		return 1;
	else if (strcmp(word_in,"#")==0)
		return 2;
	else
		return 0;

}
