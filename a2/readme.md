# Computer Networks Laboratory  
## Assignment – 2

### Title  
**TCP Socket Programming for a Multi-Client Fruit Store Management System**

---

## Objective  
To gain practical experience in **TCP socket programming** by developing a simple multi-client server application where multiple clients interact with a centralized server to purchase fruits, update stock, and track customer transaction records.

---

## Problem Statement  
Implement a TCP-based client–server application with the following functionalities:

1. The **server maintains records of fruits** in the format:  
   `fruit-name, quantity, last-sold (server timestamp)`.
2. **Multiple clients** can connect to the server and purchase fruits **one at a time**.
3. The **fruit quantity is updated** on the server after every successful transaction.
4. If the requested quantity of a fruit is **not available**, the server sends a **regret message** to the client.
5. The server maintains and displays a list of **customer IDs <IP address, Port number>** who have already completed transactions.
6. The **total number of unique customers** who have performed transactions is displayed to the client **after every transaction**.

---

## Tools and Technologies Used  
- **Operating System**: Ubuntu (Linux)  
- **Network Emulator**: Mininet  
- **Programming Language**: C  
- **Compiler**: GCC  
- **Protocol**: TCP (Transmission Control Protocol)  
- **Terminal Interface**: xterm  

---

## Network Topology  
- `h1` → Server  
- `h2`, `h3` → Clients  
- Hosts connected via default Mininet switch  

---

## Steps to Execute the Experiment  

### Step 1: Start Mininet  
```bash
sudo mn
Step 2: Open xterm Windows for Hosts

In the Mininet CLI:
xterm h1 h2 h3
This opens three separate terminals:

h1 for the server

h2 and h3 for clients

Step 3: Server Program Setup and Execution (h1)

Create the server source file:

nano tcp_fruit_server.c


Compile the server program:

gcc tcp_fruit_server.c -o tcp_fruit_server


Run the server (server runs continuously using a loop):

./tcp_fruit_server

Step 4: Client Program Setup and Execution (h2 / h3)

Create the client source file:

nano tcp_fruit_client.c


Compile the client program:

gcc tcp_fruit_client.c -o tcp_fruit_client


Run the client:

./tcp_fruit_client


Repeat this step on multiple client hosts to simulate multiple customers.

Step 5: Client–Server Interaction

Client connects to the server.

Server sends current fruit stock information.

Client requests a fruit name and quantity.

Server checks availability:

If sufficient stock → transaction successful, quantity updated, timestamp recorded.

If insufficient stock → regret message sent.

Server updates and stores client ID <IP, Port>.

Server sends:

Updated stock information

Total number of unique customers so far

Data Maintained at Server
Fruit Record Format
Fruit Name | Quantity | Last Sold Timestamp

Customer Record Format
Client IP | Client Port

Expected Output
Server Side Output
Server started and listening...
Client connected: 10.0.0.2 : 50124
Sold: Apple | Qty: 2 | Time: 15:10:05
Client connected: 10.0.0.3 : 50130
Regret message sent (Insufficient stock)
Unique customers so far: 2

Client Side Output
Connected to Fruit Store Server
Available fruits received
Purchase request sent
Transaction successful
Total unique customers till now: 2

Observations

Server successfully handles multiple clients sequentially.

Fruit inventory is updated correctly after each sale.

Regret messages are sent when stock is insufficient.

Unique customers are tracked using IP address and port number.

Customer count increases dynamically after each new transaction.

Learning Outcomes

After completing this experiment, the student will be able to:

Implement multi-client TCP server applications.

Understand handling of multiple client sockets using accept().

Track client identity using IP address and port number.

Maintain shared server-side records safely.

Simulate real-world client–server systems using Mininet.

Conclusion

This experiment demonstrates a practical implementation of a multi-client TCP socket-based application. The server efficiently manages fruit inventory, handles multiple client requests, maintains customer records, and provides real-time updates to clients. This forms a strong foundation for understanding scalable and real-world networked applications.

Folder Structure
CN_Lab/
 └── Assignment_2/
     ├── tcp_fruit_server.c
     ├── tcp_fruit_client.c
     └── README.md

