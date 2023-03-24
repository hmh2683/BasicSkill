#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void * count_clnt(void * arg);
void error_handling(char * msg);

/* �Ӱ� ����(���� ������ ����X)  */
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t handle_thread, count_thread;
    
	if(argc!=2) 
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	/* �������� ���� ���� ���� */ 
	pthread_mutex_init(&mutx, NULL); 
	
	/* ���� ���� ���� */
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); 
	
	/* �ּ� ���� �ʱ�ȭ */
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; // �ּ�ü��(IPv4, IPv6)
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY); // 32bit IP �ּ����� ���� (��Ʈ��ũ ����Ʈ ����) 
	serv_adr.sin_port=htons(atoi(argv[1]));  // 16bit PORT ��ȣ ���� (��Ʈ��ũ ����Ʈ ����) 
	
	/* ���� �ּ� �Ҵ�*/
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1) 
		error_handling("bind() error");
	
	/* ���� �����û ��� */
	if(listen(serv_sock, 5)==-1) 
		error_handling("listen() error");
	
	while(1)
	{
		/* ���� �����û ���� */
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); 

		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++]=clnt_sock; 
		pthread_mutex_unlock(&mutx);

		/* ������ ���� */ 
		pthread_create(&handle_thread, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_create(&count_thread, NULL, count_clnt, (void*)&clnt_sock);
		
		/* ���ŷ ����X -> ������ ���� -> ������ �Ҹ� */
		pthread_detach(handle_thread);
		pthread_detach(count_thread);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

/* Ŭ���̾�Ʈ �ۼ��� �� ����  */
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char msg[BUF_SIZE];

	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0) // ����
		send_msg(msg, str_len); 
	
	//shutdown(clnt_sock, SHUT_RD); // �Է� ��Ʈ�� ���� -> ����X
	
	/* ���� */
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++) 
	{ 
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);

	close(clnt_sock);
	return NULL;
}

/* ��� Ŭ���̾�Ʈ���� �޼��� �۽� */
void send_msg(char * msg, int len)
{ 
	int i;
	/* �������� �޼��� ��� */
	pthread_mutex_lock(&mutx);
	printf("%s", msg); 
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len); // �۽�
	pthread_mutex_unlock(&mutx);
}

/* ����� Ŭ���̾�Ʈ ���� 2�� ���� ��� */
void * count_clnt(void * arg)
{ 
	while(1){
		printf("Client count : %d \n", clnt_cnt);
		sleep(2);
	}
}

/* ���� �޼��� ��� �� ���� */
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}