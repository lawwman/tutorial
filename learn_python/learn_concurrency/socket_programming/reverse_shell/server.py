import socket

QUIT = "quit"
UTF_ENCODE = "utf-8"

def is_valid_command(input_command):
    if len(input_command) == 0:
        print("no command given")
        return False
    return True

def send_commands(conn):
    while True:
        cmd = input()
        if cmd == QUIT:
            conn.send(QUIT.encode(UTF_ENCODE))
            break
        if is_valid_command(cmd):
            conn.send(cmd.encode(UTF_ENCODE))
            print(f"Client response: {str(conn.recv(1024), UTF_ENCODE)}", end='')
        


host = '127.0.0.1'  # loopback interface
port = 12345
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    print(f"binding socket to {host} at port: {port}")
    s.bind((host, port))
    s.listen(5)
    conn, addr = s.accept()  # conn is a new socket used to send and receive data on the connection
    print(f"connection established with {addr[0]} at port: {addr[1]}")
    send_commands(conn)
    conn.close()

except Exception as e:
    print(e)
finally:
    print('closing the socket...')
    s.close()
    print('done!')
