e.g. of code to setup a `server`
 ```
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(), 8080))
sock.listen(5)  # listen for incoming connections
print("Server started...")
 ```

`.bind()` accepts (IP address and port) pair. (Hostname | '0.0.0.0' | '' are also accepted).

(IP address and port) defines the access restrictions for the socket created. Using '0.0.0.0'or '' means that it can accept connections from `any` IPv4 address provided. Specifying an IP address or hostname makes it more secure as you only bind sockets to a dedicated interface.