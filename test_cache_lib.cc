#include "cache_lib.cc"
#include <cassert>

/*For testing purposes, assume the data payload is always of type C string, and don't forget to account for the last '\0' character 
at the end of the line. It will be easier to debug and print data of this type.

*/
int return_number(key_type str){
    size_t length = str.length();
    return length;
}

function<size_t(key_type)> myhasher = return_number;  //takes str turns it into its str size


constexpr int repeats = 10000;
int main(){
    auto cache = Cache(32, 0.75, nullptr, myhasher);
    auto defaultedcache = Cache(32); //has no given hasher, uses its own default

    //Testing set
    Cache::size_type size;
    Cache::val_type val1 = "value1";
    Cache::val_type val2 = "value2";
    //Cache::val_type val3 = "value3";
    Cache::val_type valr = "reject?";
    //Cache::val_type val4 = "value4";
    //Cache::val_type val5 = "value5";

    assert(cache.space_used()==0);
    cache.set("key1", "value_1", 8);
    cache.set("key2", "value_2alright", 16);
    cache.set("key3", "reject?", 8); //Maybe reject this.
    //cache.set("key4", "reject", 8); //Almost certianly reject this
    //test get
    assert(*cache.get("key1", size) == *val1);
    assert(*cache.get("key2", size) == *val2);
    assert(*cache.get("key3", size) == *valr);
    //assert(cache.get("key4", 8) == nullptr);

    //test overwriting
   // cache.set("key3", "value4", 8); //write something new
    cache.set("key2", "value_1", 8); //swap things
    cache.set("key1", "value_2alright", 16);
    assert(*cache.get("key2", size) == *val1);
    assert(*cache.get("key1", size) == *val2);

    //test hasher
    //make defaulted cache be init w/same values as cache
    defaultedcache.set("key1", "value_1", 8);
    defaultedcache.set("key2", "value_2alright", 16);
    defaultedcache.set("key3", "reject?", 8); //Maybe reject this.w
    defaultedcache.set("key2", "value_1", 8); //swap things
    defaultedcache.set("key1", "value_2alright", 16);
    //The two caches cache and defaultedcache should have different buckets for the same "key1"

    //cout << cache.pImpl_->map.bucket("key1") << '\n'; //printing out, should have different numbers
    //cout << defaultedcache.pImpl_->map.bucket("key1") << '\n';
    //We don't have access to pImpl_ as it is private... but, if we set pImpl_ to public, then the two above numbers should be different.


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
    cache.set("key1", "value_1", 8); //testing readding/overwriting here as well
    cache.set("key2", "value_2alright", 16);
    cache.set("key3", "reject?", 8);
    assert(cache.space_used()!=0);
    cache.reset();
    assert(cache.get("key1", size) == nullptr);
    assert(cache.get("key2", size) == nullptr);
    assert(cache.get("key3", size) == nullptr);
    assert(cache.space_used() == 0);
    //test space used
    
    auto cache2 = Cache(100); //Changing the size for ease of access
    assert(cache2.space_used() ==0); //Making sure that values are added and space_used is increasing as well
    cache2.set("key1", "value_1", 8);
    assert(cache2.space_used() == 8);
    cache2.set("key2", "value_2alright", 16);
    assert(cache2.space_used()  == 24);
    cache2.set("key3", "value_3", 8);
    assert(cache2.space_used() == 32);

    Cache::size_type altsize = 0;
    cache2.get("key1", altsize);//check if it properly edits altsize
    assert(altsize == 8);
    cache2.get("key2", altsize);
    assert(altsize == 16);
    cache2.get("key3", altsize);
    assert(altsize == 8);
    
    assert(cache2.space_used() == 32);
    cache2.set("key1", "komencopaleontologiokonservatoriacestrigontaj", 46); //Overwrite entries, change sizes
    cache2.get("key1", altsize);
    //assert(altsize = 8);
    assert(altsize == 46); //IS NOT PROPERLY OVERWRITING ENTRIES
    assert(cache2.space_used() == 70);
    cache2.set("key3", "waaay2lon", 11); //Overwrite entries, change sizes
    cache2.get("key3", altsize);
    assert(altsize == 11);
    assert(cache2.space_used() == 73);

    return 0;
}