import socket
import threading
import os

clients = []

def handle_client(client_socket, addr):
    global clients
    client_socket.send(b'Welcome to the server. Type commands below:\n')
    while True:
        try:
            command = client_socket.recv(1024).decode('utf-8').strip()
            if not command:
                break
            
            if command.lower() == 'exit':
                client_socket.send(b'Goodbye!\n')
                break
            
            output = os.popen(command).read()
            broadcast_message(f'Command executed by {addr}: {command}\n{output}\n')
        except ConnectionResetError:
            break

    client_socket.close()
    clients.remove(client_socket)
    broadcast_message(f'Client {addr} disconnected.\n')

def broadcast_message(message):
    global clients
    for client in clients:
        try:
            client.send(message.encode('utf-8'))
        except:
            client.close()
            clients.remove(client)

def main():
    global clients
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 9999))
    server.listen(5)
    print('Server started on port 9999')

    while True:
        client_socket, addr = server.accept()
        print(f'Accepted connection from {addr}')
        clients.append(client_socket)
        broadcast_message(f'Client {addr} connected.\n')
        client_handler = threading.Thread(target=handle_client, args=(client_socket, addr))
        client_handler.start()

if __name__ == '__main__':
    main()
