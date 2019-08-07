#pragma comment(lib,"ws2_32")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>

#define BUF_SIZE	512
#define PORT		6000

SOCKADDR_IN client[10];
int client_count;

int check_exist(SOCKADDR_IN *arr, SOCKADDR_IN t)
{
	int i;
	for (i = 0; i < client_count; i++)
	{
		if (arr[i].sin_family == t.sin_family && \
			arr[i].sin_addr.s_addr == t.sin_addr.s_addr && \
			arr[i].sin_port == t.sin_port)
			return -1;
	}
	return 0;
}

//	소켓함수 에러출력 후 종료
void Error_Exit(char* str)
{
	printf("%s Error!! Exit...\n", str);
	_getch();
	exit(1);
}

int main(void)
{
	WSADATA	wsaData;
	SOCKET hServSock;
	char message[BUF_SIZE], txbuf[BUF_SIZE], rxchar;
	int strLen, index = 0;
	unsigned long nonBlk = 1;
	int i;

	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int clntAddrSize;

	//	윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		Error_Exit("WSAStartup()");
	}

	//	데이터그램 소켓 생성: socket()
	hServSock = socket(PF_INET, SOCK_DGRAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		Error_Exit("socket()");
	}

	//	bind()
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		Error_Exit("bind()");
	}

	printf("[send]: ");
	//	Nonblock 처리
	if (ioctlsocket(hServSock, FIONBIO, &nonBlk)) Error_Exit("NonBlock");

	clntAddrSize = sizeof(clntAddr);
	for (;;)
	{
		//	recvfrom(): nonblock
		if ((strLen = recvfrom(hServSock, message, BUF_SIZE, 0, (SOCKADDR*)&clntAddr, &clntAddrSize)) > 0)
		{
			message[strLen] = '\0';
			printf("\r[recv]: %s\n", message);
			printf("[send]: ");

			//IP,PORT 확인후 clinet 배열에 추가 및 갯수 파악
			if (client_count == 0)
				client[client_count++] = clntAddr;
			else
			{
				if (check_exist(client, clntAddr) == 0)
					client[client_count++] = clntAddr;
			}
			printf("client_count %d\n", client_count);

			for (i = 0; i < client_count; i++)//모든 클라이언트들에게 한 클라이언트가 보낸 메시지를 주자
				sendto(hServSock, message, strLen, 0, (SOCKADDR*)&client[i], sizeof(clntAddr));

			//삭제는?

		}
		if (_kbhit())
		{
			rxchar = (char)_getch();
			if (rxchar == '\r')
			{
				txbuf[index++] = '\0';
				if (!strcmp("exit", txbuf)) break;
				//	sendto
				//sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&clntAddr, sizeof(clntAddr));
				//index = 0;
				//printf("\n[send]: ");

				if(strcmp("1", txbuf)==0)
					sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&client[0], sizeof(clntAddr));
				else if(strcmp("2", txbuf) == 0)
					sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&client[1], sizeof(clntAddr));
				else
				{
					for (int i = 0; i < client_count; i++)
					{
						printf("i = %d port = %d\n", i, client[i].sin_port);
						sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&client[i], sizeof(clntAddr));
					}
				}
				//전체 대상으로 보내는 경우 client 배열에 있는 정보를 이용해서 send
				
				index = 0;
				printf("\n[send]: ");
				//특정 client 간에 보내고 받는 메세지에 대한 처리는?
			}
			else
			{
				printf("%c", rxchar);
				txbuf[index++] = rxchar;
			}
		}
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}



//#pragma comment(lib,"ws2_32")
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//#include <conio.h>
//
//#define BUF_SIZE	512
//#define PORT		6000
//
//
///*
//-클이 보낸 메시지를 받아
//모든 클라이언트에게 전달하게 하기
//
//-대상을 지정하기
//누구에게 메시지를 보낼것인지. 특정 클에게만 메시지를 보낸다.
//
//-삭제
//클이 특정 메시지 보냈을 때 통신 안한다 하면
//내 정보를 삭제해줘. 그래서 후에 보내는 메시지를
//저 클에 보내지 않는 것.
//
//-테스트는 혼자서 안되니까 다른 사람들과 하세요.
//..애초에 클라이언트가 고칠 게 있어요?
//그냥 포트 번호만 다르게 해서 하면 안되나?
//그..IP주소랑.
//프로젝트 여러 개 만들어서 하면..?
//*/
//
//SOCKADDR_IN client[10];
//int idx;
//
////	소켓함수 에러출력 후 종료
//void Error_Exit(char* str)
//{
//	printf("%s Error!! Exit...\n", str);
//	_getch();
//	exit(1);
//}
//
//int isnew(SOCKADDR_IN a)
//{
//	int i;
//
//	for (i = 0; i < idx; i++)
//	{
//		//이게 구조체였다는 걸 몰랐음.
//		//여기 있는 것들을 다 해야되는 거였구나.
//		if (client[i].sin_family == a.sin_family && \
//			client[i].sin_addr.s_addr == a.sin_addr.s_addr &&
//			client[i].sin_port == a.sin_port)
//			return 0;
//		//아니 주소가 똑같을리가 없잖아. 그냥 값을 보려고 하는데 안되면 어쩌라구 ㅎ.ㅎ
//	}
//
//	return 1;
//}
//
//int main(void)
//{
//	WSADATA	wsaData;
//	SOCKET hServSock;
//	char message[BUF_SIZE], txbuf[BUF_SIZE], rxchar;
//	int strLen, index = 0;
//	unsigned long nonBlk = 1;
//
//	SOCKADDR_IN servAddr;
//	SOCKADDR_IN clntAddr;
//	SOCKADDR_IN client[10];
//	SOCKADDR_IN oclient;
//
//
//	//배열을 만든다.
//
//	int clntAddrSize;
//	int i;
//
//	//	윈속 초기화
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//	{
//		Error_Exit("WSAStartup()");
//	}
//
//	//	데이터그램 소켓 생성: socket()
//	//hServSock이라는 소켓을 하나 생성했따.
//	hServSock = socket(PF_INET, SOCK_DGRAM, 0);
//	if (hServSock == INVALID_SOCKET) //잘못된거라면 뭐 에러를 발생시키고요.
//	{
//		Error_Exit("socket()");
//	}
//
//	//	bind()
//	// 에. 서버의 주소를 초기화하는건가요?
//	// ㅋㅋ 밑에 하는 것들 왜 하는건지를 모르겠다.
//	// 뭔가 초기설정을 한 다음에, bind를 하더라.
//
//	//센드는 보낼 애 주소 설정
//	//리시브는 데이터 보낸 놈의 주소가 적힌다고 했었음.
//	//.그렇다면 보낸 애들의 주소가 적히니까 ㅇㅇㅇㅇㅇㅇ..;
//	//보낸 애들의 정보를 누적해서 관리하면 된다.
//	//ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
//	//그러면 정보 보낼 때 그 애들한테 다 보내거나 하면 되는건가.
//	//그래서 서버가 그거를 관리하면 된다고 말합니다.
//	//아니 그래서 어짤ㅇㄹ.ㅇ..
//
//	//ㅋㅋㅋ tcp는 뭐가 많음.
//	//스레드 생성, fork, 입출력 다중화, select 뭐시기. 모르겠다
//	//어휴 진짜 짜증나네 ㅋㅋㅋㅋㅋ.
//	//그러나 스레드 생성은 좀 골치아프고.
//	//윈도우즈 기반 다중 사용자 접속 처리하기 위해 지금은
//	//셀렉트 함수를 사용. 입출력 다중화 하는 함수임
//	//그거를 이용해서 할 수 있는게 그나마다. 이런건가.
//	/*
//	클라이언트를 두 개 만들어서 포트 주소를 다르게 해줘서 
//	데이터 받게 해보세용. 이라는건가..아 진짜.
//	저는 너무 졸립니다.
//
//	*/
//
//	memset(&servAddr, 0, sizeof(servAddr));
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	servAddr.sin_port = htons(PORT);
//	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
//	{
//		Error_Exit("bind()");
//	}
//
//	printf("[send]: ");
//	//	Nonblock 처리
//	if (ioctlsocket(hServSock, FIONBIO, &nonBlk)) Error_Exit("NonBlock");
//
//	clntAddrSize = sizeof(clntAddr);
//	for (;;)
//	{
//		//	recvfrom(): nonblock
//		// 여기가 중요한 거 아니에요 그러면..?
//		// 메시지를 보낸 애의 주소를 받아온 부분이 여기일텐데요.
//		// 리턴 값이 수신한 바이트 수이기 때문에, 수신이 됐으면 뭐. 메시지 마지막 처리해주고
//		// 프린트 해준다는 건 알겠다만.
//		// 여기가 클라이언트가 받은 메시지 아닙니깡.
//		// 밑에서 한 거는 서버가 보내는 메시지를 모든 클라이언트에게 보낸 거였고
//		// 하라고 한 거는 한 클라이언트가 보낸 메시지를 모든 클라이언트에게 보내도록
//		// 서버가 동작을 하라는건가..?
//		// 근데 .. 일단은 ㅋㅋㅋㅋ클라이언트 정보들을 알고 있어야 되잖아요.
//		// 늦게 들어오는 애는 못 받을 수도 있다는 말인건가 그러면?
//		if ((strLen = recvfrom(hServSock, message, BUF_SIZE, 0, (SOCKADDR*)&clntAddr, &clntAddrSize)) > 0)
//		{
//			//어떤 클라이언트로부터 받은 메시지가 이거입니다.
//			message[strLen] = '\0';
//			printf("\r[recv]: %s\n", message);
//			printf("[send]: ");
//
//			//아니 뭐야 나는 왜 이렇게 한거지...;
//			//번호를 이용한다구요..?
//			//아 진짜 아무것도 하기 싫다.. 취업준비라는 게 그냥
//			//뭔가 엄청 정신이 없는 게 문제인 것 같아.
//			if (strcmp(message, "onlyme") == 0) {
//			
//				//0이어야 동일한거더라고요. 
//				//근데 다른사람들도 나처럼 치는데요.? 우다다다다다
//				//그 클라이언트 주소가 뭔지도 알아야될텐데. 그래야 그 사람한테만 보내니까.
//				oclient = clntAddr;
//				//나중에 초기화도 시켜줘야될 것 같은데요.
//				//만약에 oclient 값이 존재한다면 그 사람한테만 메시지를 보내는 거고
//				//그게 아니라면 모든 클에게 메시지를 보내게 하면 되는건가?
//			}
//			//아니 근데. 어..;
//			//어느 위치에서 해야되는데..?
//
//			//새로운 것이 맞다면 넣어준다.
//			if(isnew(clntAddr)){
//				client[idx] = clntAddr;//문제 안생기나..? 주소를 저장함.
//				idx++;
//			}
//			
//			//연결된 애들한테 하면 될 것 같아서 여기서 하면 되지 않을까?
//			//나중에 또 누가 연결되면 걔네들한테 주게 되겠지 머..
//			for (i = 0; i < idx; i++)//모든 클라이언트들에게 한 클라이언트가 보낸 메시지를 주자
//				sendto(hServSock, message, strLen, 0, (SOCKADDR*)&client[i], sizeof(clntAddr));
//
//			//ip와 port를 확인하고 client 배열에 추가하고 갯수를 파악한다
//			//기존에 있는가, 수. 그런거 확인하고.
//			//삭제도 해야돼요..?
//
//		}
//		// 무슨 말임..? ㅋㅋㅋㅋ
//		// 아무튼 여기는 한 글자씩 읽어오는 거라고 했던 것 같습니다.
//		// 여기는 서버가 클라이언트한테 보내는 거 아니에요..?
//		if (_kbhit())
//		{
//			rxchar = (char)_getch();
//			if (rxchar == '\r') //엔터를 쳤다면 마지막에 널로 채워준 다음에 보내는듯.
//			{
//				txbuf[index++] = '\0';
//				if (!strcmp("exit", txbuf)) break;
//				
//				//널 값이 아니라면 
//				//printf("dksldpdy\n");
//				//아무튼 여기서 오류가 나고 있는데.
//				if (oclient.sin_family != NULL)//어쨌든 한 값만 봐도 될 것 같기 때문임.
//				{
//					printf("ㅁㄴㅇㄹ");
//					sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&oclient, sizeof(clntAddr));
//					printf("문제가 생기는 부분은?\n");
//					oclient.sin_family = NULL;
//					printf("두 번째\n");
//					//보내준 다음에 널로 만들어서 비게 만들었다.
//					//아 모르겠다..;
//					//초기값같은 거 없어요?
//				}
//				
//				//	sendto
//				// 클라이언트의 주소인 다섯번째 변수가 두 개가 되면 되는 거 아닌가 ㅎ.ㅎ
//				// 이 부분을 아래 부분으로 바꿔주면 되는걸까요?
//				//sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&clntAddr, sizeof(clntAddr));
//				//index = 0;
//				//printf("\n[send]: ");
//
//				else {//특정하게 보낼 클라이언트가 있는게 아니라면
//					for (i = 0; i < idx; i++) {
//						//어차피 위에서 전송할 거는 똑같으니까 뭐 상관은 없을 것 같아요.
//						printf("i = %d port = %d\n", i, client[i].sin_port);
//						sendto(hServSock, txbuf, index, 0, (SOCKADDR*)&client[i], sizeof(clntAddr));
//					}
//				}
//				//그럼 이렇게 해줘야되는건가..?
//				
//				//이것도 잘못된 위치에 넣어줬었다..;
//				index = 0;
//				printf("\n[send]: ");
//				
//				//클라이언트 주소 모두에 보내주면 될 것..
//				//낑. 근데 특정한 클라이언트한테만 보내려면, 받은 메시지를 처리해서
//				//뭐.. 그런거.
//
//				//클라이언트가 보낸 메시지 중에 only me 라고 하면
//				//그 사람한테만 보내면 되는거야..?
//				//그러면 특정한 클라이언트를 따로 넣어놔야겠네요.
//				//근데 한 번 그러고 난 후에 해제도 해야되는 거 아닌가요..;
//				//그건 또 어떻게 하는데?
//				//아 개 우울하다진짜 짜증나기도 하고... ㅇㅇ..어ㅓ..
//
//			}
//			else
//			{
//				printf("%c", rxchar);
//				txbuf[index++] = rxchar;
//			}
//		}
//	}
//	closesocket(hServSock);
//	WSACleanup();
//	return 0;
//}
