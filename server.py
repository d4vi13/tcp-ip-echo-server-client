import socket
import sys

#Primeiro passo: criar socket 
'''
socket.AF_INET é uma familia de endereços, designa o tipo de endereço
com qual o socket se comunica, nesse caso IPV4

socket.SOCK_STREAM e socket.SOCK_DGRAM designam protocolo de comunicação,
TCP ou UDP, respectivamente 
'''
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

'''
primeiro item - ip
segundo item - porta (portas não privilegiadas > 1023)
'''

server_adress=('192.168.1.78',10000)


#defines the local port and interface address for the connection
server.bind(server_adress)

#começa ouvir a porta
server.listen(1)

print("Esperando por coneção: ")

"""
Wait for an incoming connection. Return a new socket representing
the connection, and the address of the client. For IP sockets, 
the address info is a pair (hostaddr, port).
"""
connection, client_adress = server.accept()

print("Conexão estabelecida: ", client_adress)

data = True
while data != 'tchau':
    data = connection.recv(1000).decode()
    print("Recebido: ",data)
    connection.sendall(data.encode())

connection.close()
server.close()

