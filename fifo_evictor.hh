#include "evictor.hh"
#include <vector>
#include <list>
#include <deque>
#include <queue>

using namespace std;

class Fifo_Evictor:public Evictor
{
private:
    //I would LIKE to make this a queue since these are best for FIFO... but, the queue has no way to account for moving an object if its touched again
    deque<key_type> values;
public:
    const key_type evict();
    void touch_key(const key_type&);
    Fifo_Evictor();
    ~Fifo_Evictor();
};
