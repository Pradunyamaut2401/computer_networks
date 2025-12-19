
# CN Lab – Assignment 14: Custom Leaf–Spine Topology in Mininet

## Objective
To learn the **Mininet Python API** by implementing a custom, scalable **leaf–spine (Clos‑style)** topology where the number of leaf and spine switches can be increased according to switch radix, and to use it for virtual network experiments. [web:199][web:208]

## Problem Statement
Create a Python script that defines a **custom Mininet topology** representing a leaf–spine fabric:

- There are two layers of switches:
  - **Spine switches** (core of the fabric).  
  - **Leaf switches** (ToR/access layer). [web:201][web:199]  
- Each leaf connects to every spine (full bipartite connectivity), or to a configurable number of spine links per leaf. [web:201]  
- Each leaf has one or more hosts attached.  
- The topology must be **scalable** with switch radix:
  - You should be able to specify, via parameters, the number of leaf switches, spine switches, and hosts per leaf, derived from or limited by the assumed port count (radix) of switches, similar to Fat‑Tree parameterization. [web:202][web:207]

The topology must be usable with Mininet’s `--custom` option.

## Design Requirements

### Mininet Topo class

- Define a class that inherits from `mininet.topo.Topo`, overriding `build()` (or using `__init__` + `Topo.__init__`) to create the topology. [web:203][web:208]

Example skeleton:

from mininet.topo import Topo

class LeafSpineTopo(Topo):
def build(self, num_leaf=2, num_spine=2, hosts_per_leaf=2):
# 1. Add spine switches
# 2. Add leaf switches
# 3. Add hosts and connect them to leafs
# 4. Connect each leaf to each spine
pass

text

- At the bottom of the script, register the topology for `--topo`:

topos = {
'leafspine': (lambda num_leaf=2, num_spine=2, hosts_per_leaf=2:
LeafSpineTopo(num_leaf=num_leaf,
num_spine=num_spine,
hosts_per_leaf=hosts_per_leaf))
}

text

This follows the pattern of custom topologies in Mininet’s documentation. [web:101][web:211]

### Scaling with switch radix (Fat‑Tree reference)

- Use Fat‑Tree concepts as reference:
  - In a classic k‑port Fat‑Tree, the number of pods, edge/aggregation switches, and hosts are derived from k. [web:202][web:207]  
- For this assignment, you can:
  - Treat the **switch radix** as an upper bound on the number of ports per spine/leaf.  
  - Ensure that:
    - `hosts_per_leaf + num_spine ≤ radix` for leaf switches.  
    - `num_leaf ≤ radix` for spine switches.  

This makes the topology scalable and realistic with respect to port counts, as in data‑center CLOS/Fat‑Tree designs. [web:202][web:204]

## Implementation Outline

### 1. Building the topology

Within `build(self, num_leaf, num_spine, hosts_per_leaf)`:

- **Create spine switches**:  
spines = []
for i in range(1, num_spine + 1):
sw = self.addSwitch(f'sp{i}')
spines.append(sw)

text

- **Create leaf switches**:  
leafs = []
for i in range(1, num_leaf + 1):
sw = self.addSwitch(f'lf{i}')
leafs.append(sw)

text

- **Create hosts and connect to leafs**:  
for i, lf in enumerate(leafs, start=1):
for h in range(1, hosts_per_leaf + 1):
host = self.addHost(f'h{i}_{h}')
self.addLink(host, lf)

text

- **Connect each leaf to each spine** (full bipartite leaf–spine fabric):  
for lf in leafs:
for sp in spines:
self.addLink(lf, sp)

text

This structure creates a Clos‑style topology that can be scaled by changing `num_leaf`, `num_spine`, and `hosts_per_leaf`.

### 2. Running the custom topology

- Save your script (e.g., `leafspine.py`) in a directory accessible to Mininet.  
- Start Mininet with:

sudo mn --custom leafspine.py --topo leafspine,num_leaf=4,num_spine=2,hosts_per_leaf=2 --controller remote

text

or for a simple local test:

sudo mn --custom leafspine.py --topo leafspine --test pingall

text

- Use `pingall`, `iperf`, or other commands to run experiments on the virtual network. [web:181][web:209]

## What to Document

In your README/report, describe:

- The **parameters** of your topology:
  - How `num_leaf`, `num_spine`, `hosts_per_leaf`, and switch radix relate. [web:199][web:204]  
- How the code uses the **Mininet API**:
  - `Topo` subclass, `addSwitch`, `addHost`, `addLink`, and the `topos` dictionary. [web:208][web:211]  
- Example commands for:
  - Creating small and larger leaf–spine fabrics.  
  - Running connectivity and performance tests (e.g., `pingall`, `iperf`). [web:181][web:209]

Explain briefly how this custom topology can be used to **perform experiments in virtual networks** (e.g., testing routing, load balancing, or congestion scenarios in a scalable data‑center‑like fabric). [web:201][web:204]
