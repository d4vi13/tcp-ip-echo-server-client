#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>


#define BUFFER_SIZE 1024
#define PORT 10000
#define FILE teste

int main(){
	int sock,sock1,fd;
	char buffer[BUFFER_SIZE] = {0};
	socklen_t endereco_tam;
	struct stat file_stat;

	/*
	#include <netinet/in.h>

	struct sockaddr Descreve um endereço de socket

	ESTRUTURA PARA LIDAR COM ENDEREÇO DE INTERNET

	Describes an IPv4 Internet domain socket address.  The
	sin_port and sin_addr members are stored in network byte
	order.

	struct sockaddr_in {
	    short            sin_family;   // e.g. AF_INET
	    unsigned short   sin_port;     // e.g. htons(3490)
	    struct in_addr   sin_addr;     // see struct in_addr, below
	    char             sin_zero[8];  // zero this if you want to
	};

	struct in_addr {
	    unsigned long s_addr;  // load with inet_aton()
	};
	*/

	struct sockaddr_in endereco;
	endereco_tam = sizeof(endereco);


	// criar socket

	/*
	socket retorna um natural, chamado de file descriptor do socket. 
	Caso haja um erro retorna -1

	Um file descriptor é um indentificador unico que o SO
	da a um arquivo quando ele é aberto
	*/

	printf("Criando socket\n");
	sock = socket(AF_INET,SOCK_STREAM,0);

	if (sock < 0){
		printf("Não foi possivel criar o socket\n");
		return 0;
	}

	printf("Configurando endereço\n");
	endereco.sin_family = AF_INET;

	// especifica que queremos bind para todas as interfaces
	endereco.sin_addr.s_addr = INADDR_ANY;

	/*
	para fazer um bind a um ip especifico
	inet_aton("10.0.0.1",&enderço.sin_addr);
	tbm pd usar inet_addr(), função antiga
	*/

	endereco.sin_port = htons(PORT);

	//bind do socket a um endereço e porta 
	printf("Binding...\n");
	bind(sock,(struct sockaddr*)&endereco,endereco_tam);

	printf("Esperando por conexão\n");

	//sock começa ser usado para aceitar pedidos de conexão
	//o segundo parametro define o tam max da fila de conexões pendentes
	listen(sock,1);

	/*
	accept() vai pegar a primeira conexão da fila , criar um
	novo socket,com o mesmo protocolo e familia de endereços
	do socket passado e allocara um novo file descriptor pro
	novo socket.
	*/

	sock1 = accept(sock,(struct sockaddr*)&endereco,&endereco_tam);
	printf("Conectado a %s\n",inet_ntoa(endereco.sin_addr));

	// le do arquivo associado ao file descripitor n bytes(ultimo parametro)
	printf("Recebendo...\n");
	read(sock1,buffer,BUFFER_SIZE-1);

	printf("%s\n",buffer);

	printf("Ecoando...\n");
	send(sock1, buffer,BUFFER_SIZE-1,0);

	close(sock1);
	close(sock);
	return 0;
}