#include "fifo_evictor.hh"

//evict blocks in order they were added, without regard to how often they were accessed before.
Fifo_Evictor::Fifo_Evictor(){

}

Fifo_Evictor::~Fifo_Evictor() = default; //may be able to be lazy with this?

const key_type Fifo_Evictor::evict(){
    if (values.empty() == false)
    {
        key_type lastkey = values.front();
        values.pop();
        return lastkey;
    }
}


void Fifo_Evictor::touch_key(const &key_type key){
    values.push(key);
}

