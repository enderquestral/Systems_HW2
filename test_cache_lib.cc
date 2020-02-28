#include "cache_lib.cc"
#include <cassert>

/*For testing purposes, assume the data payload is always of type C string, and don't forget to account for the last '\0' character 
at the end of the line. It will be easier to debug and print data of this type.

*/
constexpr int repeats = 10000;
int main(){
    auto cache = Cache(32);
    

    //Testing set

    /*int* eight = (int*)malloc(sizeof(int));
    *eight = 8;
    int* sixteen = (int*)malloc(sizeof(int));
    *sixteen = 16;
    int* eleven = (int*)malloc(sizeof(int));
    *twentyfour = 11;
    int* fourtysix = (int*)malloc(sizeof(int));
    *fourtysix = 8;*/
    Cache::size_type size;
    Cache::val_type val1 = "value1";
    Cache::val_type val2 = "value2";
    //Cache::val_type val3 = "value3";
    Cache::val_type valr = "reject?";
    //Cache::val_type val4 = "value4";
    //Cache::val_type val5 = "value5";

    assert(cache.space_used()==0);
    cache.set("key1", "value1", 8);
    cache.set("key2", "value2", 16);
    cache.set("key3", "reject?", 8); //Maybe reject this.
    //cache.set("key4", "reject", 8); //Almost certianly reject this
    //test get
    assert(cache.get("key1", size) == val1);
    assert(cache.get("key2", size) == val2);
    assert(cache.get("key3", size) == valr);
    //assert(cache.get("key4", 8) == nullptr);

    //test overwriting
   // cache.set("key3", "value4", 8); //write something new
    cache.set("key2", "value1", 8); //swap things
    cache.set("key1", "value2", 16);
   
   // assert(cache.get("key3", size) == val4);
    assert(cache.get("key2", size) == val1);
    assert(cache.get("key1", size) == val2);
    //test del  
    size = 0;
    cache.del("key1");
    assert(cache.get("key1", size) == nullptr);
    cache.del("key2");
    assert(cache.get("key2", size) == nullptr);
    cache.del("key3");
    assert(cache.get("key3", size) == nullptr);
    assert(cache.space_used() == 0);

    //test reset
    cache.set("key1", "value1", 8); //testing readding/overwriting here as well
    cache.set("key2", "value2", 16);
    cache.set("key3", "reject?", 8);
    assert(cache.space_used()!=0);
    cache.reset();
    assert(cache.get("key1", size) == nullptr);
    assert(cache.get("key2", size) == nullptr);
    assert(cache.get("key3", size) == nullptr);
    assert(cache.space_used() == 0);
    //test space used
    
    auto cache2 = Cache(50); //Changing the size for ease of access
    assert(cache2.space_used() ==0); //Making sure that values are added and space_used is increasing as well
    cache2.set("key1", "value1", 8);
    assert(cache2.space_used() == 8);
    cache2.set("key2", "value2", 16);
    assert(cache2.space_used()  == 24);
    cache2.set("key3", "value3", 8);
    assert(cache2.space_used() == 32);

    Cache::size_type altsize = 0;
    cache2.get("key1", altsize);//check if it properly edits altsize
    assert(altsize == 8);
    cache2.get("key2", altsize);
    assert(altsize == 16);
    cache2.get("key3", altsize);
    assert(altsize == 8);
    
    assert(cache2.space_used() == 32);
    cache2.set("key1", "difnumber", 46); //Overwrite entries, change sizes
    cache2.get("key1", altsize);
    assert(altsize == 46);
    assert(cache2.space_used() == 70);
    cache2.set("key3", "waaaaaaaaaaaaaytoolongavalue", 11); //Overwrite entries, change sizes
    cache2.get("key3", altsize);
    assert(altsize == 11);
    assert(cache2.space_used() == 73);

    return 0;
}