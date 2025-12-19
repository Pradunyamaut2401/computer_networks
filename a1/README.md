# Computer Networks Laboratory  
## Assignment – 1

### Title  
**Implementation of Basic TCP Client–Server Communication Using Socket Programming in Mininet**

---

## Objective  
To gain first-hand practical experience of **basic TCP socket programming** by implementing a simple client–server communication model where the client sends a message and the server responds accordingly.

---

## Problem Statement  
Develop TCP client and server programs such that:
- The **TCP client** sends the message **"Hi"**.
- The **TCP server** receives the message and replies with **"Hello"**.
- The programs are executed on **two different Mininet hosts** using **xterm terminals**.

---

## Tools and Technologies Used  
- **Operating System**: Ubuntu (Linux)  
- **Network Emulator**: Mininet  
- **Programming Language**: C  
- **Compiler**: GCC  
- **Protocol**: TCP (Transmission Control Protocol)  
- **Terminal Interface**: xterm  

---

## Conceptual Background  

### TCP Socket Programming  
TCP (Transmission Control Protocol) is a **connection-oriented and reliable** transport layer protocol.  
Socket programming allows processes to communicate over a network using TCP/IP.

In a TCP-based client–server model:
- The **server** creates a socket, binds it to an IP address and port, listens for incoming connections, and responds to client requests.
- The **client** creates a socket and initiates a connection with the server using the server’s IP address and port number.

---

## Network Topology  
- Two Mininet hosts:
  - `h1` → TCP Server  
  - `h2` → TCP Client  
- Hosts are connected via a default Mininet switch.

---

## Steps to Execute the Experiment  

### Step 1: Start Mininet  
Open a terminal and run:
```bash
sudo mn

Step 2: Open xterm Windows

In the Mininet CLI:
xterm h1 h2
This opens two xterm terminals:

h1 for the server

h2 for the client
Step 3: Server Program Execution (h1)

Create the server file:

nano tcp_server.c


Compile the server program:

gcc tcp_server.c -o tcp_server


Run the server:

./tcp_server

Step 4: Client Program Execution (h2)

Create the client file:

nano tcp_client.c


Compile the client program:

gcc tcp_client.c -o tcp_client


Run the client:

./tcp_client

Expected Output
Server Side Output
Server waiting for connection...
Client connected
Received message from client: Hi
Sent response: Hello

Client Side Output
Connected to server
Sent message: Hi
Received message from server: Hello

Observations

TCP connection is successfully established between client and server.

Data transfer occurs reliably and in order.

Client waits for the server response after sending data.

Server correctly processes and responds to the client request.

Learning Outcomes

After completing this experiment, the student will be able to:

Understand TCP client–server architecture.

Implement basic socket programming using C.

Run networking applications in a Mininet environment.

Understand the TCP workflow:

socket() → bind() → listen() → accept() → send()/recv() → close()

Gain hands-on exposure to network emulation and testing.

Applications

Client–server systems

Web applications

Chat applications

File transfer services

Conclusion

This experiment demonstrates a simple yet effective TCP client–server communication model using socket programming. The client initiates communication by sending a message, and the server responds appropriately. This experiment forms the foundation for understanding more advanced networking and distributed system concepts.

Folder Structure
CN_Lab/
 └── Assignment_1/
     ├── tcp_server.c
     ├── tcp_client.c
     └── README.md

