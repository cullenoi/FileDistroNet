#include <iostream>
#include <vector>


using namespace std;

class Node{

    private:
        unsigned address;
        vector<unsigned> address_book;

    public:

    init_node();

}

// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 