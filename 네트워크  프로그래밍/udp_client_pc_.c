#pragma comment(lib,"ws2_32")
#define	_WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>

#define BUF_SIZE	512
#define SERVER_PORT		6000
#define	SEVER_IP	"70.12.114.178"

#define MY_PORT		30000 //포트 넘버가 달라쓰.

//	소켓함수 에러출력 후 종료
void Error_Exit(char* str)
{
	printf("%s Error!! Exit...\n", str);
	_getch();
	exit(1);
}

int main(void)
{
	WSADATA wsaData;
	SOCKET sock;
	char message[BUF_SIZE], txbuf[BUF_SIZE], rxchar;
	int strLen, index = 0;
	unsigned long nonBlk = 1;

	SOCKADDR_IN servAdr;
	SOCKADDR_IN clntAdr;
	int servAdrSz;

	//	전송할 상대편 IP 설정
	memset(&clntAdr, 0, sizeof(clntAdr));
	clntAdr.sin_family = AF_INET;
	clntAdr.sin_addr.s_addr = inet_addr(SEVER_IP);
	clntAdr.sin_port = htons(SERVER_PORT);

	//	윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		Error_Exit("WSAStartup()");
	}

	//	데이터그램 소켓 생성: socket()
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		Error_Exit("socket()");
	}

	//	bind()
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(MY_PORT);
	if (bind(sock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		Error_Exit("bind()");
	}

	//	Nonblock 처리
	if (ioctlsocket(sock, FIONBIO, &nonBlk)) Error_Exit("NonBlock");
	printf("[Send]: ");
	servAdrSz = sizeof(servAdr);
	for (;;)
	{
		if ((strLen = recvfrom(sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&servAdr, &servAdrSz)) > 0)
		{
			message[strLen] = '\0';
			printf("\r[recv]: %s\n", message);
			printf("[send]: ");
		}
		if (_kbhit())
		{
			rxchar = (char)_getch();
			if (rxchar == '\r')
			{
				txbuf[index++] = '\0';
				if (!strcmp("exit", txbuf)) break;
				sendto(sock, txbuf, index, 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr));
				index = 0;
				printf("\n[send]: ");
			}
			else
			{
				printf("%c", rxchar);
				txbuf[index++] = rxchar;
			}
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}
