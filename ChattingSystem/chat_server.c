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

/* 임계 영역(전역 변수값 변경X)  */
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
	/* 전역변수 동시 접근 방지 */ 
	pthread_mutex_init(&mutx, NULL); 
	
	/* 서버 소켓 생성 */
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); 
	
	/* 주소 정보 초기화 */
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; // 주소체계(IPv4, IPv6)
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY); // 32bit IP 주소정보 저장 (네트워크 바이트 순서) 
	serv_adr.sin_port=htons(atoi(argv[1]));  // 16bit PORT 번호 저장 (네트워크 바이트 순서) 
	
	/* 소켓 주소 할당*/
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1) 
		error_handling("bind() error");
	
	/* 소켓 연결요청 대기 */
	if(listen(serv_sock, 5)==-1) 
		error_handling("listen() error");
	
	while(1)
	{
		/* 소켓 연결요청 수락 */
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); 

		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++]=clnt_sock; 
		pthread_mutex_unlock(&mutx);

		/* 쓰레드 생성 */ 
		pthread_create(&handle_thread, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_create(&count_thread, NULL, count_clnt, (void*)&clnt_sock);
		
		/* 블로킹 상태X -> 쓰레드 종료 -> 쓰레드 소멸 */
		pthread_detach(handle_thread);
		pthread_detach(count_thread);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

/* 클라이언트 송수신 및 해제  */
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char msg[BUF_SIZE];

	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0) // 수신
		send_msg(msg, str_len); 
	
	//shutdown(clnt_sock, SHUT_RD); // 입력 스트림 종료 -> 수신X
	
	/* 해제 */
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

/* 모든 클라이언트에게 메세지 송신 */
void send_msg(char * msg, int len)
{ 
	int i;
	/* 서버에서 메세지 출력 */
	pthread_mutex_lock(&mutx);
	printf("%s", msg); 
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len); // 송신
	pthread_mutex_unlock(&mutx);
}

/* 연결된 클라이언트 수를 2초 마다 출력 */
void * count_clnt(void * arg)
{ 
	while(1){
		printf("Client count : %d \n", clnt_cnt);
		sleep(2);
	}
}

/* 에러 메세지 출력 후 종료 */
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}