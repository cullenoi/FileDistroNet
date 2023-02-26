#include <iostream.h>
#include <vector.h>
#include <time.h>

#include "Tracker.h"


using namespace std;

class Node{

    private:
        unsigned address;
        node_list * address_book;
        //book_date: yy/mm/dd/hh/mm/ss/..
        unsigned book_date;

    public:

        init_node();
        book_spead();
        book_seek();


}

// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: