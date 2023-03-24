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
	/* ���� ���� ���� */
	sock=socket(PF_INET, SOCK_STREAM, 0);
	
	/* �ּ� ���� �ʱ�ȭ */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]); // IP�ּ� �Է�
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	/* ������ ���� */
	pthread_create(&con_thread, NULL, connect_sock, (void*)&sock);
	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock); 
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
	
	/* ���ŷ ����O -> ������ ���� -> ������ �Ҹ�(��ȯ) */
	pthread_join(con_thread, &thread_return);
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);

	closesocket(sock);
	WSACleanup();
	return 0;
}

/* ���� ���ϰ� Ŭ���̾�Ʈ ���� ����*/
void * connect_sock(void * arg)
{ 
	SOCKET sock=*((SOCKET*)arg);
	while(1)
	{
		/* 2�� ���� �翬�� �õ�*/
		if(connect(sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr))==-1)
			error_handling("connect() error");
		sleep(2000);
	}
}

/* �������� �޼��� �۽� */
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
		send(sock, name_msg, strlen(name_msg), 0); // �۽�
	}
	//shutdown(clnt_sock, SHUT_SEND); // ��� ��Ʈ�� ���� -> �۽�X
	return NULL;
}

/* �������� �޼��� ����*/
void * recv_msg(void * arg)
{
	SOCKET sock=*((SOCKET*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;

	while(1)
	{
		str_len=recv(sock, name_msg, NAME_SIZE+BUF_SIZE-1, 0); // ����
		if(str_len==-1) 
			return (void*)-1;

		name_msg[str_len]=0;
		fputs(name_msg, stdout);
	}
	return NULL;
}

/* ���� �޼��� ��� �� ���� */
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}