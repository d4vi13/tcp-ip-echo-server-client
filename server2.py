import socket
import sys

server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

server_adress=('200.17.212.225',10000)

server.bind(server_adress)

server.listen(1)

print("Esperando por coneção: ")

connection, client_adress = server.accept()

print("Conexão estabelecida: ", client_adress)

int tamanho = connection.recv(256).decode();

print("Tamanho do arquivo: ", tamanho);

dados_restantes = tamanho;
while dados_restantes > 0 :
	data = connection.recv(1024).decode()
	print("Recebido: ",data)
	print("Dados restantes: "dados_restantes)
	print(data)
	dados_restantes -= sys.getsizeof(data);
	#connection.sendall(data.encode())

'''
data = True
while data != 'tchau':
    data = connection.recv(1000).decode()
    print("Recebido: ",data)
    connection.sendall(data.encode())
'''
connection.close()
server.close()
















