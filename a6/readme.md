This assignment asks you to build a very simple C-based packet sniffer / analyzer that uses TCP/IP-related libraries (sockets or libpcap) to capture packets from a network interface, extract TCP/IP header fields, and treat that as a “mini network simulator” for TCP traffic analysis.​

text
# CN Lab – Assignment 6: Simple C-based TCP Traffic Analyzer

## Objective
To gain practical knowledge of **TCP/IP C libraries** by developing a simple C-based network analyzer that listens on an Ethernet interface, extracts headers and data from incoming packets, and focuses on TCP traffic. [web:74][web:71]

## Problem Statement
Develop a C program that:

1. Uses TCP/IP-related C libraries (including sockets or packet-capture APIs) to listen to incoming packets on a specified Ethernet interface. [web:72][web:80]  
2. Extracts and prints header information (Ethernet, IP, TCP) and selected data from captured packets, with specific attention to TCP segments. [web:72][web:70]

The goal is not to simulate full protocol behavior, but to **observe and analyze real TCP traffic** as it traverses the interface, effectively acting as a simple network simulator/visualizer for TCP flows. [web:71][web:74]

## Learning Outcomes
After completing this assignment you will be able to:

1. Use low-level **TCP/IP libraries** in C (e.g., raw sockets or libpcap) to capture packets from a network interface. [web:74][web:71]  
2. Parse Ethernet, IP, and TCP headers from raw packet buffers in C structures. [web:73][web:82]  
3. Relate captured header fields (ports, sequence numbers, flags) to TCP connection behavior. [web:72][web:77]

## Design Overview

You may implement the analyzer in one of two common ways (as allowed by your instructor):

- Using **raw/packet sockets** (e.g., `AF_PACKET`, `SOCK_RAW`) to receive Ethernet frames directly from the kernel. [web:72][web:78]  
- Using **libpcap** (`pcap_open_live`, `pcap_loop`) to capture packets and pass them to a callback that parses headers. [web:74][web:71]

In both cases, your program will:

1. Open an interface in promiscuous or capture mode.  
2. Continuously read incoming packets into a buffer.  
3. Cast portions of the buffer to C structs for Ethernet, IP, and TCP headers. [web:73][web:82]  
4. Print key header fields and optionally a small part of the payload for TCP packets. [web:72][web:70]

## Suggested Implementation Steps

### 1. Include required headers and data structures

Typical headers (adjust to your environment): [web:72][web:74]

- `<sys/socket.h>`, `<netinet/in.h>`, `<arpa/inet.h>`, `<netinet/ip.h>`, `<netinet/tcp.h>`, `<net/ethernet.h>`  
- If using libpcap: `<pcap.h>` [web:74][web:71]

Define/Use structures for:

- Ethernet header (`struct ethhdr` or custom struct). [web:72]  
- IP header (`struct ip` or `struct iphdr`, depending on platform). [web:73]  
- TCP header (`struct tcphdr`). [web:73][web:82]

### 2. Open capture on Ethernet interface

**Option A: Raw socket approach (Linux AF_PACKET)** [web:72][web:80]

- Create a socket:
socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

text
- Bind it to a specific interface, e.g., `eth0`, using `struct sockaddr_ll`.  
- Use `recvfrom()` or `recv()` in a loop to receive full frames into a buffer. [web:72][web:78]

**Option B: libpcap approach** [web:74][web:71]

- Open interface:
pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);

text
- Use `pcap_loop(handle, 0, callback, NULL);`  
- In `callback`, parse the captured packet buffer. [web:71][web:74]

### 3. Parse Ethernet, IP, and TCP headers

Within the packet buffer: [web:72][web:73]

- Ethernet header at start:  
struct ethhdr *eth = (struct ethhdr *)buffer;

text
- IP header after Ethernet header:  
struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));

text
- Check protocol field; only continue if `ip->protocol == IPPROTO_TCP`. [web:73]  
- TCP header after IP header (IP header length is `ip->ihl * 4` bytes):  
struct tcphdr *tcp = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);

text

Extract and print fields such as: [web:73][web:72]

- From Ethernet header: source/destination MAC, EtherType.  
- From IP header: source/destination IP, total length, TTL, protocol.  
- From TCP header: source/destination port, sequence number, acknowledgment number, flags (SYN, ACK, FIN, etc.).  

Optionally, print the first N bytes of payload following the TCP header for inspection. [web:72][web:70]

### 4. Basic “simulation” / analysis features

To make it a “simple network simulator” for TCP traffic, add:

- Counting of TCP packets per flow (defined by src/dst IP and port). [web:82]  
- Display of connection-like behavior, e.g., when a SYN/SYN-ACK/ACK handshake is observed, print “New TCP connection detected”. [web:72][web:77]  
- Per-flow statistics: number of packets, approximate data bytes transferred. [web:70][web:82]

These features help visualize how TCP connections behave using only captured headers, without implementing the full TCP stack.

## Compilation and Execution

Example (raw socket or libpcap-based sniffer):

gcc tcp_sniffer.c -o tcp_sniffer # add -lpcap if using libpcap
sudo ./tcp_sniffer eth0 # pass interface name as an argument

text

Root privileges are typically required for raw sockets and live packet capture. [web:72][web:74]

Generate TCP traffic (e.g., `curl`, `wget`, `ssh`, `iperf`) while your program is running to observe headers in real time. [web:72][web:71]

## Expected Deliverables

Submit:

- C source file(s) implementing the TCP traffic analyzer/sniffer.  
- A brief README/report describing:
  - Which C libraries/APIs were used (raw sockets, libpcap, or both). [web:74][web:80]  
  - How to compile and run the program (including required privileges).  
  - Example output showing extracted Ethernet, IP, and TCP header fields for at least one connection. [web:72][web:73]  
- (Optional) Screenshots/logs illustrating detection of TCP flags and simple per-flow statistics. [web:72][web:82]
