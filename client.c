#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 10000

int main(){
	int sock,status;
	struct sockaddr_in endereco;
	char* message = malloc(BUFFER_SIZE*sizeof(char));
	*message = 0;

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

	fgets(message,BUFFER_SIZE-1,stdin);
	send(sock,message,BUFFER_SIZE,0);
	printf("Mensagem enviada.");

	read(sock,message,BUFFER_SIZE-1);

	printf("ECHO: ");
	puts(message);
	printf("\n");

	close(sock);
	return 0;
}