#include "evictor.hh"
#include <vector>
#include <deque>
#include <queue>

using namespace std;

class Fifo_Evictor: public Evictor
{
private:
    /* data */
    queue<key_type, vector<key_type>> values;
public:
    const key_type evict();
    void touch_key(const &key_type);
    Fifo_Evictor();
    ~Fifo_Evictor();
};
