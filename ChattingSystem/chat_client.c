#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <pthread.h>
#include <winsock2.h>
	
#define BUF_SIZE 100
#define NAME_SIZE 20
	
void * connect_sock(void * arg);	
void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);

SOCKADDR_IN serv_addr;
char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET sock;
	pthread_t snd_thread, rcv_thread, con_thread;
	void * thread_return;

	if(argc!=4) 
	{
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		error_handling("WSAStartup() error!"); 

	sprintf(name, "[%s]", argv[3]);
	/* 서버 소켓 생성 */
	sock=socket(PF_INET, SOCK_STREAM, 0);
	
	/* 주소 정보 초기화 */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]); // IP주소 입력
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	/* 쓰레드 생성 */
	pthread_create(&con_thread, NULL, connect_sock, (void*)&sock);
	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock); 
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
	
	/* 블로킹 상태O -> 쓰레드 종료 -> 쓰레드 소멸(반환) */
	pthread_join(con_thread, &thread_return);
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);

	closesocket(sock);
	WSACleanup();
	return 0;
}

/* 서버 소켓과 클라이언트 소켓 연결*/
void * connect_sock(void * arg)
{ 
	SOCKET sock=*((SOCKET*)arg);
	while(1)
	{
		/* 2초 마다 재연결 시도*/
		if(connect(sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr))==-1)
			error_handling("connect() error");
		sleep(2000);
	}
}

/* 서버에게 메세지 송신 */
void * send_msg(void * arg)
{
	SOCKET sock=*((SOCKET*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1)
	{
		fgets(msg, BUF_SIZE, stdin);
		if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n"))
		{
			closesocket(sock);
			exit(0);
		}
		sprintf(name_msg,"%s %s", name, msg);
		send(sock, name_msg, strlen(name_msg), 0); // 송신
	}
	//shutdown(clnt_sock, SHUT_SEND); // 출력 스트림 종료 -> 송신X
	return NULL;
}

/* 서버에서 메세지 수신*/
void * recv_msg(void * arg)
{
	SOCKET sock=*((SOCKET*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;

	while(1)
	{
		str_len=recv(sock, name_msg, NAME_SIZE+BUF_SIZE-1, 0); // 수신
		if(str_len==-1) 
			return (void*)-1;

		name_msg[str_len]=0;
		fputs(name_msg, stdout);
	}
	return NULL;
}

/* 에러 메세지 출력 후 종료 */
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}