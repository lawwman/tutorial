# Socket Definition
*A socket is one endpoint of a two-way communication link between two programs running on the network. A socket is bound to a port number so that the TCP layer can identify the application that data is destined to be sent to.*

Socket is identified by:
- IP address of the network node
- port number within the network node

## How does it relate to TCP and UDP
In the OSI model, TCP and UDP are in the transport layer. Socket belongs to the session layer, sitting **above** TCP/UDP. TCP and UDP both require sockets to work.
- UDP would require a datagram socket
- TCP would require a stream socket

## then wtf is socket programming?
Wait a minute, these seems like it all happens automatically! what do people mean when they talk abt socket programming?

introducing web sockets! https://stackoverflow.com/questions/4973622/difference-between-socket-and-websocket. Yes there is a difference btw websocket and socket.

# WebSocket Definition
https://www.geeksforgeeks.org/what-is-web-socket-and-how-it-is-different-from-the-http/

http:
- unidirectional (client sends req, server respond. server does not send req)
- for each req, new connection is open. after each response, connection is close
- stateless (each connection is "new" and does not remember what happened before)

websocket:
- bidirectional (both sides can initiate a msg)
- connection stays open until either client or server terminates
- stateful

## When should we use it?
- when data is continuously transmitted between client and server, maintaining the same connection saves a lot of time -> improved performance.
- when we have an application that requires the server to be able to push to client. can only achieve with birectional communication.

## useful for
- Real-time web application
- Gaming application
- Chat application

- [more indepth read](https://sookocheff.com/post/networking/how-do-websockets-work/)