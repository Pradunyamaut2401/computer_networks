This assignment asks you to capture and analyze ICMP Echo (PING) traffic in Wireshark, then derive a time diagram and list key Ethernet, IP and transport/ICMP header fields from the capture.​

text
# CN Lab – Assignment 4: Wireshark Ping Analysis

## Objective
To gain knowledge of **packet capturing tools** and understand protocol header structures by analyzing a ping operation in Wireshark. [web:34][web:41]

## Problem Statement
Install Wireshark in a Linux virtual machine environment and capture packets during a PING operation between two hosts. [web:34][web:32] Using the captured trace (saved as a `.pcap` file), you must:

- Draw a time diagram showing the sequence of packets exchanged during the ping (Echo Request and Echo Reply, plus any ARP if visible). [web:32][web:39]  
- List the Layer 2 (L2), Layer 3 (L3), and Layer 4 (L4) header fields that can be extracted from the `.pcap` file for these packets. [web:38][web:36]

## Learning Outcomes
After completing this assignment you will be able to:

1. Use **Wireshark** to capture, filter, and save network packets in `.pcap` format. [web:34][web:38]  
2. Interpret the protocol stack involved in a ping (Ethernet, IP, ICMP) and understand how headers are layered. [web:36][web:39]  
3. Identify and describe important L2, L3, and L4 header fields from captured packets. [web:35][web:41]

## Environment Setup

- Platform: Linux VM (e.g., Ubuntu) with Mininet or any lab-specified topology. [web:31]  
- Tool: Wireshark (latest stable version for your distribution). [web:34]  

Install Wireshark inside the VM (for Debian/Ubuntu-like systems):

sudo apt update
sudo apt install wireshark

text

Ensure the current user has permission to capture packets (e.g., add user to `wireshark` group if required). [web:34]

## Task Steps

Follow these steps (adapted from the hints):

1. **Start Wireshark and select interface**  
   - Open Wireshark and choose the interface connected to your Mininet or VM network (e.g., `eth0`, `h1-eth0`). [web:34]  
   - Click “Start capturing packets”. [web:34]

2. **Generate ping traffic**  
   - In another terminal, ping between two hosts, for example:  
     ```
     ping <dest_ip>
     ```  
   - Let a few Echo Request/Reply pairs be exchanged, then stop the ping. [web:36][web:39]

3. **Stop capture and save `.pcap`**  
   - Stop the capture in Wireshark and save it as `ping_capture.pcap`. [web:34][web:41]

4. **Filter ICMP packets**  
   - Apply the display filter `icmp` in Wireshark to focus on Echo Request and Echo Reply packets. [web:35][web:39]

5. **Analyze protocol headers**  
   - For a selected Echo Request and Echo Reply, expand:  
     - Ethernet II  
     - Internet Protocol Version 4 (or 6)  
     - ICMP (Echo request/reply)  
   - Note down important header fields at each layer (see lists below). [web:35][web:36]

## Time Diagram Requirements

Using the timestamps column in Wireshark, construct a time diagram that shows the sequence of packets between the two hosts. [web:32][web:43] The diagram should include:

- Any ARP Request/Reply (if the MAC address is resolved during the ping). [web:32]  
- ICMP Echo Request messages. [web:36][web:39]  
- ICMP Echo Reply messages. [web:36][web:39]

Example logical structure (textual, suitable to redraw as a figure in your report):

- Host A  →  Network  →  Host B  

Typical sequence:

1. `ARP Request` (Host A asks “Who has IP of Host B?”). [web:32]  
2. `ARP Reply` (Host B responds with its MAC address). [web:32]  
3. `ICMP Echo Request` from Host A to Host B (within Ethernet + IP + ICMP). [web:36]  
4. `ICMP Echo Reply` from Host B to Host A. [web:36]  
5. (Optionally repeat Echo Request/Reply pairs for additional pings, showing time gaps). [web:32][web:39]

Include timestamps or relative times (e.g., `t0`, `t0 + Δ1`, etc.) from the Wireshark time column. [web:43]

## Header Fields to Extract

From the `.pcap` file, list at least the following header fields for ping packets.

### Layer 2 – Ethernet Header (L2)

For each ICMP packet, Ethernet header typically includes: [web:36][web:30]

- Destination MAC address  
- Source MAC address  
- EtherType (e.g., `0x0800` for IPv4)  

You can view these in Wireshark under the “Ethernet II” section. [web:36]

### Layer 3 – IP Header (L3)

Key IPv4 header fields visible in Wireshark during ping: [web:44][web:41]

- Version  
- Header Length (IHL)  
- Total Length  
- Identification  
- Flags and Fragment Offset  
- Time To Live (TTL)  
- Protocol (should show `ICMP` with value 1) [web:27][web:35]  
- Header Checksum  
- Source IP address  
- Destination IP address  

If IPv6 is used, corresponding fields include version, payload length, next header, hop limit, source and destination addresses. [web:44]

### Layer 4 – ICMP Header (treated as L4 here)

For Echo Request/Reply messages, ICMP fields include: [web:35][web:36]

- Type (8 = Echo Request, 0 = Echo Reply) [web:36][web:39]  
- Code (0 for standard Echo messages) [web:35]  
- Checksum  
- Identifier (used to match requests and replies) [web:41]  
- Sequence Number (increments for each ping) [web:41]  
- ICMP Data / Payload (contains user data and, for some implementations, timestamp or padding). [web:36]

Document these fields for at least one Echo Request and one Echo Reply packet, noting any changes (e.g., TTL, checksum, sequence number). [web:41][web:44]

## Expected Deliverables

Submit:

- The `.pcap` file containing your ping capture (e.g., `ping_capture.pcap`). [web:40]  
- A **time diagram** (hand-drawn or digital) showing ARP (if present), ICMP Echo Requests, and Echo Replies with direction and relative timing. [web:32][web:39]  
- A short report (or this README extended) listing the extracted L2, L3, and L4 header fields for at least one Echo Request and one Echo Reply, with brief explanations. [web:41][web:36]
