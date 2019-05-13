#define WIN32_LEAN_AND_MEAN
#define MaxSize 4096

#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<WinSock2.h>
#include<algorithm>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

void send_char(SOCKET sockClient,const char s[MaxSize])
{
	char sendBuf[MaxSize];
	strcpy_s(sendBuf, s);
	int byte = send(sockClient, sendBuf, strlen(sendBuf), 0);
	Sleep(40);
}

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

void receive(SOCKET _sock)
{
	char recvbuf[MaxSize];
	int temp_recv_len = recv(_sock, recvbuf, MaxSize, 0);//接受游戏信息
	recvbuf[temp_recv_len] = '\0';
	
	while (strcmp(recvbuf, "###") != 0)//退出游戏
	{
		//cout << "测试用：现在是循环读取发来的消息:" << endl;
		while (strcmp(recvbuf, "#") != 0 && strcmp(recvbuf, "###") != 0)
		{
			cout << recvbuf;
			memset(recvbuf, 0, sizeof(recvbuf));
			temp_recv_len = recv(_sock, recvbuf, MaxSize, 0);
			recvbuf[temp_recv_len] = '\0';
		}

		if (strcmp(recvbuf, "###") != 0)
		{
			memset(recvbuf, 0, sizeof(recvbuf));
			strcpy(recvbuf, " ");
			//cout << "请输入：" << endl;
			char send_temp[MaxSize];
			cin >> send_temp;
			send_char(_sock, send_temp);
		}
	}
	cout << "Welcome again!" << endl;
}

int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//1.创立套接字socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);

	//2.连接服务器
	SOCKADDR_IN _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(6666);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (SOCKET_ERROR == connect(_sock, (sockaddr*)&_sin, sizeof(SOCKADDR)))
	{
		cout << "ERROR,CONNETING Failed..." << endl;
	}
	else
	{
		cout << "Succeed!..." << endl;
	}

	//3.接受服务器信息
	char recvBuf[MaxSize]= {};
	
	int nlen = 0;
	nlen=recv(_sock, recvBuf, MaxSize, 0);
	
	if (0 >= nlen)
	{
		cout << "ERROR! Listening failed..." << endl;
	}
	else
	{
		cout << "connecting succeed!" << endl;
	}
	
	cout << recvBuf;

	while (1)
	{
		if (strcmp(recvBuf,"###")==0)
			break;
		else
		{
			if (strcmp(recvBuf,"#")!=0)
			{
				memset(recvBuf, 0, sizeof(recvBuf));
				nlen = recv(_sock, recvBuf, MaxSize, 0);
				cout << recvBuf;
			}
			else
			{
				char inword[MaxSize] = {};
				cin >> inword;
				send_char(_sock,inword);
				memset(recvBuf, 0, sizeof(recvBuf));
			}
		}

	}

	//4.关闭套接字
	closesocket(_sock);
	WSACleanup();
	//system("pause");
	return 0;
}