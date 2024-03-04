import socket
import sys 

#o que é um socket?
'''
Um socket é um das pontas de uma comunicação bidirecional entre
 dois programas na rede. O socket está ligado a um numero de porta, para
 que o TCP consiga identificar a aplicação para onde deve ser mandado os dados

 para mais informaações:https://docs.oracle.com/javase/tutorial/networking/sockets/definition.html
'''

#Primeiro passo: criar socket 
'''
socket.AF_INET é uma familia de endereços, designa o tipo de endereço
com qual o socket se comunica, nesse caso IPV4

socket.SOCK_STREAM e socket.SOCK_DGRAM designam protocolo de comunicação,
TCP ou UDP, respectivamente 
'''
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_adress=('192.168.1.78',10000)

#conectar cliente ao servidor
client.connect(server_adress)

data = True
while data != "tchau":
    message = input()

    print("SENDING",message)

    client.sendall(message.encode())
    print("ORIGINAL:",message)

    data = client.recv(1000).decode()
    print("ECHO:",data)
client.close()
