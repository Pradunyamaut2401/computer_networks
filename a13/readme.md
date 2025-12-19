
# CN Lab – Assignment 13: Packet Capture and Protocol Analysis in a Tree Topology

## Objective
To learn **packet capturing and analysis** by creating a 7‑switch binary tree topology in Mininet, capturing packets at the root switch during a PING operation, and using a C program to extract headers, draw a time diagram, and list L2/L3/L4 protocols from a `.pcap`/`.pcapng` file. [web:181][web:187]

## Mininet Setup and Packet Capture

1. **Create binary‑tree topology with 7 switches**

   - Use Mininet’s tree topology (depth 2, fanout 2) or a custom script to emulate a 7‑switch binary tree (1 root, 2 children, 4 grandchildren). [web:182][web:193]  
   - Example Mininet command (tree with depth 3, fanout 2, which gives 1 + 2 + 4 = 7 switches):  
     ```
     sudo mn --topo tree,depth=3,fanout=2
     ``` [web:196][web:184]

2. **Capture packets at the root switch**

   - Identify the root switch (e.g., `s1`) from the topology.  
   - Open an xterm for the root switch from the Mininet CLI:  
     ```
     mininet> xterm s1
     ``` [web:101]  
   - In the `s1` xterm, capture packets on the appropriate interface using `tcpdump` or `tshark`, saving to `.pcap` or `.pcapng`:  
     ```
     tcpdump -i s1-eth1 -w tree_ping.pcap
     ``` [web:185][web:192]

3. **Generate PING traffic**

   - From Mininet CLI, ping between two hosts at the leaves of the tree, for example:  
     ```
     mininet> h1 ping -c 5 h4
     ``` [web:101]  
   - Stop the capture after the ping finishes.

4. **Inspect capture**

   - Optionally open `tree_ping.pcap` in Wireshark to verify packets and understand the ICMP ping exchange (Ethernet + IP + ICMP). [web:32][web:36]

## C Program: Parsing the Capture and Time Diagram

Write a C program that uses **libpcap** to read the saved `.pcap`/`.pcapng` file and extract timing and protocol information. [web:185][web:187]

### Reading packets with libpcap

- Include `pcap.h` and open the capture file offline:

pcap_t *handle;
char errbuf[PCAP_ERRBUF_SIZE];

handle = pcap_open_offline("tree_ping.pcap", errbuf);

text

- Use `pcap_loop` or `pcap_next_ex` to iterate over all packets: [web:187][web:192]

const u_char *packet;
struct pcap_pkthdr *header;
int res;
while ((res = pcap_next_ex(handle, &header, &packet)) >= 0) {
// header->ts.tv_sec / tv_usec gives timestamp
// packet points to raw bytes
}

text

### Extracting L2/L3/L4 headers

- Use standard structs to parse headers from `packet`: [web:190][web:187]

- **L2 (Ethernet)**:
  - `struct ether_header` from `<net/ethernet.h>`; gives source/destination MAC and EtherType.  
  - EtherType 0x0800 → IPv4, 0x86DD → IPv6, 0x0806 → ARP. [web:190]

- **L3 (IP/ARP)**:
  - If IPv4: `struct ip`/`struct iphdr` from `<netinet/ip.h>`; gives source/destination IP, protocol (e.g., 1 = ICMP, 6 = TCP, 17 = UDP), TTL, etc. [web:192][web:35]  
  - If ARP: parse `struct ether_arp`.  

- **L4 (ICMP/TCP/UDP)**:
  - If protocol = 1: ICMP, parse `struct icmphdr` (type, code, checksum, identifier, sequence). [web:35][web:36]  
  - If protocol = 6: TCP, parse `struct tcphdr` (ports, flags).  
  - If protocol = 17: UDP, parse `struct udphdr` (ports, length). [web:187][web:192]

- Keep track of:
- Timestamp (`header->ts`).  
- Highest‑level protocol for each packet (e.g., ARP, ICMP, TCP, UDP).  

### Time diagram in C

- As you iterate, print a simple time‑ordered log that can be interpreted as a **time diagram**, for example:

t=0.000000 ARP h1 -> h4 (Who has IP x.x.x.x?)
t=0.001234 ARP h4 -> h1 (Reply)
t=0.002345 ICMP Echo Request src=10.0.0.1 dst=10.0.0.4
t=0.003210 ICMP Echo Reply src=10.0.0.4 dst=10.0.0.1
...

text

- In C, you can:
- Compute a reference time from the first packet and then print `delta_t` for each subsequent packet using `header->ts`. [web:192][web:195]  
- Include fields like src/dst IP and protocol name to show protocol progression over time.

This text‑based time diagram can then be redrawn as a figure in your lab report.

## Listing L2/L3/L4 Protocols

From all packets in the capture, your program should build **sets of unique protocol types** seen at each layer:

- **L2 protocols** (from EtherType): [web:185][web:190]  
- Ethernet II carrying: ARP, IPv4 (and possibly IPv6).  

- **L3 protocols** (from IP protocol field or ARP type): [web:192][web:35]  
- ARP.  
- IPv4 ICMP.  
- Possibly IPv4 TCP/UDP if any other traffic exists.

- **L4 protocols** (from IP protocol field and corresponding header parsing): [web:35][web:36]  
- ICMP (Ping Echo Request/Reply).  
- TCP or UDP if present in the trace.

Print a summary at the end, for example:

L2 protocols seen: Ethernet (IPv4), ARP
L3 protocols seen: ARP, IPv4
L4 protocols seen: ICMP

text

for a simple ping‑only capture, or including TCP/UDP if they appear.

## Expected Deliverables

Submit:

- Mininet commands or topology script used to create the 7‑switch binary tree and description of which switch is the root. [web:182][web:193]  
- The `.pcap`/`.pcapng` file captured at the root switch during a ping between two hosts.  
- C source code that:
  - Reads the capture with libpcap. [web:185][web:187]  
  - Extracts Ethernet, IP, and L4 (ICMP/TCP/UDP) headers.  
  - Prints a time‑ordered event list (time diagram) of packets and their protocols.  
  - Lists unique L2/L3/L4 protocol types observed.  
- A brief report or README explaining:
  - How to compile/run the C program.  
  - Example output showing the time diagram and protocol lists, and what this reveals about the roles of L2/L3/L4 during a ping operation. [web:188][web:36]
