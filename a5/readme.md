
# CN Lab – Assignment 5: Packet Generation Tools

## Objective
To gain knowledge of **packet generation** and related measurement tools by installing and using multiple traffic generators (e.g., iperf, D-ITG) between Mininet hosts. [web:53][web:52]

## Problem Statement
Learn and use as many packet generation tools as possible in a Linux VM environment with Mininet. [web:53][web:47] At a minimum:

- Install and use `iperf` (or `iperf3`) to generate TCP and/or UDP traffic between Mininet hosts. [web:57][web:63]  
- Install and use `D-ITG` to generate configurable traffic flows with different protocols and traffic patterns. [web:59][web:46]

You are encouraged to explore additional tools (e.g., Netperf, PackETH, Ostinato, pktgen, etc.) if allowed by your lab environment. [web:52][web:61]

## Learning Outcomes
After completing this assignment, you will be able to:

1. Use **packet generation tools** (iperf, D-ITG, etc.) to create controlled traffic between hosts in a Mininet topology. [web:47][web:59]  
2. Understand how generated traffic can be captured and analyzed with tools like Wireshark or tcpdump. [web:56][web:49]  
3. Compare basic capabilities and usage patterns of different traffic generators. [web:52][web:61]

## Environment Setup

- Platform: Linux VM running Mininet (or Mininet-WiFi, as specified). [web:60][web:63]  
- Tools to install (minimum set):
  - `iperf` / `iperf3` [web:57]  
  - `D-ITG` (Distributed Internet Traffic Generator) [web:59]

Example installation (Ubuntu/Debian-style):

sudo apt update
sudo apt install iperf iperf3

D-ITG is usually installed from tarball or packages provided on the project site
(download from the official D-ITG page and follow its installation instructions)
text

Refer to the D-ITG website/documentation for exact build and install steps. [web:59][web:50]

## Task Steps

Follow the hint sequence and document each step with commands and screenshots/output.

1. **Start Mininet topology**  
   - Launch a simple topology (e.g., `sudo mn --topo single,3 --controller remote --switch ovsk`) or a course-provided topology script. [web:63]  
   - Confirm connectivity using `pingAll`. [web:63][web:54]

2. **Use iperf between hosts**

   Example CLI usage inside Mininet: [web:57][web:63]

   - Start iperf server on one host (e.g., `h2`):
     ```
     h2 iperf -s
     ```
   - Start iperf client on another host (e.g., `h1`):
     ```
     h1 iperf -c 10.0.0.2 -t 10
     ```
   - For UDP traffic:
     ```
     h2 iperf -s -u
     h1 iperf -c 10.0.0.2 -u -b 5M -t 10
     ```
   - Record reported bandwidth, loss (for UDP), and other statistics. [web:57]

3. **Use D-ITG between hosts**

   D-ITG components: `ITGSend` (sender) and `ITGRecv` (receiver). [web:50][web:59]

   Typical sequence (run in Mininet hosts):

   - Start receiver on destination host:
     ```
     h2 ITGRecv
     ```
   - Start sender on source host with chosen parameters (e.g., UDP flow):
     ```
     h1 ITGSend -a 10.0.0.2 -T UDP -C 1000 -c 512 -t 10000 -l sender.log
     ```
     - `-T`: protocol (TCP, UDP, etc.)  
     - `-C`: packet rate (packets per second)  
     - `-c`: packet size (bytes)  
     - `-t`: duration (milliseconds) [web:50][web:49]
   - After completion, process logs (if applicable) with `ITGDec` to obtain throughput, delay, jitter statistics. [web:59][web:46]

4. **(Optional) Try additional tools**

   If time and permissions permit, explore at least one more traffic generator, for example: [web:52][web:61]

   - `Netperf` for performance measurement (TCP/UDP throughput, latency).  
   - GUI-based generators such as PackETH or Ostinato (if a GUI is available).  
   - Kernel-based `pktgen` for high-speed packet generation (advanced). [web:62]

   Record basic steps to start traffic and any metrics they report.

5. **Capture and observe generated traffic**

   - Run `tcpdump` or Wireshark on the Mininet host or VM interface while running iperf/D-ITG. [web:56][web:49]  
   - Verify that:
     - Flows correspond to chosen protocols and ports.  
     - Traffic rate roughly matches configured rate (where reported).

## What to Document in README / Report

For each tool you use (at least iperf and D-ITG):

- Tool name and **purpose** (e.g., bandwidth measurement, realistic traffic generation, distributions). [web:49][web:59]  
- Installation method (commands or brief steps).  
- Example command lines used in your Mininet experiment (server/receiver and client/sender). [web:57][web:50]  
- Key output metrics observed (e.g., throughput, packet loss, delay, jitter). [web:46][web:49]  
- Any differences in capabilities, such as:
  - D-ITG’s support for multiple probability distributions for inter-departure times and packet sizes (Constant, Poisson, Pareto, etc.). [web:49][web:59]  
  - iperf’s focus on simple throughput measurement without detailed per-packet logs. [web:46][web:52]

## Expected Deliverables

Submit:

- This `README.md` (or equivalent documentation) describing objective, environment, commands, and observations.  
- Screenshots or logs showing:
  - iperf server/client runs and measured bandwidth. [web:57]  
  - D-ITG ITGSend/ITGRecv runs and decoded statistics. [web:46][web:59]  
- A short comparison paragraph summarizing which tool is more suitable for:
  - Simple throughput tests.  
  - Detailed traffic modeling and per-flow statistics. [web:49][web:52]
