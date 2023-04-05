#Instructions

1. Use a linux based computer
2. Paste the following commands in on seperate Bash terminals :terminal

```BASH 
   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301111 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301121 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301131 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301141 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301151 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301161 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 301171 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 302181 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 302300 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c -o p2p
   ./p2p 302301 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt
   

   

```

```BASH
   #!/usr/bin/env bash
   konsole --noclose -e echo ./p2p 1111 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txtHello terminal 1! &
   konsole --noclose -e echo ./p2p 1121 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 1131 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 1141 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 1151 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 1161 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 1171 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 2181 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 2300 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt &
   konsole --noclose -e echo ./p2p 2301 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt
```