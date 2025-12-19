
# CN Lab – Assignment 12: ICMP Flood using RAW Sockets

## Objective
To use **raw sockets** in C to generate an ICMP (ping) flooding attack towards a victim IP and to study the ICMP traffic pattern of a DDoS‑style flood in a controlled Mininet environment. [web:172][web:164]

## Problem Statement
Using Mininet with **six hosts**:

- 1 host as the **attacker** running your raw‑socket ICMP flood program.  
- 1 host as the **victim** (any host with an IP address reachable in the topology).  
- 4 hosts as **agent devices** whose IP addresses will be used as **spoofed source IPs**. [web:178][web:174]

On the attacker host, write a C program that:

1. Creates a **raw socket** and crafts ICMP packets with user‑chosen header fields. [web:172][web:169]  
2. Sends a high rate of **ICMP Echo Request** packets (type 8, code 0) with:
   - Destination IP = victim.  
   - Source IPs spoofed to match the four agent hosts (cycling among them). [web:164][web:178]  

The victim (or any observing node) will capture traffic in Wireshark to visualize the ICMP flood and its DDoS characteristics. [web:168][web:171]

> Run this only inside the lab/Mininet environment, never on real or production networks.

## Learning Outcomes
After completing this assignment you will:

1. Understand how to use **raw sockets** to construct custom ICMP packets and spoof IP source addresses. [web:172][web:178]  
2. Recognize the characteristic **ICMP flood** pattern in packet captures: a high rate of Echo Requests from multiple spoofed sources, with replies attempting to go back to those sources. [web:164][web:176]

## Mininet Setup

- Create a Mininet topology with at least 6 hosts (e.g., `h1`–`h6`). [web:174]  
  - Choose one host as **victim** (e.g., `h1`).  
  - Choose one host as **attacker** (e.g., `h2`).  
  - Choose four hosts as **agents** (e.g., `h3`, `h4`, `h5`, `h6`).  

- Note the IP addresses of the victim and each agent; these will be used in your spoofed source IP fields. [web:174]

## Attacker Program Design (Raw ICMP Flood Generator)

### Raw socket creation

On the attacker host, use a raw socket for ICMP:

int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

text

Depending on the platform, either:

- Provide only the ICMP header and let the kernel add the IP header (when using `IPPROTO_ICMP`), or  
- Provide your own IP header as well (for full spoofing, typically with `IPPROTO_RAW` and `IP_HDRINCL`). [web:163][web:169]

In many Linux examples, an `AF_INET` raw socket with `IPPROTO_RAW` is used, and you manually build both IP and ICMP headers, then set `IP_HDRINCL`. [web:169][web:172]

### Packet construction

For an ICMP Echo Request: [web:147][web:172]

1. **IP header** (`struct iphdr`), if you are constructing it:
   - Version = 4, header length, total length = IP header + ICMP header + payload.  
   - Protocol = IPPROTO_ICMP.  
   - Source IP = spoofed IP from one of the four agent hosts. [web:178]  
   - Destination IP = victim IP.  
   - TTL and Identification as desired.  
   - Compute IP checksum using the standard Internet checksum. [web:172]

2. **ICMP header** (`struct icmphdr` or custom):
   - Type = 8 (Echo Request), Code = 0. [web:164][web:147]  
   - Identifier and sequence number can be arbitrary (e.g., random or incrementing).  
   - Payload: small data (e.g., a string like `"ICMPFLOOD"` plus a counter) to help identify packets in Wireshark. [web:169]  
   - Compute ICMP checksum over header + payload. [web:164][web:167]

3. Place the IP header (if used), ICMP header, and payload into a single packet buffer for `sendto()`. [web:172]

### Flood loop

Implement a loop that:

- Cycles through the 4 agent IP addresses as spoofed `src_ip`. [web:178]  
- Rebuilds or updates the IP header source address and ICMP identifier/sequence.  
- Calls `sendto(sock, packet, packet_len, 0, (struct sockaddr *)&dest, sizeof(dest));` repeatedly to send echo requests at a high rate. [web:169][web:164]

Optionally, add:

- A small sleep (`usleep`) to control the flood rate so the VM remains responsive.  
- Command‑line arguments for victim IP, number of packets, and delay.

## Observing the DDoS Pattern with Wireshark

1. **Capture setup**

   - Start Wireshark or tcpdump on:
     - The victim host’s interface, or  
     - The Mininet VM interface carrying host traffic. [web:174]  

   - Use filter: `icmp && host <victim_ip>` to focus on ICMP packets toward the victim. [web:171]

2. **Expected ICMP flood pattern**

   In the capture, you should observe: [web:168][web:176]

   - A large volume of **ICMP Echo Request** packets to the victim’s IP.  
   - Source IPs corresponding to the four agent hosts, even though only the attacker is actually sending (IP spoofing). [web:178]  
   - If the victim replies:
     - ICMP Echo Reply packets sent back toward the spoofed addresses.  
     - The agents may not respond or may be unaware, illustrating a DDoS effect. [web:176][web:164]

   This pattern—many echo requests per second from multiple apparent sources—is a classic **ICMP flood** signature. [web:168][web:171]

## Implementation and Safety Hints

- Raw sockets require **root privileges**, so run the program with `sudo`. [web:172][web:165]  
- Be careful with flood intensity to avoid freezing the Mininet VM.  
- Keep the experiment strictly confined to the Mininet lab environment. [web:173][web:174]

## Expected Deliverables

Submit:

- C source code for the **raw‑socket ICMP flood generator** that:
  - Builds custom ICMP Echo Request packets. [web:169][web:147]  
  - Spoofs source IPs for four agent hosts. [web:178]  

- A brief README/report describing:
  - Mininet topology (attacker, victim, agents, and their IPs). [web:174]  
  - How you construct and checksum ICMP and (if applicable) IP headers. [web:172][web:167]  
  - How to compile and run the program (including root requirement and parameters).  
  - Wireshark screenshots showing:
    - High‑rate ICMP Echo Requests to the victim from multiple spoofed IPs. [web:168][web:171]  
    - Any ICMP Echo Replies sent back toward agents, illustrating the DDoS pattern. [web:176]
