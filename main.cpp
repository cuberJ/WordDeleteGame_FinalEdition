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
#include"SOCKET.h"
#include<WinSock2.h>
#include"RANK.h"
#include<algorithm>
#include"PLAYER.h"
#include"BUILDER.h"


#define information "user_information.txt"
#define WORDS "word.txt"
using namespace std;
#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

void Begin(SOCKET _cSock)
{
	send_(_cSock, "\t\t\t\t\t\t**************************************************\n");
	send_(_cSock, "\t\t\t\t\t\t\tWelcome to this game!input the choice!\n");
	send_(_cSock, "\t\t\t\t\t\t1.Create a new account for game.\n");
	send_(_cSock, "\t\t\t\t\t\t2.Using an existed account to start.\n");
	send_(_cSock, "\t\t\t\t\t\t3.cancel one existed account.\n");
	send_(_cSock, "\t\t\t\t\t\t4.Create a new account for buliding Word Lib.\n");
	send_(_cSock, "\t\t\t\t\t\t5.Using an existed account for Buliding Word Lib.\n");
	send_(_cSock, "\t\t\t\t\t\t6.Show the rank list of the gamer\n");
	send_(_cSock, "\t\t\t\t\t\t7.Show the rank list of the builder\n");
	send_(_cSock, "\t\t\t\t\t\t8.Quit the game.\n");
	send_(_cSock, "\t\t\t\t\t\t**************************************************\n");
	send_(_cSock, "#");
}

void game_choose(SOCKET _cSock, class PLAYER player, class BUILDER builder)
{
	while (1)
	{
		Begin(_cSock);
		char choose_temp[MaxSize];
		int temp_recv_len = 0;
		temp_recv_len = recv(_cSock, choose_temp, MaxSize, 0);
		choose_temp[temp_recv_len] = '\0';

		int choose = atoi(choose_temp);
		if (choose == 8)
		{
			send_(_cSock, "###");
			return;
		}
		switch (choose)
		{
		case 1: {//注册账号
			player.Create_new_player();
			break;
		}
		case 2: {
			player.Log_In();
			break;
		}
		case 3: {
			player.Cancel_exist_user(0);
			break;
		}
		case 4: {
			builder.Create_Builder();
			break;
		}
		case 5: {
			builder.Log_In();
			break;
		}
		case 6: {
			Rank_Player(_cSock);
			break;
		}
		case 7: {
			Rank_Builder(_cSock);
			break;
		}
		default: {
			send_(_cSock, "Please Input a Right Choice!\n");
			send_(_cSock, "#");
			break;
		}
		}
	}


}

/*vector<SOCKET> g_client;
void select_client(SOCKET _sock)
{
	fd_set fdread;
	fd_set fdwrite;
	fd_set fdexp;

	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdexp);

	FD_SET(_sock, &fdread);
	FD_SET(_sock, &fdwrite);
	FD_SET(_sock, &fdexp);

	int flag = select(_sock + 1, &fdread, &fdwrite, &fdexp, NULL);
	if (flag < 0)
	{
		send_(_sock, "failed...\n");
	}
	if (FD_ISSET(_sock, &fdread))
	{
		FD_CLR(_sock, &fdread);
	}
}*/

int main()
{
	SOCKADDR_IN _sin;
	SOCKET_CREATE();

	//1.创立套接字socket

	_sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(6666);

	int _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == _sock)
	{
		cout << "socket Create ERROR" << endl;
	}
	//2.bind绑定客户端

	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		cout << "ERROR,CONNETING Failed..." << endl;
	}
	else
	{
		cout << "Succeed!..." << endl;
	}

	//listen监听
	if (SOCKET_ERROR == listen(_sock, 5))//五个监听端口
	{
		cout << "ERROR! Listening failed..." << endl;
	}
	else
	{
		cout << "Succeed!..." << endl;
	}
	//4.等待客户端连接成功accept
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);


	if (_cSock == INVALID_SOCKET)
	{
		cout << "invalid client..." << endl;
	}
	else
	{
		cout << "Succeed!" << endl;
	}

	class PLAYER player;//建立客户类对象和服务器对象
	player._sock = _cSock;
	class BUILDER builder;
	builder._sock = _cSock;
	//5.向客户端发送消息

	game_choose(_cSock, player, builder);

	cout << "脱离连接" << endl;

	//6.关闭套接字
	closesocket(_sock);
	WSACleanup();
	//system("pause");
	return 0;
}