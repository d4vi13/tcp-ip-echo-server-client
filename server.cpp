#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 27015


int main() {
	WSADATA wsaData;
	struct sockaddr_in endereco;
	int recebidos,tamanho,restantes;
	char buffer[BUFFER_SIZE];
	SOCKET lsock, csock;
	//lsock - socket para ouvir
	//csock - socket para comunicação 

	// inicia winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		printf("Não foi possivel inicializar o Windows Socket DLL\n");
		return 1;
	}

	//set up server adress
	memset(&endereco, 0, sizeof(endereco));
	inet_pton(AF_INET,"127.0.0.1",&endereco.sin_addr.s_addr);
	endereco.sin_family = AF_INET;// ipv4
	endereco.sin_port = htons(PORT);
	printf("Endereco configurado\n");

	
	//criar socket

	lsock = socket(AF_INET,SOCK_STREAM,0);

	//verificar se occoreu corretamente
	if (lsock == INVALID_SOCKET) {
		printf("Não foi possivel criar o socket para ouvir\n");
		WSACleanup();
		return 1;
	}
	printf("Socket criado com sucesso\n");

	//bind

	if (bind(lsock,(struct sockaddr*)&endereco, sizeof(endereco)) == SOCKET_ERROR) {
		printf("Não foi possivel realizar o bind\n");
		closesocket(lsock);
		WSACleanup();
		return 1;
	}
	printf("Socket associado ao endereco\n");


	//listen

	printf("Procurando chamados...\n");
	if (listen(lsock, SOMAXCONN) == SOCKET_ERROR) {
		printf("Não foi possivel ouvir\n");
		closesocket(lsock);
		WSACleanup();
		return 1;
	}


	//accept

	csock = accept(lsock, NULL, NULL);
	if (csock == INVALID_SOCKET) {
		printf("Não foi possivel aceitar\n");
		closesocket(lsock);
		WSACleanup();
		return 1;
	}
	printf("Conectado a um cliente\n");

	// Recebendo tamanho

	printf("Recebendo tamanho do arquivo... ");
	recv(csock, buffer, BUFFER_SIZE, 0);
	tamanho = atoi(buffer);
	printf("Tamanho do arquivo: %d\n", tamanho);
	restantes = tamanho;


	while (restantes > 0) {
		recebidos = recv(csock, buffer, BUFFER_SIZE, 0);
		restantes -= recebidos;
		printf("%s\n",buffer);
		memset(&buffer, 0, BUFFER_SIZE);
	}

	closesocket(csock);
	closesocket(lsock);
	WSACleanup();

	return 0;
}