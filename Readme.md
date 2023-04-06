#Instructions

1. Use a linux based computer
2. Paste the following commands in on seperate Bash terminals :terminal

```BASH 
   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 1111 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31121 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31131 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31141 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31151 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31161 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31171 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 32181 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 32300 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 32301 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt
   

   

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


1111,1141,126
1111,1121,67
1121,1171,54
1121,1131,32
1131,1161,71
1131,1151,49
1141,1161,55
1141,1171,32
1151,2300,64
1151,1171,40
1161,2181,23
1161,2181,77
1171,2300,22
2171,2300,49
2181,2301,90



31111,31141,126
31111,31121,67
31121,31171,54
31121,31131,32
31131,31161,71
31131,31151,49
31141,31161,55
31141,31171,32
31151,32300,64
31151,31171,40
31161,32181,23
31161,32181,77
31171,32300,22
32171,32300,49
32181,32301,90

301111
301121
301131
301141
301151
301161
301171
302181
302300
302301