# CN Lab – Assignment 3: UDP Socket Programming

## Objective
To gain hands-on experience with **UDP** socket programming by re-implementing the Assignment 2 client–server application using UDP instead of TCP. [web:12]

## Problem Statement
Redo Assignment 2 using UDP sockets. The application logic, data to be exchanged, and overall client–server interaction pattern should remain the same as in Assignment 2, but all communication must use UDP (Datagram) sockets. [web:12]

You should:
- Implement a UDP server that waits for datagrams from clients, processes the received data (as in Assignment 2), and sends appropriate responses. [web:12][web:9]  
- Implement a UDP client that sends requests to the server and displays the responses. [web:12]

## Learning Outcomes
After completing this assignment, you will be able to:
1. Understand the basics of **UDP** socket programming (socket type, bind, sendto, recvfrom, close). [web:12][web:9]  
2. Differentiate UDP from TCP in terms of connection setup, reliability, and message boundaries. [web:10]  
3. Design a simple client–server application that works correctly over an unreliable, connectionless transport. [web:12]

## Requirements

- Programming language: C / C++ / Python (as specified by your lab instructor).
- Transport protocol: UDP only (use `SOCK_DGRAM` or equivalent). [web:12][web:5]  
- Architecture: One server process, one or more client processes.
- Functionality: Same as Assignment 2 (e.g., message echo, arithmetic operation, string manipulation, or array processing), but implemented over UDP. [web:16]

If Assignment 2, for example, was:
- Echo service (client sends a string, server returns the same string), or  
- Array processing (client sends an integer array, server computes a result and sends it back),  

then replicate that logic here using datagrams. [web:16]

## Suggested Design (Server)

Typical UDP server steps: [web:12][web:9]

1. Create a UDP socket.  
2. Bind the socket to a well-known IP address and port.  
3. Repeatedly:
   - Wait for a datagram from a client (`recvfrom` or equivalent).  
   - Process the received data according to Assignment 2’s logic.  
   - Send the response back to the client using the address obtained from `recvfrom` (`sendto` or equivalent).  
4. Close the socket before terminating.

## Suggested Design (Client)

Typical UDP client steps: [web:12][web:9]

1. Create a UDP socket.  
2. Prepare the server’s IP address and port.  
3. Send the request data to the server using `sendto`.  
4. Wait for the server’s response using `recvfrom`.  
5. Display the result/output to the user.  
6. Optionally repeat steps 3–5 for multiple requests, then close the socket.

## Files and Structure

Recommended structure:
assignment3-udp/
├── server.c # or server.cpp / server.py
├── client.c # or client.cpp / client.py
└── README.md


- `server.*`: Implements the UDP server based on the logic from Assignment 2. [web:12]  
- `client.*`: Implements the UDP client that interacts with the server. [web:12]

## Compilation and Execution

Example for C (adjust filenames and commands as needed):

Compile
gcc server.c -o server
gcc client.c -o client

Run server (in one terminal)
./server

Run client (in another terminal)
./client

For C++:

g++ server.cpp -o server
g++ client.cpp -o client

Ensure that the server is started **before** running the client, and that both use the same port number and compatible IP settings. [web:12][web:9]

## Input/Output Format

Use the same input and output format as Assignment 2. For example: [web:16]

- If Assignment 2 used:
  - Input: Single line string from client.  
  - Output: Processed string (e.g., uppercased) from server.  

then keep the same behavior here, only changing the underlying transport to UDP.

Document in comments inside `client` and `server` the exact input and output formats supported.

## Testing Guidelines

- Test with multiple sequential requests from a single client. [web:12]  
- Optionally test with multiple clients running concurrently on the same or different machines. [web:12]  
- Verify:
  - Correctness of results for different inputs.  
  - Behavior when the server is not running (client should handle failure gracefully).  
  - Behavior when messages are empty or unusually long.

## Notes and Hints

- UDP is connectionless: there is no `listen` or `accept` phase; the server simply waits for datagrams. [web:12]  
- UDP preserves message boundaries but does **not** guarantee delivery, ordering, or duplication suppression. Simple lab assignments typically ignore loss and assume a reliable local network. [web:10][web:19]  
- Reuse any parsing or processing logic from Assignment 2; only the socket setup and send/receive calls change. [web:12]

## Submission

Submit the following:
- Source code files for client and server.  
- This `README.md` describing objective, design, compilation, and usage.  
- Sample screenshots or logs demonstrating at least two successful client–server interactions.


