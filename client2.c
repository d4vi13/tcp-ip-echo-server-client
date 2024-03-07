#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define BUFFER_SIZE 1024
#define PORT 10000
#define FILE "teste"

int main(){
	int sock,status,fd;
	long int dados_restantes;
	off_t offset;
	struct sockaddr_in endereco;
	struct stat file_stat;
	char tamanho_arquivo[256];

	printf("Criando socket...\n");
	sock = socket(AF_INET,SOCK_STREAM,0);

	endereco.sin_family=AF_INET;

	endereco.sin_port = htons(PORT);

	inet_pton(AF_INET,"127.0.0.1",(struct sockadrr*)&endereco.sin_addr);

	printf("Conectando...\n");
	/*
		connect() conecta o socket passado pelo file descriptor
		ao endereço especificado
	*/
	status = connect(sock, (struct sockaddr*)&endereco, sizeof(endereco));

	fd = open(FILE,O_RDONLY);
	 /*
		O_RDONLY - read only
		O_WRONLY - write only
		O_RDWR - read and wite
	 */

	// obtem informações sobre arquivo associado ao file descriptor
	fstat(fd,&file_stat);

 	sprintf(tamanho_arquivo,"%ld",file_stat.st_size);

 	// mandar tamanho de arquivo
	send(sock,tamanho_arquivo,256,0);
	printf("tamanho_arquivo enviado.\n");

	//confirmar recebimento
	read(sock,tamanho_arquivo,255);
	printf("ECHO: ");
	puts(tamanho_arquivo);
	printf("\n");

	dados_restantes = file_stat.st_size;

	offset = 0;
	while (dados_restantes > 0){
		dados_restantes -= sendfile(sock,fd,&offset,4096);
		printf("1024 bytes enviados, restam %ld\n", dados_restantes);
	}


	close(sock);
	return 0;
}