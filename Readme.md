#Instructions

1. Use a linux based computer
2. Paste the following commands in on seperate Bash terminals :terminal

```BASH 
   g++ P2P.cpp Node/Node.cpp Node/Routing.c Node/Tracker.c Request.c receiver_assembler.c -o p2p
   ./p2p 31111 Node/NodeInfo.csv Node/Nodes.txt Node/Edges.txt Node/Files.txt

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


31111,Node A,1000,"Afghanistan,Kabul,34.5289,69.1725,4011770"
31121,Node B,1004,"Albania,Tiranë (Tirana),41.3275,19.8189,475577"
31131,Node C,1007,"Algeria,El Djazaïr  (Algiers),36.7525,3.0420,2693542"
31141,Node D,1108,"American Samoa,Pago Pago,-14.2781,-170.7025,48526"
31151,Node E,1274,"Andorra,Andorra la Vella,42.5078,1.5211,22614"
31161,Node F,1333,"Angola,Luanda,-8.8368,13.2343,7774200"
31171,Node G,1443,"Anguilla,The Valley,18.2170,-63.0578,1402"
32181,Node H,1445,"Antigua and Barbuda,St. John's,17.1172,-61.8457,20764"
32300,Node I,1456,"Argentina,Buenos Aires,-34.6051,-58.4004,14966530"
32301,Node J,1556,"Armenia,Yerevan,40.1820,44.5146,1080324"



1000
1004
1007
1108
1274
1333
1443
1445
1456
1556