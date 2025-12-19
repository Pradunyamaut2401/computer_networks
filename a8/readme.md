
# CN Lab – Assignment 8: Multithreaded TCP Chat Server

## Objective
To understand **multi-threading with TCP sockets** by implementing a chat server where multiple clients can communicate in real time through the server, with all conversations logged to a file. [web:105][web:113]

## Problem Statement
Write a C program that:

- Implements a **TCP chat server** listening on a chosen port. [web:113]  
- Accepts multiple client connections; for each new client, the server creates a **separate thread** to handle it. [web:105][web:109]  
- Broadcasts every message received from any client to **all connected clients** (group chat behavior). [web:103][web:108]  
- Maintains a **message log** on the server side (`log.txt`), where each message is appended with a timestamp and (optionally) client identifier. [web:114][web:117]  
- Ensures each client sees conversations in real time (messages appear as they are sent). [web:116][web:119]

Clients can be simple TCP programs that:

- Connect to the server using IP and port. [web:113]  
- Send messages typed by the user.  
- Display messages broadcast by the server from other clients. [web:110][web:121]

## Learning Outcomes
After completing this assignment you will:

1. Understand how to use **pthread** threads with TCP sockets to handle multiple clients concurrently. [web:105][web:104]  
2. Learn how to **broadcast** messages to all connected clients from the server. [web:103][web:108]  
3. Implement basic **logging** of network conversations with timestamps to a text file. [web:114][web:117]

## Server Design

### Core components

- **Main listening socket**:
  - Create a TCP socket (`AF_INET`, `SOCK_STREAM`), `bind`, and `listen` on a server port. [web:113]  

- **Accept loop with threads**:
  - Use the pattern given in the hint, similar to: [web:105][web:109]  
    ```
    while ( (newfd = accept(sockfd,
                (struct sockaddr *)&client,
                (socklen_t *)&c)) )
    {
        printf("Accepted\n");
        if (pthread_create(&thread_id, NULL,
                           client_handler,
                           (void *)&newfd) < 0) {
            perror("Thread error");
            return 1;
        }
    }
    ```
  - In a robust implementation, allocate `newfd` on the heap (e.g., `int *p = malloc(sizeof(int)); *p = newfd;`) before passing to the thread, to avoid race conditions. [web:105][web:115]

- **Client tracking and broadcast**:
  - Maintain a global list/array of connected client sockets (e.g., `int clients[MAX_CLIENTS];` and a count). [web:108][web:114]  
  - Protect this list with a `pthread_mutex_t` to avoid race conditions when adding/removing sockets or broadcasting. [web:108]  
  - The `client_handler` thread:
    - Reads from its client in a loop (`recv`/`read`). [web:113]  
    - On each message:
      - Logs the message with timestamp to `log.txt`. [web:114]  
      - Broadcasts the message to all clients in the list (including or excluding the sender, as you choose). [web:103][web:108]  
    - On disconnect or error:
      - Removes its socket from the global list (under mutex) and closes it.

### Logging messages

- Open `log.txt` in append mode (`fopen("log.txt", "a")`). [web:114]  
- For each message, write a line with timestamp and client info, for example:  
  `2025-12-20 00:30:15 [client 2]: Hello everyone`  
- Use `time()`, `localtime()`, `strftime()` or similar to format timestamps. [web:117]

Ensure log writes are protected with a mutex if multiple threads write concurrently. [web:117]

## Client Design

Each client program should:

- Connect to the server using `connect()` to server IP and port. [web:113]  
- Use two loops (either via two threads or `select`):
  - One to read from stdin and send messages to the server. [web:110][web:121]  
  - One to receive messages from the server and print them in real time. [web:110]  
- A common pattern is to create a **receiver thread** that continuously reads from the socket and prints messages, while the main thread handles keyboard input. [web:110][web:112]

## Implementation Hints

- Use a fixed buffer size for messages (e.g., 512 bytes) and ensure it is null-terminated before treating as a string. [web:108]  
- Use `pthread_detach()` if you do not plan to `pthread_join()` threads, so their resources are freed automatically. [web:107]  
- Handle client disconnects gracefully:
  - `recv` returning 0 indicates the client closed the connection. [web:113]  
  - Remove the client socket from the list and close it.  
- Consider prefixing messages with a simple identifier or nickname so clients know who sent each message. [web:110][web:119]

## Expected Deliverables

Submit:

- Server source file implementing:
  - TCP listening socket and accept loop. [web:113]  
  - Per-client threads using `pthread_create`. [web:105]  
  - Broadcast to all connected clients. [web:103][web:108]  
  - Logging of messages with timestamps in `log.txt`. [web:114]  

- Client source file(s) implementing:
  - Connection to the server and real-time send/receive (using threads or equivalent). [web:110][web:121]  

- A short README/report describing:
  - Compilation and run commands for server and clients.  
  - How threads are used to handle multiple clients concurrently. [web:104][web:105]  
  - Sample `log.txt` content and screenshots of a group chat session.
