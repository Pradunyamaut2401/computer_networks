
# CN Lab – Assignment 11: TCP SYN Flood using RAW Sockets

## Objective
To use **raw sockets** in C to generate a TCP SYN flooding attack towards a victim IP, and to observe the resulting TCP control‑message pattern of a SYN‑based DDoS in a controlled Mininet environment. [web:150][web:149]

## Problem Statement
Using Mininet with **six hosts**:

- 1 host as the **attacker** (running your raw‑socket program).  
- 1 host as the **victim** (running any TCP service or just listening on a chosen port).  
- 4 hosts designated as **agent devices** whose IP addresses will be used as spoofed sources. [web:150][web:157]

On the attacker host, write a C program that:

1. Uses a **raw socket** to manually build and send TCP packets with:
   - Proper IPv4 and TCP headers.  
   - TCP flag **SYN** set.  
   - Spoofed **source IP addresses** corresponding to the four agent hosts. [web:152][web:149]

2. Sends a high rate of SYN packets to the victim’s IP and target port, emulating a SYN flood. [web:150][web:154]

The goal is to:

- Generate a pattern where the victim sees many half‑open connections (SYN received, but no valid ACK from spoofed sources). [web:150]  
- Capture and analyze this behavior using Wireshark/tcpdump to understand DDoS‑style TCP control‑message patterns. [web:150][web:154]

> Run this only inside the isolated lab/Mininet environment, never on real networks.

## Learning Outcomes
After completing this assignment you will:

1. Understand how to use **raw sockets** to construct TCP SYN packets with custom header fields and spoofed IPs. [web:152][web:160]  
2. Recognize the characteristic **pattern of SYN flooding** in packet captures (many SYNs, corresponding SYN‑ACKs to spoofed addresses, and lack of final ACK). [web:150][web:153]

## Mininet Topology Setup

- Use Mininet to create at least 6 hosts (e.g., `h1`–`h6`). [web:101]  
  - Choose one host as **victim** (e.g., `h1`).  
  - Choose one host as **attacker** (e.g., `h2`).  
  - Choose four hosts as **agents** (e.g., `h3`, `h4`, `h5`, `h6`).  

- Assign IPs (either default 10.0.0.x or as provided by your lab). Note the IP of the victim and each agent host.

- On the victim host:
  - Optionally run a simple TCP server listening on a chosen port (e.g., 8080) so that the victim responds with SYN‑ACK to incoming SYNs. [web:113]

## Attacker Program Design (RAW TCP SYN Generator)

### Raw socket creation

On the attacker host:

- Create a raw socket for TCP:  
int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

text
- Set option to include your own IP header:  
int one = 1;
setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one));

text

### Packet construction

For each SYN packet, manually construct:

1. **IP header** (`struct iphdr`): [web:149]
 - Version = 4, IHL, Total length = IP header + TCP header.  
 - Protocol = IPPROTO_TCP.  
 - Source IP = **spoofed agent host IP** (cycle through the four agent IPs).  
 - Destination IP = victim IP.  
 - TTL and Identification as desired.  
 - Header checksum computed with standard Internet checksum. [web:149][web:160]

2. **TCP header** (`struct tcphdr`): [web:152][web:145]
 - Source port = arbitrary (could randomize).  
 - Destination port = victim service port (e.g., 8080 or 80).  
 - Sequence number = random or incrementing.  
 - Flags: SYN = 1, others 0.  
 - Window size, offset set appropriately.  
 - TCP checksum computed over pseudo‑header + TCP header (and payload if any). [web:149][web:160]

3. **Payload**:
 - For SYN flood, no payload is necessary; standard SYN segments typically have no data. [web:138]

### Sending SYN packets

- Use `sendto()` in a loop to send many SYNs at a controlled or high rate: [web:152][web:148]

while (1) {
// build IP+TCP headers with spoofed src IP
sendto(sock, packet, packet_len, 0,
(struct sockaddr *)&dest_addr, sizeof(dest_addr));
// optional: small delay to control rate
}

text

- Cycle the spoofed source IP among the four agent hosts to emulate a DDoS from multiple sources. [web:150][web:154]

## Observing and Analyzing the Attack Pattern

1. **Wireshark/tcpdump capture**

 - Run Wireshark or tcpdump on:
   - The victim host’s interface, or  
   - The Mininet VM interface. [web:150][web:157]

 - Apply a filter such as:
   - `tcp and host <victim_ip>`  
   - or `tcp[tcpflags] & tcp-syn != 0` to see SYN packets. [web:150]

2. **Expected pattern**

 In the captured trace, you should see: [web:150][web:153]

 - Many TCP segments with:
   - Destination IP = victim.  
   - SYN flag set.  
   - Source IPs = the four spoofed agent addresses.  

 - From the victim’s perspective:
   - It will send SYN‑ACK responses toward the spoofed IPs.  
   - Because those hosts never actually initiated a real TCP handshake and never send ACK back, connections remain half‑open for some time (until timeout). [web:150][web:153]

 This is the typical **SYN flood** signature: large number of SYNs, many SYN‑ACKs, but very few (or no) final ACKs. [web:150]

## Implementation and Safety Hints

- Run as **root** (raw sockets require elevated privileges). [web:152][web:161]  
- Ensure IP forwarding/firewall rules in the VM are not interfering with raw packet transmission. [web:155]  
- Keep the flood **rate limited** in the lab so the VM and Mininet do not become unresponsive.  
- Perform all experiments only inside the controlled Mininet environment, never toward external or production networks. [web:150][web:155]

## Expected Deliverables

Submit:

- C source code for the raw‑socket TCP SYN generator program. [web:152][web:145]  
- A brief README/report describing:
- Mininet topology (which hosts are attacker, victim, agents and their IPs). [web:101]  
- How you construct IP and TCP headers and compute checksums. [web:149][web:160]  
- How you spoof source IPs for the four agent hosts.  
- How to compile and run the program (including root requirement). [web:152][web:146]  
- Wireshark screenshots showing:
  - Streams of SYN packets to the victim from multiple spoofed IPs.  
  - SYN‑ACK responses from the victim to agent IPs, with no final ACKs. [web:150][web:153]
