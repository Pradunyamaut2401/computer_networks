# CN Lab – Assignment 9: File Upload and Download over TCP

## Objective
To use **TCP sockets** in C for reliable file transfer between two hosts, implementing both file download (server → client) and upload (client → server), and measuring the transfer time in each case. [web:138][web:130]

## Problem Statement
Write a TCP client–server socket program in C that:

- Runs on two different hosts in a Mininet setup (one acting as server, one as client). [web:101][web:113]  
- Supports two operations:
  1. **Download**: Client requests a file located in the server’s directory and stores the received file in its own directory. [web:128][web:131]  
  2. **Upload**: Client sends a file from its directory to the server, which stores it in the server directory. [web:139][web:135]  
- Measures and displays the **time taken** for each transfer (download and upload) at both client and server using `time.h` functions. [web:123][web:129]

## Environment and Directory Setup

Follow these steps on the machine running Mininet:

1. Create two directories, for example:  
   - `server_dir/` for server files.  
   - `client_dir/` for client files.  

2. Start Mininet and open two xterms: one for the server host, one for the client host. [web:101]  

3. In the server host xterm:  
   - `cd server_dir` and run the compiled **server** program.  

4. In the client host xterm:  
   - `cd client_dir` and run the compiled **client** program.  

5. Place:
   - A test file in `server_dir` (for client **download**).  
   - Another test file in `client_dir` (for client **upload**).  

## Protocol and Program Behavior

### Connection model (TCP)

- The server:
  - Creates a TCP socket (`AF_INET`, `SOCK_STREAM`), binds to a port, and calls `listen`. [web:125][web:113]  
  - Accepts a client connection using `accept`.  

- The client:
  - Creates a TCP socket and connects to the server IP and port using `connect`. [web:125]

### Simple application protocol

Define a basic text protocol to indicate the operation:

- For download:
  - Client sends: `GET filename\n` [web:139][web:128]  
- For upload:
  - Client sends: `PUT filename\n`  

Server behavior:

- On receiving `GET filename`:
  - Check if file exists in server directory.  
  - Send file size (or an error message) followed by the file bytes. [web:128][web:131]  

- On receiving `PUT filename`:
  - Receive file size/meta (if you choose) and then read file bytes, saving into server directory. [web:139][web:135]

Use a loop with `send` / `recv` to transfer file data in chunks (e.g., 4 KB buffers) until the whole file is sent/received. [web:132][web:134]

## Measuring Transfer Time

Use `time.h` to measure transfer duration:

- Include `<time.h>`.  
- Use `clock_t start = clock();` before starting file transfer and  
  `clock_t end = clock();` after finishing transfer. [web:123]  
- Compute elapsed seconds as:  
double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

text
- Display the time taken at:
- **Client side** for download and upload separately.  
- **Server side** for sending (download) and receiving (upload). [web:123][web:129]

Alternatively, for higher resolution you can use `gettimeofday` (from `<sys/time.h>`), but `clock()` is sufficient for this lab. [web:123][web:132]

## Implementation Hints

- Make sure to:
- Use binary mode for file operations: `fopen("file", "rb")` for read, `fopen("file", "wb")` for write. [web:130][web:135]  
- Loop on `send` and `recv` until all bytes are transmitted/received:
  - Handle partial sends/receives. [web:132][web:134]  
- Send file size first (e.g., as a fixed-length header or text number) so the receiver knows how many bytes to expect. [web:128][web:139]  

- For **download**:
- Client:
  - Sends `GET filename`.  
  - Receives file size (if protocol includes it).  
  - Starts timer, receives file in chunks, writes to `downloaded_<filename>`.  
  - Stops timer and prints download time. [web:130][web:135]  
- Server:
  - Opens requested file in server directory.  
  - Starts timer, sends file content in chunks.  
  - Stops timer and prints send time. [web:127][web:131]

- For **upload**:
- Client:
  - Sends `PUT filename`.  
  - Opens file in client directory.  
  - Starts timer, sends file content in chunks.  
  - Stops timer and prints upload time. [web:130][web:135]  
- Server:
  - Prepares to create/overwrite target file in server directory.  
  - Starts timer, receives incoming bytes, writes to file.  
  - Stops timer and prints receive time. [web:127][web:133]

## Expected Deliverables

Submit:

- C source code for:
- TCP **server** implementing file download (GET) and upload (PUT) and timing for both.  
- TCP **client** implementing the same protocol and timing. [web:130][web:135]  

- A brief README/report describing:
- Directory setup and run commands in Mininet (which host runs server, which runs client). [web:101]  
- Protocol format (GET/PUT, how filename and size are sent). [web:128][web:139]  
- Transfer times measured for:
  - Client download from server.  
  - Client upload to server.  

- Optional: note any differences observed between upload and download times and relate them to TCP’s reliable stream behavior. [web:138]
