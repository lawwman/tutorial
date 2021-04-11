# Socket Programming

## Handle, Pointer and References
- A handle is usually an opaque reference to an object. The type of the handle is unrelated to the object referenced. Consider for example a file descriptor returned by `open()` system call. The type is `int` but it represents an entry in the open files table. The actual data stored in the table is unrelated to the `int` that was returned by `open()` freeing the implementation from having to maintain compatibility (i.e. the actual table can be refactored transparently without affecting user code. Handles can only be used by functions in the same library interface, that can remap the handle back to the actual object.

- A pointer is the combination of an address in memory and the type of the object that resides in that memory location. The value is the address, the type of the pointer tells the compiler what operations can be performed through that pointer, how to interpret the memory location. Pointers are transparent in that the object referenced has a concrete type that is present from the pointer. Note that in some cases a pointer can serve as a handle (a `void*` is fully opaque, a pointer to an empty interface is just as opaque).

- References are aliases to an object. That is why you cannot have a reference to a reference: you can have multiple aliases for an object, but you cannot have an alias of an alias. As with pointers references are typed. In some circumstances, references can be implemented by the compiler as pointers that are automatically dereferenced on use, in some other cases the compiler can have references that have no actual storage. The important part is that they are aliases to an object, they must be initialized with an object and cannot be reseated to refer to a different object after they are initialized. Once they are initialized, all uses of the reference are uses of the real object.

## Transmission Control Protocol - TCP
When sending files from point to point, a large file would take a long time to reach the destination and block connection. To reduce congestion, files a chopped into small packets.

TCP makes sure that all the packets arrive in their correct destination, and re-ordered into correct sequence (packets might take different routes and arrive at different times).

TCP also sends an acknowledgement that packet was received, so if a packet gets lost, the sender will know from the lack of ACK and resends it.

## IP Address, Port, Socket
- IP Address, 4 byte identifier separated by dots. Used in Internet Protocol. You only have 1 IP address, so its not enough to connect multiple requests. The answer to that is ports.

- A port is jsut a number that identifies the specific application/service on your computer that's attempting to access the network. IP Address gets the info to the right computer, the port gets the info to the right application/service on the computer.

- A Socket is a combination of IP Address and port. One endpoint of a 2 way communication link between 2 programs running on a network. Socket is bound to a port number so that the TCP layer can identify the application that data is destined to be sent to.

## Hostname
Hostname - plaintext name identifying a host in a given domain.
- On a LAN, a server's hostname might be a nickname like mailserver1.
- On the internet, a hostname makes up part of the web address and has 3 parts: subdomain, domain name and top-level domain. For e.g. The hostname `whatis.techtarget.com` (subdomain: 'whatis', domain: 'techtarget', top-level domain: '.com')



