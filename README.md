text
# Computer Networks Lab – Assignments 1–14

This repository contains implementations and experiment artifacts for all **Computer Networks (CN) Lab** assignments (1–14) based on the official lab manual. [file:216]  

## Repository Structure

Each assignment has its own subfolder:

- `a1/` – Assignment 1: Basic TCP socket **“Hi/Hello”** client–server. [file:216]  
- `a2/` – Assignment 2: TCP socket **fruit store** server with multiple clients and per‑client transaction tracking. [file:216]  
- `a3/` – Assignment 3: UDP implementation of Assignment 2 (same fruit‑store logic over UDP). [file:216]  
- `a4/` – Assignment 4: Wireshark‑based **packet capture and analysis** of PING; time diagram and L2/L3/L4 headers from `.pcap`. [file:216]  
- `a5/` – Assignment 5: Traffic **generation tools** (iperf, D‑ITG, etc.) with Mininet hosts. [file:216]  
- `a6/` – Assignment 6: C‑based **TCP traffic analyzer/simulator** using TCP/IP libraries to capture headers and data. [file:216]  
- `a7/` – Assignment 7: UDP **scientific calculator** client–server with packet‑loss detection and Wireshark verification. [file:216]  
- `a8/` – Assignment 8: Multithreaded TCP **group chat server** using `pthread` and server‑side logging. [file:216]  
- `a9/` – Assignment 9: TCP **file upload/download** between two hosts with transfer‑time measurement using `time.h`. [file:216]  
- `a10/` – Assignment 10: RAW‑socket **custom TCP** (roll number payload) and **ICMP timestamp** packet generators. [file:216]  
- `a11/` – Assignment 11: RAW‑socket **TCP SYN flood** generator (attacker + victim + 4 spoofed agents in Mininet). [file:216]  
- `a12/` – Assignment 12: RAW‑socket **ICMP flood** generator mirroring Assignment 11 with ICMP packets. [file:216]  
- `a13/` – Assignment 13: 7‑switch **binary tree** Mininet topology, capture at root switch, C parser for `.pcap` and protocol/time diagram. [file:216]  
- `a14/` – Assignment 14: Custom scalable **leaf–spine** Mininet topology in Python (radix‑aware, Fat‑Tree inspired). [file:216]  

You may additionally have:

- `CN-Lab-Manual-2.pdf` – Original lab manual specifying all assignment statements and learning outcomes. [file:216]  

## Common Requirements

Across assignments, the following environment and tools are typically used: [file:216]  

- **Mininet** for emulated network topologies and hosts.  
- **Linux VM** for running Mininet, servers, clients, and captures.  
- **C** for socket programming (TCP/UDP, raw sockets, libpcap).  
- **Python** for Mininet custom topologies.  
- **Wireshark/tcpdump/tshark** for packet capture and analysis.  

Each assignment subfolder is expected to contain:

- Source code (`.c`, `.h`, `.py`, etc.).  
- A per‑assignment `README.md` describing objectives, usage, and sample outputs.  
- Any scripts, `.pcap`/`.pcapng` files, or logs required by that assignment.  

## How to Use This Repository

1. **Clone** the repository and move into it:

git clone <your-repo-url> cn-lab
cd cn-lab

text

2. **Per‑assignment work**:

- Navigate to the relevant folder, e.g.:
  ```
  cd a7
  ```
- Follow that folder’s `README.md` for compilation, execution, and experiment steps (Mininet commands, Wireshark filters, etc.).

3. **Environment assumptions**:

- Mininet installed and working on a Linux VM. [file:216]  
- Root privileges (`sudo`) available where needed (raw sockets, Mininet, packet capture). [file:216]  

## License and Academic Use

This repository is intended for **educational use** in the Computer Networks Lab course. Adapt or extend the code for learning and experiments; follow your institution’s academic integrity guidelines when using or submitting this work. [file:216]
