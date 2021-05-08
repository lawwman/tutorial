# Socket Programming

## Transmission Control Protocol - TCP
When sending files from point to point, a large file would take a long time to reach the destination and block connection. To reduce congestion, files are chopped into small packets.

TCP makes sure that all the packets arrive in their correct destination, and re-ordered into correct sequence (packets might take different routes and arrive at different times).

TCP also sends an acknowledgement that packet was received, so if a packet gets lost, the sender will know from the lack of ACK and resends it.

## IP Address, Port, Socket
- IP Address, 4 byte identifier separated by dots. Used in Internet Protocol. You only have 1 IP address, so its not enough to connect multiple requests. The answer to that is ports.

- A port is a number that identifies the specific application/service on your computer that's attempting to access the network
- - `IP Addresses` gets the info to the right computer.
- - The `port` gets the info to the right application/service on the computer.

- A Socket is a combination of IP Address and port. One endpoint of a 2 way communication link between 2 programs running on a network. Socket is bound to a port number so that the TCP layer can identify the application that data is destined to be sent to.

## Hostname
Hostname - plaintext name identifying a host in a given domain.
- On a LAN, a server's hostname might be a nickname like mailserver1.
- On the internet, a hostname makes up part of the web address and has 3 parts: subdomain, domain name and top-level domain. For e.g. The hostname `whatis.techtarget.com` (subdomain: 'whatis', domain: 'techtarget', top-level domain: '.com')



