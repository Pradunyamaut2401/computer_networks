# Computer Networks Lab

This repository contains Computer Networks (CN) laboratory assignments implemented using **C socket programming** and tested on **Mininet**.

---

## 📁 Assignment 1 (a1)

### Objective
To gain first-hand experience of basic **TCP socket programming** using a client–server model.

---

### Problem Statement
Write a TCP client and server program where:
- The client sends the message **"Hi"**
- The server responds with the message **"Hello"**

---

### Tools & Technologies
- C Programming Language
- TCP/IP Socket Programming
- Mininet
- Linux (Ubuntu)
- xterm

---

### Folder Structure
cn/
└── a1/
├── tcp_server.c
└── tcp_client.c

-Open terminals for both hosts:
xterm h1 h2
Compile the programs:

On h1 (Server):

gcc tcp_server.c -o tcp_server


On h2 (Client):

gcc tcp_client.c -o tcp_client


Run the programs:

On h1:

./tcp_server


On h2:

./tcp_client

Expected Output

Server Output

Client says: Hi


Client Output

Server replies: Hello

Learning Outcomes

Understanding of TCP client–server communication

Basics of socket creation, binding, listening, and connecting

Hands-on experience with Mininet and xterm

Practical exposure to network programming concepts

Author

Pradunya Maut
MCA | Computer Networks Lab
-
