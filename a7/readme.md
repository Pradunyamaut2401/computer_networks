This assignment asks you to build a UDP-based scientific-calculator client–server and then use Wireshark in Mininet to observe how UDP behaves, including any packet loss.​

text
# CN Lab – Assignment 7: UDP Scientific Calculator with Packet-Loss Detection

## Objective
To implement **client–server communication using UDP** where the server acts as a scientific calculator, and to study UDP reliability and packet loss using Wireshark in a Mininet environment. [web:5][web:101]

## Problem Statement
Develop a UDP client–server socket program with the following behavior:

- The **client** sends:
  - One or two numbers (integer or floating point), and  
  - A scientific calculator operation such as `sin`, `cos`, `*`, `/`, `inv` (1/x), etc. [web:85][web:99]  
- The **server** maintains a scientific calculator and:
  - Parses the expression (examples: `sin(x)`, `cos(x)`, `x+y`, `x*y`, `x/y`, `inv(x)`),  
  - Computes the result using C math functions, and  
  - Sends the result back to the client using UDP. [web:86][web:93]

You must then run this program between Mininet hosts and use Wireshark to check whether any UDP packets are lost during the transactions. [web:101][web:98]

## Learning Outcomes
After completing this assignment you will:

1. Understand how to implement **UDP client–server applications** for simple request–response transactions. [web:5][web:15]  
2. Gain experience using `math.h` to perform scientific calculations in C. [web:86][web:99]  
3. Observe the **unreliable nature of UDP**, and learn basic techniques to detect packet loss using sequence numbers and Wireshark traces. [web:88][web:100]

## Design Requirements

### Server

- Implement a UDP server that:
  - Creates a UDP socket (`SOCK_DGRAM`). [web:5]  
  - Binds to a known port on the Mininet host. [web:5]  
  - Receives expressions from clients using `recvfrom`.  
  - Parses the request string and evaluates the expression using `math.h` functions (e.g., `sin`, `cos`, `pow`, etc.). [web:86][web:99]  
  - Sends the result (as string, e.g., `"Result: 0.7071"`) back to the client with `sendto`. [web:85]

- Use `math.h` functions for scientific operations:
  - `sin()`, `cos()`, `tan()`, `sqrt()`, `pow()`, etc. [web:86][web:99]  
  - Ensure arguments to trigonometric functions are in **radians**, or clearly document if you convert from degrees. [web:86]

### Client

- Implement a UDP client that:
  - Creates a UDP socket. [web:5]  
  - Accepts user input such as:
    - Single-operand operations: `sin 1.5708`, `cos 0.5`, `inv 4`  
    - Two-operand operations: `add 3 5`, `mul 2.5 4`, `div 10 3`  
  - Encodes the request as a string, e.g., `"sin 1.5708"` or `"add 3 5"`, and sends it with `sendto` to the server. [web:85]  
  - Waits for the server’s reply using `recvfrom` and prints the result.

You can define your own simple text protocol, for example:

- Format: `op operand1 [operand2] seq`  
  - Examples: `sin 1.5708 1`, `add 3 5 2`  
  - `seq` is a sequence number used for loss detection (see below). [web:100]

## Handling UDP Packet Loss (Graceful Detection)

UDP does not guarantee delivery, ordering, or duplication. [web:97][web:91] Implement basic loss detection:

- Add a **sequence number** to each request from the client. [web:100][web:94]  
- The server:
  - Copies the sequence number into its reply.  
- The client:
  - Starts a timeout (e.g., using `select` with a timeout or non-blocking socket) after sending a request. [web:88]  
  - If no reply is received within the timeout:
    - Report “Possible packet loss for seq = X”.  
    - Optionally retransmit the request once or twice. [web:88][web:100]

In your README/report, clearly state that:

- UDP itself provides no built-in reliability; your sequence number + timeout mechanism is only for **detecting** and reacting to losses in this lab. [web:97][web:91]

## Wireshark and Mininet Usage

1. **Run in Mininet**  
   - Start Mininet with at least two hosts (e.g., `h1`, `h2`). [web:101]  
   - Run the server on `h2` and the client on `h1`, using their IP addresses.  

2. **Capture traffic with Wireshark**  
   - Start Wireshark on the Mininet VM interface (e.g., `eth0`) or on a specific host interface. [web:101]  
   - Apply a display filter like `udp && ip.addr==10.0.0.1 && ip.addr==10.0.0.2` to focus on the calculator traffic. [web:98]  

3. **Detecting packet loss in Wireshark**  
   - Verify sequence numbers in the UDP payloads:
     - Check whether any request `seq` value is missing in the observed packet stream. [web:92][web:100]  
   - Look for:
     - Client request payloads that have no corresponding server response with the same sequence number. [web:92]  
   - For more complex scenarios, you can export and compare client- and server-side captures, but in this lab one capture is usually enough. [web:92][web:95]

Demonstrate your Wireshark trace and any observed losses (or explain that no losses were seen on the local lab network) to your TA. [web:95][web:91]

## Implementation Hints

- Use a fixed-size buffer for messages (e.g., 256 bytes), and ensure you zero it before reuse. [web:5]  
- Use `sscanf` or `strtok` to parse the operation and operands from the received string. [web:85]  
- Validate input:
  - Avoid division by zero.  
  - Handle invalid operations by sending an error message to the client.  
- Use clear text formats for easier debugging in Wireshark (ASCII strings for requests and responses). [web:85][web:98]

## Expected Deliverables

Submit:

- UDP server and client source files implementing the scientific calculator and loss detection. [web:5][web:85]  
- A brief README/report describing:
  - Message format (how you encode operation, operands, and sequence numbers).  
  - How to compile and run server and client on Mininet hosts. [web:15][web:101]  
  - How you detect possible packet loss (timeout + sequence number). [web:88][web:100]  
- Wireshark screenshots or notes:
  - Showing at least one successful request–response exchange (request and matching reply). [web:98][web:95]  
  - If possible, a case where a packet was lost or retransmitted, or a statement that no loss was observed. [web:91]
