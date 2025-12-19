# CN Lab – Assignment 10: Custom TCP and ICMP with RAW Sockets

## Objective
To learn how to use **raw sockets** in C to manually construct and send custom TCP and ICMP packets, including control over header fields and payload. [web:152][web:143]

## Problem Statement
Write **two** C programs that use raw sockets:

1. **Raw TCP packet generator**  
   - Create a TCP packet using a raw socket where:
     - IP and TCP headers are filled manually (source/destination IPs, ports, flags, etc.). [web:152][web:149]  
     - The **TCP payload contains your roll number** as ASCII text.  
   - Send the crafted packet to a target IP address using `sendto` on a raw socket. [web:152][web:148]

2. **Raw ICMP timestamp message generator**  
   - Create ICMP **Timestamp Request** packets (ICMP type 13, code 0) towards a target IP. [web:153][web:150]  
   - Fill ICMP header fields: type, code, identifier, sequence number, and timestamp fields (originate, receive, transmit). [web:153][web:157]  
   - Send the ICMP packets using a raw socket so that the **receiver can capture and display them in Wireshark**. [web:150][web:157]

The receiver (or an observing host) must run Wireshark and confirm that the crafted TCP and ICMP messages appear correctly on the wire. [web:150][web:154]

## Learning Outcomes
After completing this assignment, you will:

1. Understand how to use **raw sockets** to build custom IP/TCP and IP/ICMP packets at user level. [web:152][web:160]  
2. Gain experience generating packets with manually set headers and payloads, and validating them using Wireshark. [web:150][web:154]

## Program 1: Raw TCP Packet with Roll Number

### Design requirements

- Use a raw socket such as:  
socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

text
or an `AF_PACKET`/`SOCK_RAW` variant on Linux (depending on the approach used). [web:152][web:146]

- Manually build a buffer containing:
1. IPv4 header (`struct iphdr`). [web:149]  
2. TCP header (`struct tcphdr`). [web:152][web:145]  
3. Payload: your roll number as text, e.g., `"ROLL: 23XYZ001"`.  

- Set key fields:
- IP header: version, IHL, total length, protocol = TCP, source/destination IPs, TTL, checksum. [web:149]  
- TCP header: source/destination ports, sequence/ack numbers (can be arbitrary for this lab), flags (e.g., SYN or PSH), window size, checksum. [web:152][web:145]

- Compute checksums:
- Implement functions to compute IP and TCP checksums using standard Internet checksum algorithm. [web:149][web:160]

- Send the packet using `sendto()` to the destination IP. [web:152][web:148]

Run Wireshark on the path between sender and receiver and verify:
- The packet appears as TCP, with your chosen ports.  
- The payload in the TCP segment shows your roll number. [web:152][web:150]

## Program 2: Raw ICMP Timestamp Messages

### Design requirements

- Use a raw socket for ICMP, for example:  
socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

text

- Manually construct an IPv4 header + ICMP Timestamp Request packet, or rely on the kernel for IP header depending on your platform and privileges. [web:150][web:153]

- Use ICMP **Timestamp** message fields: [web:153][web:157]  
- Type = 13 (Timestamp Request), Code = 0.  
- Identifier and sequence number (arbitrary but consistent).  
- Originate timestamp, Receive timestamp, Transmit timestamp (e.g., milliseconds since midnight UTC or system time).  

- Compute the ICMP checksum over the ICMP header and data. [web:150][web:157]

- Send the packet using `sendto()` to the target IP. [web:150]

At the receiver side (or observer):

- Start Wireshark and apply filter `icmp`. [web:150]  
- Confirm that:
- ICMP packets are of type 13 (Timestamp Request) and corresponding type 14 (Timestamp Reply) if the target responds. [web:157][web:153]  
- Timestamps and identifiers match what your program set.

## Implementation Hints

- Raw sockets typically require **root privileges**, so run your programs with `sudo`. [web:152][web:161]  
- On some systems, you may need to set `IP_HDRINCL` with `setsockopt` so the kernel knows you provide your own IP header for TCP packets. [web:152][web:149]  
- Use structures from `<netinet/ip.h>`, `<netinet/tcp.h>`, and `<netinet/ip_icmp.h>` if available, or define your own packed structs. [web:152][web:160]  
- Use small payloads and local/Mininet IPs to simplify debugging.

## Expected Deliverables

Submit:

- C source code for:
- Raw TCP packet generator with roll‑number payload. [web:152][web:145]  
- Raw ICMP timestamp packet generator. [web:150][web:153]  

- A brief README/report describing:
- How you construct IP, TCP, and ICMP headers, and how checksums are computed. [web:149][web:160]  
- How to compile and run each program (including the need for root privileges). [web:152][web:146]  
- Wireshark screenshots showing:
  - The custom TCP packet with your roll number visible in the payload.  
  - The ICMP Timestamp messages visible with correct type/code and timestamps. [web:150][web:153]
