e.g. of code to setup a `server`
 ```
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(), 8080))
sock.listen(5)  # listen for incoming connections
print("Server started...")
 ```
## Bind
`.bind()` accepts (IP address and port) pair. (Hostname | '0.0.0.0' | '' are also accepted).

While reading up on Socket programming, `bind()` has always been a weird function for me to accept, particularly with the IP Address argument. It accepts the following format:
- actual ip address like '192.68.0.1'
- '0.0.0.0' which accepts ip addresses on any available interfaces
- empty string which has the same behavior as '0.0.0.0'
- hostname (e.g: "localhost"), which resolves to an IP address

Doubts:
- if I assign '0.0.0.0', does it mean that I can bind this socket to any IP address in the world?
- What kind of IP addresses can I use? Am I free to choose?

One key thing to note: `bind() defines a relationship between the socket you created and the addresses that are available on your host`. The key is `available on your host`. If your host has multiple IP addresses, you are free to choose from any of them. The '0.0.0.0' accepts any IP addresses `that your host has`.

A possible reason for the host machine to have multiple IP addresses is if the host has multiple network interfaces.

Specifying an IP address or hostname makes it more secure as you only bind sockets to a dedicated interface.

To find your IP address and other info, type `ipconfig /all` on `cmd` (Windows).
To look at the state of your sockets, type `netstat` in terminal (any OS).