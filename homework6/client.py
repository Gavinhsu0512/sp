import socket
import threading
import sys

def receive_messages(client_socket):
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                break
            print(message, end='')
        except:
            break

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('127.0.0.1', 9999))

    receive_thread = threading.Thread(target=receive_messages, args=(client,))
    receive_thread.start()

    try:
        while True:
            message = input()
            client.send(message.encode('utf-8'))
            if message.lower() == 'exit':
                break
    except KeyboardInterrupt:
        client.close()
        sys.exit()

    client.close()

if __name__ == '__main__':
    main()
